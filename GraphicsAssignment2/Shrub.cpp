/*		Shrub CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class generates a shrub 
 * Uses alpha blending to get grass blades
 * 
 * Last Updated: 08/11/2012
*/

#include "Shrub.h"
#include "TextureLoader.h"

#include <windows.h>	
#include <stdio.h>	
#include <freeglut.h>
#include <math.h>


Shrub::Shrub()
{

}


Shrub::Shrub(GLfloat x , GLfloat y , GLfloat z , GLuint texID)
{
	xPosition = x;
	yPosition = y;
	zPosition = z;
	xAngle = 0; 
	yAngle = 0;
	zAngle = 0;
	scale = 0.3f;
	level = 1;
	
	texName = texID;

	xAngle = (rand()% 30) - (rand()% 30);
	zAngle = (rand()% 360);
	zAngle = (rand()% 30) - (rand()% 30);
	height = (rand()% 5) + 3;

	leaves = (rand()% 4) +1;
}


Shrub::~Shrub(void)
{
}



void Shrub::display(void)
{
	glPushMatrix(); 
	glTranslated(-15 ,0 ,-15);

	glScaled(0.5 ,0.5 ,0.5);

	glPushMatrix(); 

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);

	tree();

	glPopMatrix();
	glPopMatrix();

	
	glDisable(GL_TEXTURE_2D);
}


void Shrub::tree()
{
	//Palms
	glColor3f(1, 1, 1);

	glBegin(GL_TRIANGLES);	
	glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);	 glVertex3f( 0.0f, 0.8 , 0.6f);		
	glTexCoord2f(1.0, 0.0);	 glVertex3f(-1.0f, 0.2 , 0.0f);		
	glTexCoord2f(0.0, 1.0);	 glVertex3f( 1.0f, 0.14 , 0.0f);		
	glEnd();	


	
		glBegin(GL_TRIANGLES);		
		glNormal3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0, 0.0); glVertex3f( 0.0f, 0.4 , -0.6f);		
		glTexCoord2f(1.0, 0.0);	 glVertex3f(-1.0f, 0.3 , 0.0f);		
		glTexCoord2f(0.0, 1.0);	 glVertex3f( 1.0f, 0.12 , 0.0f);		
		glEnd();
	
		glBegin(GL_TRIANGLES);
		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);	 glVertex3f( -0.6f, 0.9 , -0.0f);	
		glTexCoord2f(1.0, 0.0);	 glVertex3f(0.0f, 0.14 , -1.0f);		
		glTexCoord2f(0.0, 1.0);	 glVertex3f( 0.0f, 0.11 , 1.0f);		
		glEnd();
	
		glBegin(GL_TRIANGLES);	
		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);	 glVertex3f( 0.6f, 0.6 , -0.0f);	
		glTexCoord2f(1.0, 0.0);	 glVertex3f(0.0f, 0.14 , 1.0f);		
		glTexCoord2f(0.0, 1.0);	 glVertex3f( 0.0f, 0.12 , -1.0f);		
		glEnd();
}


void Shrub::setAngle(GLfloat xAngleT , GLfloat yAngleT , GLfloat zAngleT)
{
	xAngle = xAngleT;
	yAngle = yAngleT;
	zAngle = zAngleT;
}

void Shrub::setPosition(GLfloat xPositionT , GLfloat yPositionT , GLfloat zPositionT)
{
	xPosition = xPositionT;
	yPosition = yPositionT;
	zPosition = zPositionT;
}

