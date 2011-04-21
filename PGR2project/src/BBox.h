#ifndef _BBOX_H
#define _BBOX_H

#include "utils.h"
#include "settings.h"
#include "../common/models/cube.h"



class BBox
{
public:
	BBox(void);
	BBox(v3 &_minCorner, v3 &_maxCorner, v3 &_color = v3(1.0,0.f,0.f)); 
	~BBox(void);
	
	void draw();

	v3 sizes;
	v3 center;
	v3 minCorner;
	v3 color;
	GLenum drawMode;
};



#endif
