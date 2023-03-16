#include "SpriteObject.h"
#include "VectorHelper.h"

SpriteObject::SpriteObject()
	: sprite()
	, position(0, 0)
	, colliding (false)
	, collisionOffset(0, 0)
	, collisionScale(1, 1)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);

	bool drawCollider = true;
	if (drawCollider)
	{
		sf::CircleShape circle;

		sf::Vector2f shapePosition = GetCollisionCentre();
		float circleRadius = GetCircleColliderRadius();
		shapePosition.x -= circleRadius;
		shapePosition.y -= circleRadius;

		circle.setPosition(shapePosition);
		circle.setRadius(circleRadius);
		sf::Color collisionColour = sf::Color::Green;
		//turn this red if a collision is occurring
		if (colliding)
		{
			collisionColour = sf::Color::Red;
		}
		collisionColour.a = 100;
		circle.setFillColor(collisionColour);

		target.draw(circle);
	}
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool SpriteObject::CheckCollision(SpriteObject other)
{

	//get the vector representing the displacement between the two circles
	sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

	//get the magnitude of that vector, which is how far apart the circle centres
	float sqaureDistance = VectorHelper::SquareMagnitude(displacement); //todo

	//compare that to the comvined radii of the two circles
	float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

	return sqaureDistance <= combinedRadii * combinedRadii;
}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width / 2.0f;
	centre.y += bounds.height / 2.0f;

	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

float SpriteObject::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	if (bounds.width > bounds.height)
		return bounds.width / 2.0f;
	else
		return bounds.height / 2.0f;
}
