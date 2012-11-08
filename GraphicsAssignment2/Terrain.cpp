/*		Terrain CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to render terrain from an array of vertexes
 * It also generates a coloured 
 * 
 * Last Updated: 07/11/2012
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

	generateMap(size);
}


Terrain::~Terrain(void)
{

}

void Terrain::generateMap(int mapSize)
{
	TerrainGenerator gen = TerrainGenerator();
	gen.generateTerrain(landsc);

	peakX = gen.peakX;
	peakY = gen.peakY;
	peakZ = gen.peakZ;

	calculateSlopes(mapSize);
	calculateColors(mapSize);
	calculateTextures(mapSize);
	calculateNormals(mapSize);
}


void Terrain::calculateColors(int size)
{


}


void Terrain::calculateTextures(int size)
{
	for(int x = 0 ; x < 64 ; x++)
	{
		for(int y =0; y< 64 ; y++)
		{
			textures[x][y] = getTextureValue( x ,  y);
		}
	}

}


void Terrain::calculateNormals(int size)
{


}


void Terrain::calculateSlopes(int size)
{
	for(int x = 0; x < size; x++)
	{
		for(int y = 0; y < size ; y++)
		{
			slope[x][y] = SlopeHelper::getSlopeValue(x,y , landsc);
		}
	}
}

void Terrain::getTexture(int x , int y)
{
	if(slope[x][y] < 0.4f)
	{
		if( landsc[x][y] < 0.2f)
		{
			glBindTexture(GL_TEXTURE_2D, grassTex);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, grassTex);
		}
	}
	else if (slope[x][y] < 1.0f)
	{
		if( landsc[x][y] < 0.2f)
		{
			glBindTexture(GL_TEXTURE_2D, rockTex);
		}
		else if ( landsc[x][y]  > 4)
		{
			glBindTexture(GL_TEXTURE_2D, grassTex);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, rockTex);
		}
	}
	else 
	{
		glBindTexture(GL_TEXTURE_2D, rockTex);
	}

	if( landsc[x][y] >= 4 )
	{
		glBindTexture(GL_TEXTURE_2D, rockTex);
	}
}



GLfloat Terrain::getTextureValue(int x , int y)
{





	if(slope[x][y] < 0.4f)
	{
		if( landsc[x][y] < 0.2f)
		{
			return sandTex;
		}
		else
		{
			return grassTex;
		}
	}
	else if (slope[x][y] < 1.0f)
	{
		if( landsc[x][y] < 0.2f)
		{
			return rockTex;
		}
		else if ( landsc[x][y]  > 4)
		{
			return grassTex;
		}
		else
		{
			return rockTex;
		}
	}
	else 
	{
		return rockTex;
	}

	if( landsc[x][y] >= 4 )
	{
		return rockTex;
	}
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

		color[0] = r; color[1] = g; color[2] = b; 
	}
	else if ( (value >= min) && (value < 2))
	{
		float perc = (value / (2 - min));

		float r =   ((0.8 - 0.2) * (1-perc)) + 0.2;
		float g = ((0.9 - 0.49) * (1-perc)) + 0.49;
		float b = ((0.7 - 0.22) * (1-perc)) + 0.22;

		color[0] = r; color[1] = g; color[2] = b; 
	}
	else if ( value < 4)
	{
		color[0] = 0.4; color[1] = 0.28; color[2] = 0.18; 
	}
	else 
	{
		color[0] = 0.4; color[1] = 0.4; color[2] = 0.4; 
	}

}


void Terrain::display(void)
{
	int size = 64;

	glPushMatrix(); 

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);

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
		  getTexture( i,j);
		  
		  glBegin(GL_POLYGON);

		  drawVertex(i,j);

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