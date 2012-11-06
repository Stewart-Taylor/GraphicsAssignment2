/*		TableSurface CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * Generates a white plane with graident and surface normals.
 * 
 * Last Updated: 24/10/2012
*/

#include "Plane.h"
#include "TextureLoader.h"

#include <stdio.h>	
#include <freeglut.h>

Plane::Plane(void)
{
	xPosition = 0;
	yPosition = -0.9;
	zPosition = 0;
	xAngle = -90;
	yAngle = 0;
	zAngle = 0;
	scale = 800;

	texName = TextureLoader::loadTexture("Textures\\water.bmp");
}


Plane::~Plane(void)
{
}


void Plane::display(void)
{
	glPushMatrix(); 

	

	//	glEnable(GL_TEXTURE_2D); 
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
//	glBindTexture(GL_TEXTURE_2D, texName);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
		glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);


	glBegin(GL_POLYGON);
	glNormal3f(0.0 , 1.0 , 0.0);
	glColor3f( 0.0 ,0.58, 0.5 );	
	 	glVertex3f(  0.5, -0.5, 0.0 );      
	 		glVertex3f(  0.5,  0.5, 0.0 );     
		glVertex3f( -0.5,  0.5, 0.0 );      
	 		glVertex3f( -0.5, -0.5, 0.0 );      
	glEnd();

	glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
}	