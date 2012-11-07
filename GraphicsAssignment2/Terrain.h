#include <freeglut.h>
#include <math.h>

#pragma once
class Terrain
{

public:
	Terrain(void);
	Terrain(int sizeT);
	~Terrain(void);
	void drawVertex(int x , int y);
	void display(void);
	void generateMap(int size);
	void getTexture(int x , int y);
	void getColor(GLfloat color[3], float value);
	void calculateSlopes(int size);
	float getSlopeValue(int x , int y);
	GLuint peakX;
	GLuint peakY;
	GLuint peakZ;
private:
	void calculateColors(int size);
	void calculateTextures(int size);
	void calculateNormals(int size);
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	GLfloat scale;
	GLuint sandTex;
	GLuint grassTex;
	GLuint rockTex;
};
