/*		Foilage Generator
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to generate a foilage over the island
 * This generator will populate the island with foilage based on specified values
 *
 *
 * Last Updated: 09/11/2012
*/

#include "FoilageGenerator.h"
#include "LTree.h"
#include "Shrub.h"
#include "Terrain.h"
#include "TextureLoader.h"

FoilageGenerator::FoilageGenerator(void)
{
}


FoilageGenerator::~FoilageGenerator(void)
{
}


void FoilageGenerator::generateForest(LTree trees[800], Terrain terrain)
{
	GLuint treeTexID = TextureLoader::loadTexture("Textures\\palm.bmp");

	for(int i = 0 ; i < 800 ; i++)// reset trees
	{
		int x = 0;
		int y = -4;
		int z = 0;
		trees[i] = LTree(x,y,z ,treeTexID);
	}

	int treeCounter = 0;

	for(int x = 10 ; x < 50 ; x++)
	{
		for(int y =10; y< 50 ; y++)
		{
			if( (isPeak(x,y,terrain) == false) && ( treeCounter < 800))
			{
				if(( terrain.heightPoints[x][y] < 2.0f) && ( terrain.heightPoints[x][y] > 0.7f) )
				{
					if( (terrain.textures[x][y] == terrain.grassTex) || ( terrain.heightPoints[x][y] < 4.0f) )
					{
						for(int i = 0 ; i < 2 ; i++) // Provide spead out over one tile
						{
							GLfloat xPos = x + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
							GLfloat zPos = y + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
							GLfloat yPos = terrain.heightPoints[x][y];
							trees[treeCounter] = LTree(xPos,yPos,zPos ,treeTexID);
							treeCounter++;
						}
					}
				}
			}
		}
	}

}

void FoilageGenerator::generateShrubs(Shrub shrubs[800] , Terrain terrain)
{
	GLuint shrubTexID = TextureLoader::loadTexture("Textures\\shrub.bmp");

	for(int i = 0 ; i < 800 ; i++)
	{
		int x = 0;
		int y = -4;
		int z = 0;
		shrubs[i] = Shrub(x,y,z ,shrubTexID);
	}

	int shrubCounter = 0;

	for(int x = 10 ; x < 50 ; x++)
	{
		for(int y =10; y< 50 ; y++)
		{
			if( (isPeak(x,y,terrain) == false) && ( shrubCounter < 800))
			{
				if(( terrain.heightPoints[x][y] < 2.0f) && ( terrain.heightPoints[x][y] > 0.4f) )
				{
					for(int i = 0 ; i < 5 ; i++)
					{
						float xPos = x + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
						float zPos = y + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
						float yPos = terrain.heightPoints[x][y];

						shrubs[shrubCounter] = Shrub(xPos,yPos,zPos ,shrubTexID);
						shrubCounter++;
					}
				}
			}
		}
	}

}


bool FoilageGenerator::isPeak(int x , int  y , Terrain terrain)
{
	if ( (x  < 10) || ( x > 50))
	{
		return false;
	}

	if ( (y  < 10) || ( y > 50))
	{
		return false;
	}

	int xT = x;
	int yT = y;

	for(int iX = -4; iX < 4 ; iX++)
	{
		for(int iY = -4; iY < 4 ; iY++)
		{
			if( (xT +iX == terrain.peakX) && (yT + iY == terrain.peakZ))
			{
				return true;
			}
		}
	}
	
	return false;
}