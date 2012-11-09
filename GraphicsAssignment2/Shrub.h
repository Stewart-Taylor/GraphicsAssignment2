#include <freeglut.h>


#pragma once
class Shrub
{
public:
	Shrub();
	Shrub(GLfloat x , GLfloat y , GLfloat z , GLuint texID);
	~Shrub(void);
	void display(void);
	bool active;
private:
	void drawShrub(void);
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat scale;
	GLuint texName;
};
