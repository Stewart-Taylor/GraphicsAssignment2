#include "LTree.h"
#include "Shrub.h"
#include "Terrain.h"

#pragma once
class FoilageGenerator
{
public:
	FoilageGenerator(void);
	~FoilageGenerator(void);
	void generateForest(LTree trees[800] , Terrain terrain);
	void generateShrubs(Shrub shrubs[800] , Terrain terrain);
private:
	bool isPeak(int x , int y, Terrain terrain);
};

