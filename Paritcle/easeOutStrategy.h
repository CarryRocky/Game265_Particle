#pragma once

#include "strategyBase.h"

class EaseOutStrategy : public StrategyBase
{
	public:
		EaseOutStrategy(float pStartV, float pChangeV) :
			StrategyBase(pStartV, pChangeV) {}

		float executeStrategy(float x)
		{
			return (-changeValue * x * (x - 2) + startValue);
		}
};