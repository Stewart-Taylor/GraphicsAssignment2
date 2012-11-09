/*		Particle Manager
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to generate the smoke from a volcano
 * It also simulates wind
 *
 * Last Updated: 09/11/2012
*/

#include "ParticleManager.h"
#include "TextureLoader.h"
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

}

ParticleManager::ParticleManager(int x , int y , int z)
{
	emitterX = x;
	emitterY = y;
	emitterZ = z;

	for(int i = 0 ; i < 1000 ; i++)
	{
		createParticle(i);
		particles[i].timer = (rand()%990);
	}

	texName = TextureLoader::loadTexture("Textures\\smoke.bmp");
}

ParticleManager::~ParticleManager(void)
{
}

void ParticleManager::createParticle(int i)
{
	 particles[i].x = emitterX + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
	 particles[i].y = emitterY  - (float)rand()/((float)RAND_MAX/2);
	 particles[i].z = emitterZ + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
	 particles[i].timer = (rand()%100); 
	 particles[i].limit = 1000;
	 particles[i].direction[0] = (float)rand()/((float)RAND_MAX/0.003f) - (float)rand()/((float)RAND_MAX/0.003f) ;
	 particles[i].direction[1] = (float)rand()/((float)RAND_MAX/0.02f) ;
	 particles[i].direction[2] = (float)rand()/((float)RAND_MAX/0.003f) - (float)rand()/((float)RAND_MAX/0.003f) ;
	 particles[i].scale = (float)rand()/((float)RAND_MAX/0.9f) ;
	 particles[i].active = true;
	 particles[i].color[0] = 0;
	 particles[i].color[1] = 0;
	 particles[i].color[2] = 0;
	 particles[i].color[3] = 1;
}


void ParticleManager::display(void)
{
	glEnable(GL_COLOR_BUFFER_BIT );
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
 
	glPushMatrix(); 

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTranslated(-15 ,0 ,-15);
	glTranslated(0,0 ,0);
	glScaled(0.5 ,0.5 ,0.5);

	
	for(int i = 0; i<1000 ;i++)
	{
		glPushMatrix(); 

		glTranslated(particles[i].x ,particles[i].y ,particles[i].z);
		glScaled(particles[i].scale ,particles[i].scale ,particles[i].scale);

		glBegin (GL_QUADS);
		glColor4f( particles[i].color[0] ,particles[i].color[1], particles[i].color[2] , particles[i].color[3] );	
		glTexCoord2d (0, 0);  glVertex3f (-1, -1, 0);
		glTexCoord2d (1, 0);  glVertex3f (1, -1, 0);
		glTexCoord2d (1, 1);  glVertex3f (1, 1, 0);
		glTexCoord2d (0, 1);  glVertex3f (-1, 1, 0);
		glEnd();

		glPopMatrix();
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}


void ParticleManager::reset(int x , int y , int z)
{
	emitterX = x;
	emitterY = y;
	emitterZ = z;

	windX = (float)rand()/((float)RAND_MAX/0.1f) - (float)rand()/((float)RAND_MAX/0.1f);
	windZ = (float)rand()/((float)RAND_MAX/0.1f) - (float)rand()/((float)RAND_MAX/0.1f);

	for(int i = 0; i<1000 ;i++)
	{
		particles[i].x = emitterX + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
		particles[i].y = emitterY ;
		particles[i].z = emitterZ + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
		particles[i].scale = 0.3;
	}
}


void ParticleManager::update(void)
{
	for(int i = 0; i<1000 ;i++)
	{
		particles[i].timer++;

		if( particles[i].timer < particles[i].limit)
		{
			float perc = particles[i].timer / particles[i].limit;

			if(particles[i].y < emitterY + 3)
			{
				particles[i].color[0] =  0.37f;
				particles[i].color[1] = 0.21f; 
				particles[i].color[2] = 0.1f; 
			}
			else if( (particles[i].y > 15) &&  (particles[i].y < 20))
			{
				float perc2 = particles[i].y /80.0f;
				particles[i].x -= perc2 * windX;
				particles[i].z -= perc2 * windZ;
			}
			else 
			{
				float perc2 = particles[i].y /60.0f;
				particles[i].x -=  perc2  * windX;
				particles[i].z -=  perc2  * windZ;
			}

			particles[i].x += particles[i].direction[0];
			particles[i].y += particles[i].direction[1];
			particles[i].z += particles[i].direction[2];
			
			if(particles[i].y > 10)
			{
				particles[i].color[0] = (1-perc);
				particles[i].color[1] =  (1-perc);
				particles[i].color[2] = (1-perc);
			}
			
			particles[i].color[3] = (1-perc);
			particles[i].scale += 0.0008f;
		}
		else
		{
			createParticle(i);
		}
	}
}