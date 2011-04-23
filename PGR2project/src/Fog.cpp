#include "Fog.h"


Fog::Fog(void)
{
}


Fog::~Fog(void)
{
}
void Fog::init()
{
	GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// Storage For Three Types Of Fog
	GLuint fogfilter= 0;							// Which Fog To Use
	//GLfloat fogColor[4]= {125.f/255.f, 145.f/255.f, 149.f/255.f,1.f};
	GLfloat fogColor[4]= {0.03f, 0.07f, 0.14f, 1.f};
	glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.008f);				// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
	glFogf(GL_FOG_START, 500.0f);				// Fog Start Depth
	glFogf(GL_FOG_END, 1000.0f);				// Fog End Depth
}

void Fog::turnOn(){
	glEnable(GL_FOG);
}

void Fog::turnOff(){
	glDisable(GL_FOG);
}
