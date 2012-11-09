#include <freeglut.h>
#include <math.h>

#pragma once
class Terrain
{

public:
	Terrain(void);
	Terrain(int sizeT);
	~Terrain(void);
	void display(void);
	void generateMap(int size);
	GLuint peakX;
	GLuint peakY;
	GLuint peakZ;
	GLfloat heightPoints[64+1][64+1];
	GLfloat textures[64+1][64+1];
	GLuint grassTex;
private:
	void drawVertex(int x , int y);
	void getTexture(int x , int y);
	void getColor(GLfloat color[3], float value);
	void calculateSlopes(int size);
	void calculateColors(int size);
	void calculateTextures(int size);
	void calculateNormals(int size);
	GLfloat getSlopeValue(int x , int y);
	GLfloat getTextureValue(int x , int y);
	GLfloat slope[64+1][64+1];
	GLfloat cd[64+1];
	GLfloat normals[64+1][64+1][3];
	GLfloat colors[64+1][64+1][3];
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
