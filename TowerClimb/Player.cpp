#include "Player.h"
#include "AssetManager.h"

enum class PhysicsType
{
	FORWARD_EULER,
	BACKWARD_EULER
};

Player::Player()
	: SpriteObject()
	, position(100, 300)
	, velocity()
	, acceleration()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
	sprite.setPosition(position);
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG = 0.99f;
	const PhysicsType physics = PhysicsType::BACKWARD_EULER;

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
		{
			//EXPLICIT EULER (FORWARD EULER)

			position = position + velocity * frameTime.asSeconds();
			velocity = velocity + acceleration * frameTime.asSeconds();

			//Drag
			velocity = velocity * DRAG;

			//Update acceleration
			UpdateAcceleration();
		}
		break;

	case PhysicsType::BACKWARD_EULER:
		{
			//IMPLICIT / BACKWARD EULER
			// 
			//Update acceleration
			UpdateAcceleration();

			//drag
			velocity = velocity * DRAG;

			velocity = velocity + acceleration * frameTime.asSeconds();
			position = position + velocity * frameTime.asSeconds();
		}
		break;

	default:
		break;
	}


	//update the visual position to match the physics
	sprite.setPosition(position);
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 2000;

	//Update acceleration
	acceleration.x = 0;
	acceleration.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		acceleration.y = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		acceleration.y = ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
	}
}
