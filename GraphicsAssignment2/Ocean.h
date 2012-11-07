#include <freeglut.h>

#pragma once
class Ocean
{

public:
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
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
	int timer;
	int limit;
private:
	GLfloat scale;
	GLuint texName;
	GLuint slices;
	GLfloat radius;
	GLfloat length;
	int midX;
	int midY;
	float spread;
	double distanceT(double dX0, double dY0, double dX1, double dY1);
	 GLuint sandTex;
	 GLuint grassTex;
	 GLuint rockTex;
};
