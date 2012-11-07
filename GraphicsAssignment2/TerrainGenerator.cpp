/*		Terrain Generator
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to generate a volcanic terrain island. 
 * Uses a customer designed algorithm to generate the island
 *
 *
 * Last Updated: 07/11/2012
*/

#include "TerrainGenerator.h"

#include <windows.h>	
#include <stdio.h>	
#include <freeglut.h>
#include <math.h>
#include <time.h>

TerrainGenerator::TerrainGenerator(void)
{
}


TerrainGenerator::~TerrainGenerator(void)
{
}


void TerrainGenerator::generateTerrain(float mapGrid[65][65])
{
	float tempLand[64 + 1][64 + 1];
	int mapSize = 64;

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
				tempLand[i][j] = -2 -rSize ;
			}
			else
			{
				tempLand[i][j] = ((rand()%2)) ;		
			}
		}
	}
		
	smoothTerrain(1 , tempLand );

	int vPointX = mapSize /2;
	int vPointY = mapSize /2;

	vPointX += (rand()%10) - (rand()%10) ;
	vPointY += (rand()%10) - (rand()%10) ;



	

	int craterSize = (rand()%3 + 3);
	int poolSize = craterSize - 2;
	float height =  (rand()%6 + 3);
	float poolHeight = height - (rand()%craterSize)  -4;
	int outerSize = ( (rand()%10) + craterSize);

	peakX = vPointX - (craterSize/2) +1;
	peakZ = vPointY - (craterSize/2) +1;
	peakY  = height -1;

	int heightJitter = 3;

	if( poolHeight <= 1 )
	{
		poolHeight = 2;
	}

	int jitter = ( (rand()%4) + 1);


	for(int x = -outerSize; x < outerSize; x++)
	{
		for(int y = -outerSize; y < outerSize; y++)
		{
			float distance = sqrt( pow( (float)((vPointX+x) - vPointX),2)+ (pow( (float)((vPointY+y) - vPointY),2)));


			float val = (distance /(outerSize+craterSize + 3));
			val = (1- val);
			tempLand[vPointX + x ][vPointY + y] = (height * val) -(rand()%heightJitter ) ;
		}
	}


	for(int x = -craterSize; x < craterSize; x++)
	{
		for(int y = -craterSize; y < craterSize; y++)
		{
			tempLand[vPointX + x ][vPointY + y] = height + (rand()%heightJitter );
		}
	}
		

	for(int x = -poolSize; x < poolSize; x++)
	{
		for(int y = -poolSize; y < poolSize; y++)
		{
			tempLand[vPointX + x ][vPointY + y] = 1 ;
		}
	}
		
	smoothTerrain(1 , tempLand);


	for (int i = 0; i <= mapSize; i++)
	{
		for (int j = 0; j <= mapSize; j++)
		{
			int rSize = ((rand()%20)+2);

			if(  (i < rSize) || (j < rSize) || (i > mapSize-rSize - 1) || ( j > mapSize-rSize))
			{
				//	tempLand[i][j] = -2 -rSize ;
					tempLand[i][j] = -8;
			}
		}
	}

	smoothTerrain(1 , tempLand);
		
	errodeCoast(tempLand);

	for (int x = 0; x <= 64; x++)
	{
		for (int y = 0; y <= 64; y++)
		{
			mapGrid[x][y] = tempLand[x][y];
		}
	}

}


void TerrainGenerator::errodeCoast(float map[65][65])
{
	int size = 64;

	for(int x = 2; x < size -2; x++)
	{
		for(int y = 2; y < size -2; y++)
		{
			if( map[x][y] <=1)
			{
				float valCof = 0.1f;
				map[x][y] =	interpolate(map[x][y], 0,valCof );  
			}
		}
	}
}

 GLfloat TerrainGenerator::interpolate(GLfloat a, GLfloat b, float coefficient)
{
    return a + coefficient * (b - a);
}



 void TerrainGenerator::smoothTerrain(int passes , float map[65][65])
{
	int size = 64;

	for(int i =0 ; i < passes ; i++)
	{

		for(int x = 2; x < size -2; x++)
		{
			for(int y = 2; y < size -2; y++)
			{
				float total = 0;
				total += map[x][y] ;
				total += map[x-1][y-1] ;
				total += map[x][y-1] ;
				total += map[x+1][y] ;
				total += map[x-1][y] ;
				total += map[x+1][y] ;
				total += map[x-1][y+1] ;
				total += map[x][y+1] ;
				total += map[x+1][y+1] ;

				float avg = total / 9;
				map[x][y] = avg; 
			}
		}
	}

 }
