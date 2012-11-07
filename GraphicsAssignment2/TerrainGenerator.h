#include <freeglut.h>

#pragma once
class TerrainGenerator
{
public:
	TerrainGenerator(void);
	~TerrainGenerator(void);
	void generateTerrain(float mapGrid[65][65]);
	void errodeCoast(float map[65][65]);
	void smoothTerrain(int passes , float map[65][65]);
	GLuint peakX;
	GLuint peakY;
	GLuint peakZ;
private:
	GLfloat interpolate(GLfloat a, GLfloat b, float coefficient);
};

