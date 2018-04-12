#pragma once

#include "strategyBase.h"

class LinearStrategy : public StrategyBase
{
	public:
		LinearStrategy(float pStartV, float pChangeV) : 
			StrategyBase(pStartV,pChangeV) {}
		
		float executeStrategy(float x)
		{
			return (startValue + changeValue * x);
		}
};