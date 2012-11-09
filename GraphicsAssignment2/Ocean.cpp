/*		Ocean CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class generates Procedurally Generated Ocean 
 * It also simulates the oceans animation
 * 
 * Last Updated: 07/11/2012
*/
#include "Ocean.h"
#include "TextureLoader.h"

#include <windows.h>	
#include <stdio.h>	
#include <freeglut.h>
#include <math.h>
#include "NormalHelper.h"
#include <time.h>
  
GLfloat seasc[64+1][64+1];
GLfloat seascO[64+1][64+1];
GLfloat cdss[64+1];
GLfloat normalst[64+1][64+1][3];

Ocean::Ocean()
{

}

Ocean::Ocean(int size)
{
	xPosition = -30;
	yPosition = 0;
	zPosition = -30;
	xAngle = 90; // straight up
	yAngle = 0;
	zAngle = 0;
	scale = 1;

	limit = 200;
	timer = 0;

	for (int x = 0; x <= size; x++)
	{
		cdss[x] = x;
	}

	texName = TextureLoader::loadTexture("Textures\\ocean.bmp");

	genMap(size);
}


Ocean::~Ocean(void)
{

}


void Ocean::genMap(int mapSize)
{	
	srand(time(0));
	int random_seed = rand();
	srand(random_seed);

	for (int i = 0; i <= mapSize; i++)
	{
		for (int j = 0; j <= mapSize; j++)
		{
			int rSize = ((rand()%20)+2);

			if(  (i < rSize) || (j < rSize) || (i > mapSize-rSize - 1) || ( j > mapSize-rSize))
			{
				seasc[i][j] = (float)rand()/((float)RAND_MAX/2.11f);
			}
			seascO[i][j] = seasc[i][j];
		}
	}

	update();
}



void Ocean::getColor(GLfloat color[4], int x , int y)
{
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;

	float distance = distanceT(x, y, 32, 32);
	float perc = distance/46;

	float r =  (0.4-perc);
	float g =  (0.8-perc) ;
	float b =  (0.75-perc) ;
	float a = (1-perc) ;

	color[0] = r; color[1] = g; color[2] = b; color[3] = a;  

}


double Ocean::distanceT(double dX0, double dY0, double dX1, double dY1)
{
    return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}


void Ocean::display(void)
{
	int size = 64;

	glPushMatrix(); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,1);



	int i, j;
	float v1[3],v2[3],out[3];
	glColor3f(1.0, 1.0, 1.0);
	v1[0] = cdss[1];
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = cdss[1];
   for (j = 0; j < size; j++)
      for (i = 0; i < size; i++) {
		  v1[2] = seasc[i+1][j] - seasc[i][j];
          v2[2] = seasc[i][j+1] - seasc[i][j];
		  NormalHelper::normcrossprod(v1,v2,out);
		 // NormalHelper::getSurfaceNormal(out, out, v1, v2);
		  normalst[i][j][0] = -out[0];
		  normalst[i][j][1] = -out[1];
		  normalst[i][j][2] = -out[2];
	  }
   for (j = 0; j < size; j++) {
	  normalst[size][j][0] = normalst[size-1][j][0];
      normalst[size][j][1] = normalst[size-1][j][1];
      normalst[size][j][2] = normalst[size-1][j][2];
	  }
   for (i = 0; i < size; i++) {
	  normalst[i][size][0] = normalst[i][size-1][0];
	  normalst[i][size][1] = normalst[i][size-1][1];
	  normalst[i][size][2] = normalst[i][size-1][2];
	  }
   normalst[size][size][0] = normalst[size-1][size-1][0];
   normalst[size][size][1] = normalst[size-1][size-1][1];
   normalst[size][size][2] = normalst[size-1][size-1][2];


   for (j = 0; j < size; j++)
      for (i = 0; i < size; i++){

		  glBegin(GL_POLYGON);
		  drawVertex(i,j);
		  glEnd();

	  }
      glEnd();  


	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}




void Ocean::drawVertex(int i , int j)
{
	GLfloat color[4] = {0,0,0 , 0};

	getColor(color , i,j);
	glColor4f(color[0], color[1], color[2] , color[3]);	  glNormal3fv(&normalst[i][j][0]);   glTexCoord2f(0,0);glVertex3f(cdss[i],cdss[j],-seasc[i][j]);

	getColor(color , i+1,j);
	glColor4f(color[0], color[1], color[2], color[3]);	  glNormal3fv(&normalst[i+1][j][0]);  glTexCoord2f(1,0); glVertex3f(cdss[i+1],cdss[j],-seasc[i+1][j]);

	getColor(color , i+1,j+1);
	glColor4f(color[0], color[1], color[2], color[3]);	  glNormal3fv(&normalst[i+1][j+1][0]); glTexCoord2f(1,1); glVertex3f(cdss[i+1],cdss[j+1],-seasc[i+1][j+1]);

	getColor(color , i, j+1);
	glColor4f(color[0], color[1], color[2], color[3]);  glNormal3fv(&normalst[i][j+1][0]); glTexCoord2f(0,1); glVertex3f(cdss[i],cdss[j+1],-seasc[i][j+1]);

}



void Ocean::update()
{
	timer+= 0.008f;

	for (int i = 0; i <= 64; i++)
	{
		for (int j = 0; j <= 64; j++)
		{

			GLfloat val1 = 0.1f *sin((float)(i+ timer))  ;
			GLfloat val2 = 0.3f *sin((float)(j+ (timer*2)))  ;
			GLfloat val3 = 0.3f *sin((float)(seascO[i][j] + timer) ) ;

			GLfloat valF = val1 + val2 + val3;
			seasc[i][j]  =valF - 0.4f ;
		}
	}

}