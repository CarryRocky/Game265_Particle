#pragma once

#include "particleConfigue.h"
#include "aParticleSystem.h"

class AParticleManager
{	
	public:
		AParticleManager();
		~AParticleManager();

		AParticleSystem* addNewSystem(Vector2f);
		void increaseAllMaxNum();
		void decreaseAllMaxNum();
		void drawWholeSystem(RenderWindow*);
		void updateWholeSystem(float);

		void deleteAllSystems();

		void addNewSystemBySceneId(int);

		int getWholeParticleNum();
	private:
		vector<AParticleSystem*> childSystems;
		vector<Texture> textureArray;
		int curTextIndex;

		int getInitAngleByPos(Vector2f);
};