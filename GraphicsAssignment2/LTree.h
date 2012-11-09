#include <freeglut.h>

#pragma once
class LTree
{
public:
	LTree();
	LTree(GLfloat x , GLfloat y , GLfloat z , GLuint texID);
	~LTree(void);
	void display(void);
	bool active;
private:
	void drawTree(void);
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLuint leaves;
	GLfloat scale;
	GLuint texName;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	GLfloat height;
};
