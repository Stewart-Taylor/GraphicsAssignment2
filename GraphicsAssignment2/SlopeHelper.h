#include <freeglut.h>

#pragma once
class SlopeHelper
{
public:
	SlopeHelper(void);
	~SlopeHelper(void);
	static	float getSlopeValue(int x , int y, GLfloat landsc[65][65]);
private:
	static int size;
	static GLfloat getGradientValue(GLfloat x, GLfloat y);
	static GLfloat getTopLeftSlope(int x, int y, GLfloat landsc[65][65]);
	static GLfloat getTopMiddleSlope(int x, int y, GLfloat landsc[65][65]);
	static GLfloat getTopRightSlope(int x, int y, GLfloat landsc[65][65]);
	static GLfloat getMiddleLeftSlope(int x, int y, GLfloat landsc[65][65]);
	static	GLfloat getMiddleRightSlope(int x, int y, GLfloat landsc[65][65]);
	static	GLfloat getBottomLeftSlope(int x, int y, GLfloat landsc[65][65]);
	static	GLfloat getBottomMiddleSlope(int x, int y, GLfloat landsc[65][65]);
	static	GLfloat getBottomRightSlope(int x, int y , GLfloat landsc[65][65]);
};

