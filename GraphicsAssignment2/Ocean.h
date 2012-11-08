#include <freeglut.h>

#pragma once
class Ocean
{

public:
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	Ocean(void);
	Ocean(int sizeT);
	~Ocean(void);
	void drawVertex(int x , int y);
	void display(void);
	void genMap(int size);
	void getColor(GLfloat color[4], int x , int y);
	void smooth(int passes , float map[65][65]);
	void update();
	GLfloat timer;
	int limit;
private:
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat scale;
	double distanceT(double dX0, double dY0, double dX1, double dY1);
};
