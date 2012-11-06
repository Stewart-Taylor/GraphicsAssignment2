#include <freeglut.h>
#include <math.h>
#include <minmax.h>

#pragma once
class Terrain
{

public:
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	Terrain(void);
	Terrain(int sizeT);
	~Terrain(void);
		void drawVertex(int x , int y);
	void display(void);
	void genMap(int size);
	GLfloat interpolate(GLfloat a, GLfloat b, float coefficient);
	void getTexture(GLfloat color[3],int x , int y);
	void getColor(GLfloat color[3], float value);
	void calcSLopes(int size);
	float getSlopeValue(int x , int y);
	GLfloat getGradientValue(GLfloat x, GLfloat y);
	GLfloat getTopLeftSlope(int x, int y);
	GLfloat getTopMiddleSlope(int x, int y);
	GLfloat getTopRightSlope(int x, int y);
	GLfloat getMiddleLeftSlope(int x, int y);
	GLfloat getMiddleRightSlope(int x, int y);
	GLfloat getBottomLeftSlope(int x, int y);
	GLfloat getBottomMiddleSlope(int x, int y);
	GLfloat getBottomRightSlope(int x, int y);

private:
	GLfloat scale;
	GLuint texName;
	GLuint slices;
	GLfloat radius;
	GLfloat length;


	 GLuint sandTex;
	 GLuint grassTex;
	 GLuint rockTex;
};
