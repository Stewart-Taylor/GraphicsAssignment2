/*		Tree CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class generates random palm tree
 * It also provides a crude shadow method
 * 
 * Last Updated: 07/11/2012
*/


#include "LTree.h"
#include "TextureLoader.h"

#include <windows.h>	
#include <stdio.h>	
#include <freeglut.h>
#include <math.h>



LTree::LTree()
{

}


LTree::LTree(GLfloat x , GLfloat y , GLfloat z , GLuint texID)
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


LTree::~LTree(void)
{
}



void LTree::display(void)
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


void LTree::tree()
{
	glColor3f(1, 1, 1);
               
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0, -1.0);  glVertex3f(0.1,height,0.1);
	glTexCoord2f(1.0,  1.0);   glVertex3f(-0.1,height,0.1);
	glTexCoord2f(-1.0,  1.0);  glVertex3f(-0.1,-0.1,0.1);
	glTexCoord2f(-1.0, -1.0);    glVertex3f(0.1,-0.1,0.1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, -1.0);   glVertex3f(0.1,height,0.1);
	glTexCoord2f(1.0,  1.0);   glVertex3f(0.1,-0.1,0.1);
	glTexCoord2f(-1.0,  1.0);  glVertex3f(0.1,-0.1,-0.1);
	glTexCoord2f(-1.0, -1.0);  glVertex3f(0.1,height,-0.1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0, -1.0);	glVertex3f(0.1,height,-0.1);
	glTexCoord2f(1.0,  1.0);	glVertex3f(0.1,-0.1,-0.1);
	glTexCoord2f(-1.0,  1.0);   glVertex3f(-0.1,-0.1,-0.1);
	glTexCoord2f(-1.0, -1.0);   glVertex3f(-0.1,height,-0.1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, -1.0);	glVertex3f(-0.1,height,0.1);
	glTexCoord2f(1.0,  1.0);    glVertex3f(-0.1,height,-0.1);
	glTexCoord2f(-1.0,  1.0);   glVertex3f(-0.1,-0.1,-0.1);
	glTexCoord2f(-1.0, -1.0);   glVertex3f(-0.1,-0.1,0.1);
	glEnd();


	
	//Palms

	glBegin(GL_TRIANGLES);	
	glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);	glColor3f(0.22, 0.85, 0.1); glVertex3f( 0.0f, -0.8 + height, 0.6f);		
	glTexCoord2f(1.0, 0.0);	glColor3f(0.22, 0.25, 0.1); glVertex3f(-1.0f, 0.2 + height, 0.0f);		
	glTexCoord2f(0.0, 1.0);	glColor3f(0.32, 0.45, 0.1); glVertex3f( 1.0f, 0.14 + height, 0.0f);		
	glEnd();	

	if(leaves >=2)
	{
		glBegin(GL_TRIANGLES);		
		glNormal3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);	glColor3f(0.22, 0.85, 0.1); glVertex3f( 0.0f, -0.4 + height, -0.6f);		
		glTexCoord2f(1.0, 0.0);	glColor3f(0.22, 0.25, 0.1); glVertex3f(-1.0f, 0.3 + height, 0.0f);		
		glTexCoord2f(0.0, 1.0);	glColor3f(0.32, 0.45, 0.1); glVertex3f( 1.0f, 0.12 + height, 0.0f);		
		glEnd();
	}

	if(leaves >=3)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);	glColor3f(0.22, 0.85, 0.1); glVertex3f( -0.6f, -0.9 + height, -0.0f);	
		glTexCoord2f(1.0, 0.0);	glColor3f(0.22, 0.25, 0.1); glVertex3f(0.0f, 0.14 + height, -1.0f);		
		glTexCoord2f(0.0, 1.0);	glColor3f(0.32, 0.45, 0.1); glVertex3f( 0.0f, 0.11 + height, 1.0f);		
		glEnd();
	}

	if(leaves >=4)
	{
		glBegin(GL_TRIANGLES);	
		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);	glColor3f(0.22, 0.85, 0.1); glVertex3f( 0.6f, -0.6 + height, -0.0f);	
		glTexCoord2f(1.0, 0.0);	glColor3f(0.22, 0.25, 0.1); glVertex3f(0.0f, 0.14 + height, 1.0f);		
		glTexCoord2f(0.0, 1.0);	glColor3f(0.32, 0.45, 0.1); glVertex3f( 0.0f, 0.12 + height, -1.0f);		
		glEnd();
	}


}


void LTree::setAngle(GLfloat xAngleT , GLfloat yAngleT , GLfloat zAngleT)
{
	xAngle = xAngleT;
	yAngle = yAngleT;
	zAngle = zAngleT;
}

void LTree::setPosition(GLfloat xPositionT , GLfloat yPositionT , GLfloat zPositionT)
{
	xPosition = xPositionT;
	yPosition = yPositionT;
	zPosition = zPositionT;
}

