/*		Terrain CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class generates Procedurally Generated Terrain 
 * It also provides a crude shadow method
 * 
 * Last Updated: 03/10/2012
*/

#define _USE_MATH_DEFINES // Allows me to use PI constant 

#include "Terrain.h"
#include "TextureLoader.h"
#include "TerrainGenerator.h"
#include "SlopeHelper.h"
#include "NormalHelper.h"

#include <windows.h>	
#include <stdio.h>	
#include <freeglut.h>
#include <math.h>
#include "NormalHelper.h"
#include <time.h>
  


GLfloat landsc[64+1][64+1];
GLfloat slope[64+1][64+1];
GLfloat cd[64+1];
GLfloat normals[64+1][64+1][3];


Terrain::Terrain()
{

}

Terrain::Terrain(int sizeT)
{
	int size = sizeT;

		xPosition = -15;
	yPosition = 0;
	zPosition = -15;
	xAngle = 90; // straight up
	yAngle = 0;
	zAngle = 0;
	scale = 0.5;

	grassTex = TextureLoader::loadTexture("Textures\\grass.bmp");
	rockTex = TextureLoader::loadTexture("Textures\\rock.bmp");
	sandTex = TextureLoader::loadTexture("Textures\\sand.bmp");


		for (int x = 0; x <= size; x++)
		{
			cd[x] = x;
		}





		genMap(size);
}




Terrain::~Terrain(void)
{

}

void Terrain::genMap(int mapSize)
{
	
	TerrainGenerator gen = TerrainGenerator();
	gen.generateTerrain(landsc);

	calcSLopes(64);
}



void Terrain::calcSLopes(int size)
{
		for(int x = 0; x < size; x++)
		{
			for(int y = 0; y < size ; y++)
			{
				slope[x][y] = SlopeHelper::getSlopeValue(x,y , landsc);
			}
		}
}



void Terrain::getTexture(GLfloat color[3], int x , int y)
{
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;


	if(slope[x][y] < 0.4f)
	{
		if( landsc[x][y] < 0.2f)
		{
		//	color[0] = 0.9f; color[1] = 0.95; color[2] = 0.37;
			glBindTexture(GL_TEXTURE_2D, sandTex);
		}
		else
		{
		//	color[0] = 0.17; color[1] = 0.5f; color[2] = 0.03;
			glBindTexture(GL_TEXTURE_2D, grassTex);
		}
	}
	else if (slope[x][y] < 1.0f)
	{
		if( landsc[x][y] < 0.2f)
		{
		//	color[0] = 0.4; color[1] = 0.28; color[2] = 0.18;
			glBindTexture(GL_TEXTURE_2D, rockTex);
		}
		else if ( landsc[x][y]  > 4)
		{
		//	color[0] = 0.4; color[1] = 0.28; color[2] = 0.18;
			glBindTexture(GL_TEXTURE_2D, grassTex);
		}
		else
		{
		//	color[0] = 0; color[1] = 1; color[2] = 0;
			glBindTexture(GL_TEXTURE_2D, rockTex);
		}
	}
	else 
	{
		//color[0] = 0.4; color[1] = 0.28; color[2] = 0.18;
		glBindTexture(GL_TEXTURE_2D, rockTex);
	}

			if( landsc[x][y] >= 4 )
		{
			glBindTexture(GL_TEXTURE_2D, rockTex);
			}

		//	glBindTexture(GL_TEXTURE_2D, rockTex);

}



void Terrain::getColor(GLfloat color[3], float value)
{
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;


	float max = 40;
	float min = 0.5f;


	if( value < min)
	{
		float perc = (value / (min - -1));

		float r =   ((0.9 - 0.788) * (1-perc)) + 0.788;
		float g = ((0.93- 0.87) * (1-perc)) + 0.87;
		float b = ((0.7 - 0.61) * (1-perc)) + 0.61;

		color[0] = r; color[1] = g; color[2] = b; // grass MIN
		//color[0] = 0.8; color[1] = 0.9; color[2] = 0.7; // grass MIN

		//color[0] = 0.22; color[1] = 0.49; color[2] = 0.22; // grass MAX
	}
	else if ( (value >= min) && (value < 2))
	{
		float perc = (value / (2 - min));

		float r =   ((0.8 - 0.2) * (1-perc)) + 0.2;
		float g = ((0.9 - 0.49) * (1-perc)) + 0.49;
		float b = ((0.7 - 0.22) * (1-perc)) + 0.22;

		color[0] = r; color[1] = g; color[2] = b; // grass MIN
		//color[0] = 0.8; color[1] = 0.9; color[2] = 0.7; // grass MIN

		//color[0] = 0.22; color[1] = 0.49; color[2] = 0.22; // grass MAX
	}
	else if ( value < 4)
	{
		color[0] = 0.4; color[1] = 0.28; color[2] = 0.18; // rock
	}
	else 
	{
		color[0] = 0.4; color[1] = 0.4; color[2] = 0.4; // rock
	}


}








