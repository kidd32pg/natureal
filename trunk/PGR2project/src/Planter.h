#ifndef _PLANTER_H
#define _PLANTER_H

#include "settings.h"
#include "Terrain.h"
#include "../common/Vector2.h"
#include "Vegetation.h"
#include <ctime>

class Planter
{
public:
	Planter(Terrain *_terrain);
	~Planter(void);
	void init(	Vegetation* _prototype, 
				Vegetation*	_growth,
				float		_height_min,
				float		_height_max,
				float		_minDist,
				int			_res_x,
				int			_res_y);
	void plantVegetationCount(int _count);
	void add();
	void erase();
	void bakeVBO();
	int plantVegetation(Vegetation* prototype, Vegetation* growth);
	
	int desiredCount;
	int count;
	float height_min;
	float height_max;
	float minDist;
	int res_x;
	int res_y;

	vector<v3> candidates;
	vector<v3> realPositions;
	Vegetation *prototype;
	Vegetation *growth;
	Terrain *terrain;	
};

#endif

