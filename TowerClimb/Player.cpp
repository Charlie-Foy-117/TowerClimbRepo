#include "Player.h"
#include "AssetManager.h"

enum class PhysicsType
{
	FORWARD_EULER,
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	POSITION_VERLET,
	VELOCITY_VERLET
};

Player::Player()
	: SpriteObject()
	, twoFramesOldPosition(100, 300)
	, velocity()
	, acceleration()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));

	collisionOffset = sf::Vector2f(0, 25);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
	collisionType = CollisionType::CIRCLE;
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG = 10.0f;
	const PhysicsType physics = PhysicsType::VELOCITY_VERLET;

	sf::Vector2f lastFramePos = GetPosition();

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
		{
			//EXPLICIT EULER (FORWARD EULER)

			SetPosition(GetPosition() + velocity * frameTime.asSeconds());
			velocity = velocity + acceleration * frameTime.asSeconds();

			//Drag
			velocity = velocity - velocity * DRAG * frameTime.asSeconds();

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
			SetPosition(GetPosition() + velocity * frameTime.asSeconds());
		}
		break;

	case PhysicsType::SYMPLECTIC_EULER:
		{
			//SEMI-IMPLICIT / SYMPLECTIC EULER
		
			velocity = velocity + acceleration * frameTime.asSeconds();

			//drag
			velocity = velocity - velocity * DRAG * frameTime.asSeconds();

			SetPosition(GetPosition() + velocity * frameTime.asSeconds());
			UpdateAcceleration();
		}
		break;

	case PhysicsType::POSITION_VERLET:
		{
			//POSITION_VERLET

			//Update acceleration
			UpdateAcceleration();

			//calculate current frames position
			SetPosition(2.0f * GetPosition() - twoFramesOldPosition + acceleration * frameTime.asSeconds() * frameTime.asSeconds());

		}
		break;

	case PhysicsType::VELOCITY_VERLET:
		{
			//VELOCITY VERLET
			//get half frame velocity using
			//previous frame's acceleration
			sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

			//get new frame's position using half frame velocity
			SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

			//update our current acceleration
			UpdateAcceleration();

			//get new frame's velocity using half frame velocity and updated acceleration
			velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

			//drag
			velocity = velocity - velocity * DRAG * frameTime.asSeconds();
		}
		break;

	default:
		break;
	}

	//two frames ago (for next frame)
	twoFramesOldPosition = lastFramePos;
}

void Player::HandleCollision(SpriteObject other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		//move in x direction
		newPosition.x += depth.x;
	}
	else
	{
		//move in y direction
		newPosition.y += depth.y;
	}

	SetPosition(newPosition);
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 10000;

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
