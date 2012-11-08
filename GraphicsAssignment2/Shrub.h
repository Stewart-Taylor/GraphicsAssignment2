#include <freeglut.h>


#pragma once
class Shrub
{
public:
	int level;
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	Shrub();
	Shrub(GLfloat x , GLfloat y , GLfloat z , GLuint texID);
	~Shrub(void);
	void display(void);
	void tree();
	void setAngle(GLfloat xAngleT , GLfloat yAngleT , GLfloat zAngleT);
	void setPosition(GLfloat xPositionT , GLfloat yPositionT , GLfloat zPositionT);
	void spin(GLfloat speed);
private:
	GLuint leaves;
	GLfloat scale;
	GLuint texName;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	GLfloat height;
};
