/*		Cylinder CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class generates a textured cylinder.
 * It also provides a crude shadow method
 * 
 * Last Updated: 24/10/2012
*/

#define _USE_MATH_DEFINES // Allows me to use PI constant 

#include "LTree.h"
#include "TextureLoader.h"

#include <windows.h>	
#include <stdio.h>	
#include <freeglut.h>
#include <math.h>







LTree::LTree()
{

}


LTree::LTree(GLfloat x , GLfloat y , GLfloat z)
{
	xPosition = x;
	yPosition = y;
	zPosition = z;
	xAngle = 0; // straight up
	yAngle = 0;
	zAngle = 0;
	scale = 0.3f;
	level = 1;
	texName = TextureLoader::loadTexture("Textures\\steel.bmp");



	height = (rand()%12);

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


	tree(level,1);



	

	glPopMatrix();

	glPopMatrix();

	

	glDisable(GL_TEXTURE_2D);
}


void LTree::tree(int level, int leaves)
{


     glColor3f(0.74, 0.6, 0.4);
               
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








                  

				glBegin(GL_TRIANGLES);	
				glNormal3f(0.0f, 1.0f, 1.0f);
				glColor3f(0.22, 0.85, 0.1); glVertex3f( 0.0f, -0.8 + height, 0.6f);		// Top
				glColor3f(0.22, 0.25, 0.1); glVertex3f(-1.0f, 0.2 + height, 0.0f);		// Bottom Left
				glColor3f(0.32, 0.45, 0.1); glVertex3f( 1.0f, 0.14 + height, 0.0f);		// Bottom Right
				glEnd();	

				glBegin(GL_TRIANGLES);		
				glNormal3f(0.0f, 1.0f, 1.0f);
				glColor3f(0.22, 0.85, 0.1); glVertex3f( 0.0f, -0.4 + height, -0.6f);		// Top
				glColor3f(0.22, 0.25, 0.1); glVertex3f(-1.0f, 0.3 + height, 0.0f);		// Bottom Left
				glColor3f(0.32, 0.45, 0.1); glVertex3f( 1.0f, 0.12 + height, 0.0f);		// Bottom Right
				glEnd();	

				glBegin(GL_TRIANGLES);
				glNormal3f(1.0f, 1.0f, 0.0f);
				glColor3f(0.22, 0.85, 0.1); glVertex3f( -0.6f, -0.9 + height, -0.0f);		// Top
				glColor3f(0.22, 0.25, 0.1); glVertex3f(0.0f, 0.14 + height, -1.0f);		// Bottom Left
				glColor3f(0.32, 0.45, 0.1); glVertex3f( 0.0f, 0.11 + height, 1.0f);		// Bottom Right
				glEnd();


				glBegin(GL_TRIANGLES);	
				glNormal3f(1.0f, 1.0f, 0.0f);
				glColor3f(0.22, 0.85, 0.1); glVertex3f( 0.6f, -0.6 + height, -0.0f);		// Top
				glColor3f(0.22, 0.25, 0.1); glVertex3f(0.0f, 0.14 + height, 1.0f);		// Bottom Left
				glColor3f(0.32, 0.45, 0.1); glVertex3f( 0.0f, 0.12 + height, -1.0f);		// Bottom Right
				glEnd();


                 // glBegin(GL_POLYGON);
                 //  glVertex3f(0.0,height -2,0.2);
				//  glVertex3f(0.0,height -1,1.5);
				//  glVertex3f(0.0,height -2,1.5);
				  
				  //glVertex3f(0.5,-0.1 + height -2,0.0);
                  //   glVertex3f(0.0,0.5+ height -2,0.0);
                   //  glVertex3f(-0.5,-0.1+ height -2,0.0);
                   //  glVertex3f(-0.5,1.4+ height -2,0.0);
                   //  glVertex3f(-0.1,1.0+ height -2,0.0);
                   //  glVertex3f(0.1,1.0+ height -2,0.0);
                   //  glVertex3f(0.5,1.4+ height -2,0.0);
               //   glEnd();

				  /*
				   glBegin(GL_POLYGON);
                     glVertex3f(0.0,2.0 + height -2,0.5);
                     glVertex3f(0.0,2.5+ height -2,0.0);
                     glVertex3f(-0.0,2.0+ height -2,-0.5);
                     glVertex3f(-0.0,1.4+ height -2,-0.5);
                     glVertex3f(-0.0,1.0+ height -2,-0.1);
                     glVertex3f(0.0,1.0+ height -2,0.1);
                     glVertex3f(0.0,1.4+ height -2,0.5);
                  glEnd();
				  */

	/*
	if (leaves && ((lstring[current+1] == ']') || 
                   (lstring[current+1] == 0))) {
                  glColor3f(0.24, 0.6, 0.21);
                  glBegin(GL_POLYGON);
                     glVertex3f(0.5,2.0,0.0);
                     glVertex3f(0.0,2.5,0.0);
                     glVertex3f(-0.5,2.0,0.0);
                     glVertex3f(-0.5,1.4,0.0);
                     glVertex3f(-0.1,1.0,0.0);
                     glVertex3f(0.1,1.0,0.0);
                     glVertex3f(0.5,1.4,0.0);
                  glEnd();
               }
 */


}









void LTree::drawLeaf(int level, int leaves)
{
	int height = 4;
		glPushMatrix(); 


	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(80, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);

		glColor3f(0.24, 0.6, 0.21);
        glBegin(GL_TRIANGLES); 
          glNormal3f(-0.1, 0, 0.25); 
          glVertex3f(0, height, 0); 
          glVertex3f(0.25, height +0.25, 0.1); 
          glVertex3f(0, height +0.5, 0); 

          glNormal3f(0.1, 0, 0.25); 
          glVertex3f(0, height, 0); 
          glVertex3f(0, height +0.5, 0); 
          glVertex3f(-0.25, height +0.25, 0.1); 
        glEnd(); 



				  glPopMatrix();

	/*
	if (leaves && ((lstring[current+1] == ']') || 
                   (lstring[current+1] == 0))) {
                  glColor3f(0.24, 0.6, 0.21);
                  glBegin(GL_POLYGON);
                     glVertex3f(0.5,2.0,0.0);
                     glVertex3f(0.0,2.5,0.0);
                     glVertex3f(-0.5,2.0,0.0);
                     glVertex3f(-0.5,1.4,0.0);
                     glVertex3f(-0.1,1.0,0.0);
                     glVertex3f(0.1,1.0,0.0);
                     glVertex3f(0.5,1.4,0.0);
                  glEnd();
               }
 */


}

void LTree::displayShadow(void)
{


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

