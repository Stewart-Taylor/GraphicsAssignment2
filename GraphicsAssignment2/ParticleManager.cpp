#include "ParticleManager.h"
#include <freeglut.h>




struct Particle
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat timer;
	GLfloat limit;
	GLfloat direction[3];
	GLfloat scale;
	bool active;
	GLfloat color[4];

};


Particle particles[1000];


ParticleManager::ParticleManager(void)
{

	for(int i = 0 ; i < 1000 ; i++)
	{
		createParticle(i);
		particles[i].timer = (rand()%990);
	}


}


ParticleManager::~ParticleManager(void)
{
}



void ParticleManager::createParticle(int i)
{
		particles[i].x = 0;
	 particles[i].y = 0;
	 particles[i].z = 0;
	 particles[i].timer = (rand()%100); 
	 particles[i].limit = 1000;
	 particles[i].direction[0] = (float)rand()/((float)RAND_MAX/0.003f) - (float)rand()/((float)RAND_MAX/0.003f) ;
	 particles[i].direction[1] = (float)rand()/((float)RAND_MAX/0.02f) ;
	 particles[i].direction[2] = (float)rand()/((float)RAND_MAX/0.003f) - (float)rand()/((float)RAND_MAX/0.003f) ;
	 particles[i].scale = (float)rand()/((float)RAND_MAX/0.05f) ;
	 particles[i].active = true;
	 particles[i].color[0] = 0; //(float)rand()/((float)RAND_MAX/0.9f);
	 particles[i].color[1] = 0; //(float)rand()/((float)RAND_MAX/0.9f);
	 particles[i].color[2] = 0; // (float)rand()/((float)RAND_MAX/0.9f);
	 particles[i].color[3] = 1;
}







void ParticleManager::display(void)
{
	


	glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glTranslated(xPosition ,yPosition ,zPosition);
	//glRotatef(xAngle, 1.0, 0.0, 0.0);
	//glRotatef(yAngle, 0.0, 1.0, 0.0);
//	glRotatef(zAngle, 0.0, 0.0, 1.0);
//	glTranslated(0,0 ,0);
//	glScaled(scale ,scale ,scale);

	
	for(int i = 0; i<1000 ;i++)
	{
			glPushMatrix(); 

			glMatrixMode(GL_MODELVIEW);

		glTranslated(particles[i].x ,particles[i].y ,particles[i].z);
		glTranslated(0,0 ,0);
		glScaled(particles[i].scale ,particles[i].scale ,particles[i].scale);


		glBegin(GL_POLYGON);
		glColor4f( particles[i].color[0] ,particles[i].color[1], particles[i].color[2] , particles[i].color[3] );	
	 	glVertex3f(  0.5, -0.5, 0.0 );      
	 	glVertex3f(  0.5,  0.5, 0.0 );     
		glVertex3f( -0.5,  0.5, 0.0 );      
	 	glVertex3f( -0.5, -0.5, 0.0 );   
		glEnd();

		glPopMatrix();
	}

	
}


void ParticleManager::update(void)
{

	for(int i = 0; i<1000 ;i++)
	{
		particles[i].timer++;

		if( particles[i].timer < particles[i].limit)
		{
			particles[i].x += particles[i].direction[0];
			particles[i].y += particles[i].direction[1];
			particles[i].z += particles[i].direction[2];
			particles[i].color[0] += 0.001f;
			particles[i].color[1] += 0.001f;
			particles[i].color[2] += 0.001f;
			particles[i].color[3] -= 0.001f;
			particles[i].scale += 0.0002f;
		}
		else
		{
			createParticle(i);
		}
	}

}