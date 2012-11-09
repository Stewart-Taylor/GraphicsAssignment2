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
	GLfloat landsc[64+1][64+1];
	GLfloat slope[64+1][64+1];
	GLfloat cd[64+1];
	GLfloat normals[64+1][64+1][3];
	GLfloat colors[64+1][64+1][3];
	GLfloat textures[64+1][64+1];
	GLuint grassTex;
private:
	void calculateColors(int size);
	void calculateTextures(int size);
	void calculateNormals(int size);
	GLfloat getTextureValue(int x , int y);
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	GLfloat scale;
	GLuint sandTex;
	GLuint rockTex;
};
