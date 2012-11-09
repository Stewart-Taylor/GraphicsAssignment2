/*		Terrain CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to render terrain from an array of vertexes
 * It also generates colored vertex information
 * 
 * Last Updated: 09/11/2012
*/

#include "Terrain.h"
#include "TextureLoader.h"
#include "TerrainGenerator.h"
#include "SlopeHelper.h"
#include "NormalHelper.h"
#include <freeglut.h>

Terrain::Terrain()
{

}

Terrain::Terrain(int size)
{
	xPosition = -15;
	yPosition = 0;
	zPosition = -15;
	xAngle = 90;
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
	gen.generateTerrain(heightPoints);

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
	for(int x = 0 ; x < size ; x++)
	{
		for(int y =0; y< size ; y++)
		{
			 getColor(colors[x][y] , heightPoints[x][y]);
		}
	}
}


void Terrain::calculateTextures(int size)
{
	for(int x = 0 ; x < size ; x++)
	{
		for(int y =0; y< size ; y++)
		{
			textures[x][y] = getTextureValue( x ,  y);
		}
	}
}


void Terrain::calculateNormals(int size)
{
	int i, j;
	float v1[3],v2[3],out[3];
	v1[0] = cd[1];
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = cd[1];
	for (j = 0; j < size; j++)
      for (i = 0; i < size; i++) {
		  v1[2] = heightPoints[i+1][j] - heightPoints[i][j];
          v2[2] = heightPoints[i][j+1] - heightPoints[i][j];
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
}


void Terrain::calculateSlopes(int size)
{
	for(int x = 0; x < size; x++)
	{
		for(int y = 0; y < size ; y++)
		{
			slope[x][y] = SlopeHelper::getSlopeValue(x,y , heightPoints);
		}
	}
}

void Terrain::getTexture(int x , int y)
{
	glBindTexture(GL_TEXTURE_2D, textures[x][y]);
}


GLfloat Terrain::getTextureValue(int x , int y)
{
	if(slope[x][y] < 0.4f)
	{
		if( heightPoints[x][y] < 0.2f)
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
		if( heightPoints[x][y] < 0.2f)
		{
			return rockTex;
		}
		else if ( heightPoints[x][y]  > 4)
		{
			return grassTex;
		}
	}

	return rockTex;
}


void Terrain::getColor(GLfloat color[3], GLfloat value)
{
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;

	GLfloat max = 40;
	GLfloat min = 0.5f;

	if( value < min)
	{
		float perc = (value / (min - -1));

		GLfloat r =   ((0.9 - 0.788) * (1-perc)) + 0.788;
		GLfloat g = ((0.93- 0.87) * (1-perc)) + 0.87;
		GLfloat b = ((0.7 - 0.61) * (1-perc)) + 0.61;

		color[0] = r; color[1] = g; color[2] = b; 
	}
	else if ( (value >= min) && (value < 2))
	{
		GLfloat perc = (value / (2 - min));

		GLfloat r =   ((0.8 - 0.2) * (1-perc)) + 0.2;
		GLfloat g = ((0.9 - 0.49) * (1-perc)) + 0.49;
		GLfloat b = ((0.7 - 0.22) * (1-perc)) + 0.22;

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

   for (int j = 10; j < 54; j++)
      for (int i = 10; i < 54; i++) 
	  {
		  getTexture( i,j);
		  glBegin(GL_POLYGON);
		  drawVertex(i,j);
		  glEnd();
	  }
      glEnd();  

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void Terrain::drawVertex(int i , int j)
{
	glColor3f(colors[i][j][0], colors[i][j][1], colors[i][j][2]);				glNormal3fv(&normals[i][j][0]);		glTexCoord2f(0,0);glVertex3f(cd[i],cd[j],-heightPoints[i][j]);
	glColor3f(colors[i+1][j][0], colors[i+1][j][1], colors[i+1][j][2]);			glNormal3fv(&normals[i+1][j][0]);	glTexCoord2f(1,0); glVertex3f(cd[i+1],cd[j],-heightPoints[i+1][j]);
	glColor3f(colors[i+1][j+1][0], colors[i+1][j+1][1], colors[i+1][j+1][2]);	glNormal3fv(&normals[i+1][j+1][0]); glTexCoord2f(1,1); glVertex3f(cd[i+1],cd[j+1],-heightPoints[i+1][j+1]);
	glColor3f(colors[i][j+1][0], colors[i][j+1][1], colors[i][j+1][2]);			glNormal3fv(&normals[i][j+1][0]);	glTexCoord2f(0,1); glVertex3f(cd[i],cd[j+1],-heightPoints[i][j+1]);
}