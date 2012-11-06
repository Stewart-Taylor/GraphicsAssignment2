#include <freeglut.h>
#pragma once
class LTree
{
public:
	int level;
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	LTree();
	LTree(GLfloat x , GLfloat y , GLfloat z );
	~LTree(void);
	void display(void);
	void displayShadow(void);
	void tree(int level, int leaves);
	void setAngle(GLfloat xAngleT , GLfloat yAngleT , GLfloat zAngleT);
	void setPosition(GLfloat xPositionT , GLfloat yPositionT , GLfloat zPositionT);
	void spin(GLfloat speed);
private:
	GLfloat scale;
	GLuint texName;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
};
