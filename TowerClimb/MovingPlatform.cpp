#include "MovingPlatform.h"
#include "AssetManager.h"
#include "VectorHelper.h"

MovingPlatform::MovingPlatform(sf::Vector2f newPos1, sf::Vector2f newPos2)
	: Platform()
	, SPEED(100)
	, POS1(newPos1)
	, POS2(newPos2)
	, targetPoint(&POS2)
	, velocity(0, 0)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/MovingPlatform.png"));

	sf::Vector2f vectorToNewTarget = *targetPoint - GetPosition();
	vectorToNewTarget = VectorHelper::Normalise(vectorToNewTarget);
	velocity = vectorToNewTarget * SPEED;
}

void MovingPlatform::Update(sf::Time frameTime)
{
	float frameSeconds = frameTime.asSeconds();

	sf::Vector2f newPos = GetPosition();

	sf::Vector2f toMove = velocity * frameSeconds;
	float squareDistToMove = VectorHelper::SquareMagnitude(toMove);

	sf::Vector2f vectorToTarget = *targetPoint - newPos;
	float squareDistToTarget = VectorHelper::SquareMagnitude(vectorToTarget);

	if (squareDistToMove >= squareDistToTarget)
	{
		//we arrived 

		//set us to be the target point
		newPos = *targetPoint;

		//change our target point to be the other one
		if (targetPoint == &POS1)
		{
			targetPoint = &POS2;
		}
		else
		{
			targetPoint = &POS1;
		}

	}
	else
	{
		newPos += toMove;
	}

	SetPosition(newPos);
}

void MovingPlatform::SetPosition(sf::Vector2f newPosition)
{
	Platform::SetPosition(newPosition);

	//update our velocity
	sf::Vector2f vectorToNewTarget = *targetPoint - GetPosition();
	vectorToNewTarget = VectorHelper::Normalise(vectorToNewTarget);
	velocity = vectorToNewTarget * SPEED;
}
