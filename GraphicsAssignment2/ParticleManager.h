#include <freeglut.h>

#pragma once
class ParticleManager
{
public:
	ParticleManager(void);
	ParticleManager(int x , int y , int z);
	~ParticleManager(void);
	void display(void);
	void update(void);
	void reset(int x , int y , int z);
private:
	void createParticle(int i);
	GLuint texName;
	GLuint emitterX;
	GLuint emitterY;
	GLuint emitterZ;
	GLfloat windX;
	GLfloat windZ;
};

