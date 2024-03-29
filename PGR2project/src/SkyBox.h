#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "SceneModel.h"
#include "Camera.h"
#include "Light.h"

static const string appendices[] = {
	"north",
	"west",
	"east",
	"south",
	"up",
	"down"
};

class SkyBox :
	public SceneModel
{
public:
	SkyBox(void);
	SkyBox(TextureManager *texManager, ShaderManager *shManager, string filename);
	~SkyBox(void);

	void draw();

	virtual void drawForLOD(); 

	void init();

	void update(double time);

	void loadFromFiles(string filename);
	
	void connectShadowMap(int shadowMapTMID);
	
	vector<int> textureIds;
	Camera* p_activeCamera;
	Light*	p_light;
};

#endif

