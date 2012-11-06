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
	xAngle = 90; // straight up
	yAngle = 0;
	zAngle = 0;
	scale = 1;
	level = 1;
//	texName = TextureLoader::loadTexture("Textures\\steel.bmp");
}


LTree::~LTree(void)
{
}



void LTree::display(void)
{
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
	glDisable(GL_TEXTURE_2D);
}


void LTree::tree(int level, int leaves)
{
	char lstring[20] = "F[+F][-F]\0";


	   int current;
   current = 0;
   while (lstring[current]) {
      switch (lstring[current]) {
         case 'F':
            if (level == 0) {
               glColor3f(0.45, 0.32, 0.26);
               
	glBegin(GL_POLYGON);
	//glNormal3f(normal1[0], normal1[1], normal1[2]);
	glTexCoord2f(1.0, -1.0);  glVertex3f(0.1,1.0,0.1);
	glTexCoord2f(1.0,  1.0);   glVertex3f(-0.1,1.0,0.1);
	glTexCoord2f(-1.0,  1.0);  glVertex3f(-0.1,-0.1,0.1);
	glTexCoord2f(-1.0, -1.0);    glVertex3f(0.1,-0.1,0.1);
	glEnd();

	glBegin(GL_POLYGON);
	//glNormal3f(normal2[0], normal2[1], normal2[2]);
	glTexCoord2f(1.0, -1.0);   glVertex3f(0.1,1.0,0.1);
	glTexCoord2f(1.0,  1.0);   glVertex3f(0.1,-0.1,0.1);
	glTexCoord2f(-1.0,  1.0);  glVertex3f(0.1,-0.1,-0.1);
	glTexCoord2f(-1.0, -1.0);  glVertex3f(0.1,1.0,-0.1);
	glEnd();

	glBegin(GL_POLYGON);
	//glNormal3f(normal3[0], normal3[1], normal3[2]);
	glTexCoord2f(1.0, -1.0);	glVertex3f(0.1,1.0,-0.1);
	glTexCoord2f(1.0,  1.0);	glVertex3f(0.1,-0.1,-0.1);
	glTexCoord2f(-1.0,  1.0);   glVertex3f(-0.1,-0.1,-0.1);
	glTexCoord2f(-1.0, -1.0);   glVertex3f(-0.1,1.0,-0.1);
	glEnd();

	glBegin(GL_POLYGON);
	//glNormal3f(normal4[0], normal4[1], normal4[2]);
	glTexCoord2f(1.0, -1.0);	glVertex3f(-0.1,1.0,0.1);
	glTexCoord2f(1.0,  1.0);    glVertex3f(-0.1,1.0,-0.1);
	glTexCoord2f(-1.0,  1.0);   glVertex3f(-0.1,-0.1,-0.1);
    glTexCoord2f(-1.0, -1.0);   glVertex3f(-0.1,-0.1,0.1);
	glEnd();

	glBegin(GL_POLYGON);
	//glNormal3f(normal5[0], normal5[1], normal5[2]);
	glTexCoord2f(1.0, -1.0);	glVertex3f(0.1,1.0,0.1);
	glTexCoord2f(1.0,  1.0);    glVertex3f(0.1,1.0,-0.1);
	glTexCoord2f(-1.0,  1.0);   glVertex3f(-0.1,1.0,-0.1);
    glTexCoord2f(-1.0, -1.0);   glVertex3f(-0.1,1.0,0.1);
	glEnd();

	glBegin(GL_POLYGON);
	//glNormal3f(normal6[0], normal6[1], normal6[2]);
	glTexCoord2f(1.0, -1.0);    glVertex3f(0.1,-0.1,0.1);
	glTexCoord2f(1.0,  1.0);    glVertex3f(-0.1,-0.1,0.1);
	glTexCoord2f(-1.0,  1.0);    glVertex3f(-0.1,-0.1,-0.1);
	glTexCoord2f(-1.0, -1.0);   glVertex3f(0.1,-0.1,-0.1);
	glEnd();





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
               glTranslatef(0.0,1.0,0.0);
            }
            else { 
               if ((lstring[current+1] == ']') ||
                   (lstring[current+1] == 0)) LTree::tree(level-1, leaves);
               else
                  tree(level - 1,0);
            }
            break;
         case '[':
            glPushMatrix();
            glScalef(0.707,0.707,1.0);
            break;
         case ']':
            glPopMatrix();
            break;
         case '+':
            glRotatef(-20.0,0.0,0.0,1.0);
            break;
         case '-':
            glRotatef(20.0,0.0,0.0,1.0);
            break;
         default:
            break;
      }
      current++;
   }


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

