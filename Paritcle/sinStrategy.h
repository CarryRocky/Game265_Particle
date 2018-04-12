#pragma once

#include "strategyBase.h"
#include "SFMLHeader.h"

class SinStrategy : public StrategyBase
{
public:
	SinStrategy(float pStartV, float pChangeV) :
		StrategyBase(pStartV, pChangeV) {}

	float executeStrategy(float x)
	{
		return (changeValue * sin(PI * x) + startValue);
	}
};