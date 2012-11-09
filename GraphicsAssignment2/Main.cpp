/*	Procedural Generation
 *	AUTHOR: STEWART TAYLOR
 *	DATE STARTED: 31/10/2012
 *------------------------------------
 * This program is part of the Graphics modules second assignment.
 * It demonstrates the use of generating 3D objects procedurally. 
 * 
 * The main class is used as a controller and is also used to set the program up.
 *
 * Last Updated: 10/11/2012
*/

#define _USE_MATH_DEFINES


#include "Camera.h"
#include "Main.h"
#include "SkyBox.h"
#include "Plane.h"
#include "ShadowHelper.h"
#include "LTree.h"
#include "Terrain.h"
#include "Ocean.h"
#include "Shrub.h"
#include "ParticleManager.h"
#include "TextureLoader.h"

#include <math.h>
#include <stdlib.h>
#include <freeglut.h>
#include <fstream>
#include <iostream>


Camera camera = Camera();

SkyBox skybox;
Plane plane;
Ocean ocean;
LTree tree;
Terrain terrain ;
ParticleManager particleManager;
LTree trees[800];
Shrub shrubs[800];


GLfloat specular = 1.0;
GLfloat diffuse = 0.5;
GLfloat shiny = 50.0;

GLfloat light_position[] = { 56.0 , 20.0 ,9.0 , 1.0};
GLfloat mat_specular[] = { specular, specular, specular, 1.0 };
GLfloat mat_diffuse[] = { diffuse, diffuse, 0.5, 1.0 };
GLfloat mat_shininess[] = { shiny };


bool isPeak(int x , int y)
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


void generateForest()
{
	GLuint treeTexID = TextureLoader::loadTexture("Textures\\palm.bmp");

	for(int i = 0 ; i < 800 ; i++)
	{
		int x = ((rand()%20) - (rand()%20));
		int y = -4;
		int z = ((rand()%20) - (rand()%20));
		trees[i] = LTree(x,y,z ,treeTexID);

	}

	int treeCounter = 0;

	for(int x = 10 ; x < 50 ; x++)
	{
		for(int y =10; y< 50 ; y++)
		{
			if( isPeak(x,y) == false)
			{
			if(( terrain.heightPoints[x][y] < 2.0f) && ( terrain.heightPoints[x][y] > 0.7f) )
			{
				if( (terrain.textures[x][y] == terrain.grassTex) || ( terrain.heightPoints[x][y] < 4.0f) )
				{
					if(treeCounter < 800)
					{
						for(int i = 0 ; i < 2 ; i++)
						{

							float xPos = x + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
							float zPos = y + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
							float yPos = terrain.heightPoints[x][y];

							trees[treeCounter] = LTree(xPos,yPos,zPos ,treeTexID);
							treeCounter++;
						}
					}
				}
			}
			}
		}
	}

}



void generateShrubs()
{
	GLuint treeTexID = TextureLoader::loadTexture("Textures\\shrub.bmp");

	for(int i = 0 ; i < 800 ; i++)
	{
		int x = ((rand()%20) - (rand()%20));
		int y = -4;
		int z = ((rand()%20) - (rand()%20));
		shrubs[i] = Shrub(x,y,z ,treeTexID);

	}

	int treeCounter = 0;

	for(int x = 10 ; x < 50 ; x++)
	{
		for(int y =10; y< 50 ; y++)
		{
			if( isPeak(x,y) == false)
			{
			if(( terrain.heightPoints[x][y] < 2.0f) && ( terrain.heightPoints[x][y] > 0.4f) )
			{
					if(treeCounter < 800)
					{
						for(int i = 0 ; i < 5 ; i++)
						{

							float xPos = x + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
							float zPos = y + (float)rand()/((float)RAND_MAX/0.5f) - (float)rand()/((float)RAND_MAX/0.5f) ;
							float yPos = terrain.heightPoints[x][y];

							shrubs[treeCounter] = Shrub(xPos,yPos,zPos ,treeTexID);
							treeCounter++;
						}
					}
				
			}
			}
		}
	}

}

void generateMap()
{
	terrain.generateMap(64);
	ocean.genMap(64);
	particleManager.reset(terrain.peakX,terrain.peakY,terrain.peakZ);
	generateForest();
	generateShrubs();
}


void setObjects(void)
{
	skybox =  SkyBox();
	plane = Plane();
	terrain = Terrain(64);
	particleManager = ParticleManager(0 , 0 , 0); 
	ocean = Ocean(64);
	tree.setAngle(0,90,0);
	
	generateMap();
}

void init (void) 
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glCullFace(GL_FRONT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	setObjects();
}


void displayFog(void)
{
	GLfloat density = 0.002f;
	GLfloat fogColor[4] = {0.70f, 0.7f, 0.7f, 1.0f};
	glFogi (GL_FOG_MODE, GL_LINEAR);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 100.0f);
	glFogf(GL_FOG_END, 600.0f); 
    glEnable(GL_FOG);
}


void display (void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel (GL_SMOOTH);

	displayFog();

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	camera.update();

	glDisable(GL_CULL_FACE);
	skybox.display();
	glEnable(GL_CULL_FACE);
	
	plane.display();
	terrain.display();
	ocean.display();
	
	glDisable(GL_CULL_FACE);
	particleManager.display();

	for(int i = 0 ; i < 800 ; i++)
	{
		if(trees[i].yPosition != -4) // only draws assigned trees - 4 is default not assigned 
		{
			trees[i].display();
			shrubs[i].display();
		}
	}


	
	glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1600.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void keyboard (unsigned char key, int x, int y)
{
	key = tolower(key); // Allows Caps Lock to still work

	camera.keyboardControl(key , x , y);

	if (key=='k'){light_position[1] += 1;}
	if (key=='i'){light_position[1] -= 1;}
	if (key=='j'){light_position[0] += 1;}
	if (key=='l'){light_position[0] -= 1;}
	if (key=='u'){light_position[2] += 1;}
	if (key=='o'){light_position[2] -= 1;}

	if (key=='g'){generateMap();}
}

void mouseUpdate(int x , int y)
{
	//camera.mouseControl(x,y);
}

void idle(void)
{
	ocean.update();
	particleManager.update();
	glutPostRedisplay();
}

void printInfo()
{
	std::cout << "	3D Procedural Generation" << std::endl << std::endl;
	std::cout << "	Created by Stewart Taylor" << std::endl << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CONTROLS" << std::endl;
	std::cout << std::endl;
	std::cout << "CAMERA" << std::endl;
	std::cout << " W,A,S,D  - Move Camera" << std::endl;
	std::cout << " Q,E - Look Left/Right" << std::endl;
	std::cout << " R,F - Move Camera Up/Down " << std::endl;
	std::cout << " Z,X - Tilt Camera Up/Down" << std::endl;
	std::cout << std::endl;
	std::cout << "Main " << std::endl;
	std::cout << " G - Generate Island" << std::endl;
	std::cout << std::endl;
	std::cout << "LIGHT " << std::endl;
	std::cout << " U,I,K,L,J - Move Light Source" << std::endl;
	std::cout << std::endl;
}

int main (int argc, char **argv)
{
	printInfo();
    glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600); 
    glutInitWindowPosition (200, 100);
    glutCreateWindow ("3D Procedural Generation"); 
    init (); 
    glutDisplayFunc (display); 
    glutIdleFunc (idle); 
    glutReshapeFunc (reshape);
	glutPassiveMotionFunc(mouseUpdate); 
    glutKeyboardFunc (keyboard); 
    glutMainLoop (); 
    return 0;
}
