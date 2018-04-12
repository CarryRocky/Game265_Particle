#pragma once

class StrategyBase
{
	public:
		StrategyBase(float pStartV, float pChangeV) : 
			startValue(pStartV) , changeValue(pChangeV) {}
		
		virtual float executeStrategy(float) = 0;
	protected:
		float startValue;
		float changeValue;
};