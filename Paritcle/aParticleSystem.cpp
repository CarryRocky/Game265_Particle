#include "aParticleSystem.h"

AParticleSystem::AParticleSystem(Vector2f pBornPos, float pVelocity, Vector2f pAngleRange, 
									Texture* pTexture, int pMaxNum, Vector2f pSize)
{
	bornPoint = pBornPos;
	velocity = pVelocity;
	emitAngleRange = pAngleRange;
	texture = pTexture;
	maxNum = pMaxNum;
	size = pSize;

	changeType = NO_CHANGE;
	strategyType = NO_S;
	strategyPA = 0;
	strategyPB = 0;
}

AParticleSystem::~AParticleSystem()
{
	int childSize = childParcitle.size();
	for (int i = childSize - 1; i >= 0; i--)
	{
		delete childParcitle[i];
		childParcitle.erase(childParcitle.begin() + i);
	}
}

void AParticleSystem::setAStrategy(int pChangeType,int pStrategyType,float pA,float pB)
{
	changeType = pChangeType;
	strategyType = pStrategyType;
	strategyPA = pA;
	strategyPB = pB;
}

void AParticleSystem::createNewParticle()
{
	AParticle *newParticle = new AParticle(velocity,emitAngleRange);
	newParticle->setPosition(bornPoint);
	newParticle->setTexture(texture);
	newParticle->setSize(size);
	newParticle->setOrigin(Vector2f(size.x/2,size.y/2));

	setParticleStrategy(newParticle);

	childParcitle.push_back(newParticle);
}

void AParticleSystem::setParticleStrategy(AParticle* pParticle)
{
	if (changeType == NO_CHANGE || strategyType == NO_S)
	{
		return;
	}
	
	if (changeType == CHANGE_V)
	{
		pParticle->setVelocityStrategy(strategyType, strategyPA, strategyPB);
	}
	else if (changeType == CHANGE_S)
	{
		pParticle->setSizeStrategy(strategyType,strategyPA,strategyPB);
	}
	else if (changeType == CHANGE_R)
	{
		pParticle->setRotationStrategy(strategyType,strategyPA,strategyPB);
	}
}

void AParticleSystem::updateParticles(float dt)
{
	if (childParcitle.size() < maxNum)
	{
		createNewParticle();
	}

	int curParticleNum = childParcitle.size();

	for (int i = curParticleNum - 1;i >= 0;i--)
	{
		childParcitle[i]->updateParticle(dt);
		if (childParcitle[i]->isDead())
		{
			delete childParcitle[i];
			childParcitle.erase(childParcitle.begin() + i);
		}
	}
}

void AParticleSystem::drawAllParticles(RenderWindow *window)
{
	for (int i = 0; i < childParcitle.size(); i++)
	{
		window->draw(*childParcitle[i]);
	}
}