void Terrain::display(void)
{
	int size = 64;


	glPushMatrix(); 

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	//glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	


	
	int i, j;
   float v1[3],v2[3],out[3];
   glColor3f(1.0, 1.0, 1.0);
   v1[0] = cd[1];
   v1[1] = 0;
   v2[0] = 0;
   v2[1] = cd[1];
   for (j = 0; j < size; j++)
      for (i = 0; i < size; i++) {
		  v1[2] = landsc[i+1][j] - landsc[i][j];
          v2[2] = landsc[i][j+1] - landsc[i][j];
		  NormalHelper::normcrossprod(v1,v2,out);
		 // NormalHelper::getSurfaceNormal(out, out, v1, v2);
		  normals[i][j][0] = -out[0];
		  normals[i][j][1] = -out[1];
		  normals[i][j][2] = -out[2];
	  }
   for (j = 0; j < size; j++) {
	  normals[size][j][0] = normals[size-1][j][0];
      normals[size][j][1] = normals[size-1][j][1];
      normals[size][j][2] = normals[size-1][j][2];
	  }
   for (i = 0; i < size; i++) {
	  normals[i][size][0] = normals[i][size-1][0];
	  normals[i][size][1] = normals[i][size-1][1];
	  normals[i][size][2] = normals[i][size-1][2];
	  }
   normals[size][size][0] = normals[size-1][size-1][0];
   normals[size][size][1] = normals[size-1][size-1][1];
   normals[size][size][2] = normals[size-1][size-1][2];


   for (j = 0; j < size; j++)
      for (i = 0; i < size; i++) {
		
		  GLfloat color[3] = {0,0,0};
		  getTexture(color , i,j);
	//	glColor3f(color[0], color[1], color[2]);
		  
		  glBegin(GL_POLYGON);

		//  GLfloat color[3] = {0,0,0};
		//  getColor(color , i,j);
		 
		//  glColor3f(color[0], color[1], color[2]);

		  drawVertex(i,j);

	//glColor3f(0.1, 0.1, 0.1);	  glNormal3fv(&normals[i][j][0]);   glTexCoord2f(0,0);glVertex3f(cd[i],cd[j],-landsc[i][j]);
		  
	//glColor3f(0.1, 0.1, 1.0);	  glNormal3fv(&normals[i+1][j][0]);  glTexCoord2f(1,0); glVertex3f(cd[i+1],cd[j],-landsc[i+1][j]);
		  
	//glColor3f(1.0, 0.1, 0.1);	  glNormal3fv(&normals[i+1][j+1][0]); glTexCoord2f(1,1); glVertex3f(cd[i+1],cd[j+1],-landsc[i+1][j+1]);
		  
	//glColor3f(0.1, 1.0, 0.1);	  glNormal3fv(&normals[i][j+1][0]); glTexCoord2f(0,1); glVertex3f(cd[i],cd[j+1],-landsc[i][j+1]);
		  glEnd();

	  }
      glEnd();  


	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}






void Terrain::drawVertex(int i , int j)
{
	GLfloat color[3] = {0,0,0};
	

	getColor(color , landsc[i][j]);
	glColor3f(color[0], color[1], color[2]);	  glNormal3fv(&normals[i][j][0]);   glTexCoord2f(0,0);glVertex3f(cd[i],cd[j],-landsc[i][j]);
		  
	getColor(color , landsc[i+1][j]);
	glColor3f(color[0], color[1], color[2]);	  glNormal3fv(&normals[i+1][j][0]);  glTexCoord2f(1,0); glVertex3f(cd[i+1],cd[j],-landsc[i+1][j]);
		  
	getColor(color , landsc[i+1][j+1]);
	glColor3f(color[0], color[1], color[2]);	  glNormal3fv(&normals[i+1][j+1][0]); glTexCoord2f(1,1); glVertex3f(cd[i+1],cd[j+1],-landsc[i+1][j+1]);
		  
	getColor(color , landsc[i][j+1]);
	glColor3f(color[0], color[1], color[2]);	  glNormal3fv(&normals[i][j+1][0]); glTexCoord2f(0,1); glVertex3f(cd[i],cd[j+1],-landsc[i][j+1]);

}