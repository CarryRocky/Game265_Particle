#pragma once

#include "SFMLHeader.h"

#include "linearStrategy.h"
#include "easeInStrategy.h"
#include "easeOutStrategy.h"
#include "sinStrategy.h"

class AParticle : public RectangleShape
{
	private:
		float velocity;
		float angle;
		float lifetime;
		Vector2f direction;
		bool isDeadBool;

		float curTime;

		StrategyBase *sizeStrategy;
		StrategyBase *velocityStrategy;
		StrategyBase *rotationStrategy;

		StrategyBase* chooseStrategy(int,float,float);

		float randomFloat(float,float);
	public:
		AParticle(float,Vector2f);
		~AParticle();
		
		void setSizeStrategy(int,float,float);
		void setVelocityStrategy(int, float,float);
		void setRotationStrategy(int, float,float);

		void updateParticle(float);
		bool isDead()
		{
			return isDeadBool;
		}
};