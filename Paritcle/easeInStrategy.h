#pragma once

#include "strategyBase.h"

class EaseInStrategy : public StrategyBase
{
	public:
		EaseInStrategy(float pStartV, float pChangeV) :
			StrategyBase(pStartV, pChangeV) {}

		float executeStrategy(float x)
		{
			return (startValue + changeValue * x * x);
		}
};