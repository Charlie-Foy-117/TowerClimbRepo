#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, platformVector()
	, player()
	, door(this)
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, camera()
	//, window(newGamePointer->GetWindow())
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player.SetAlive(true);
		player.Update(frameTime);

		for (size_t i = 0; i < platformVector.size(); ++i)
		{
			platformVector[i]->Update(frameTime);
		}

		player.SetColliding(false);

		for (size_t i = 0; i < platformVector.size(); i++)
		{
			platformVector[i]->SetColliding(false);
		}
		door.SetColliding(false);

		for (size_t i = 0; i < platformVector.size(); i++)
		{
			if (platformVector[i]->CheckCollision(player))
			{
				player.SetColliding(true);
				platformVector[i]->SetColliding(true);
				player.HandleCollision(*platformVector[i]);
				platformVector[i]->HandleCollision(player);
			}
		}

		if (player.CheckCollision(door))
		{
			player.SetColliding(true);
			door.SetColliding(true);
			door.HandleCollision(player);
		}

		//if (player.GetPosition().y > window.getPosition().y)
		{
		//	player.SetAlive(false);
		//	TriggerEndState(false);
		}
	}
	else
	{
		endPanel.Update(frameTime);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	//update camera based on the render target size and player position
	camera = target.getDefaultView();
	sf::Vector2f cameraCentre = camera.getCenter();
	cameraCentre.y = player.GetPosition().y;
	camera.setCenter(cameraCentre);

	//update the render target to use the camera
	target.setView(camera);

	//draw world objects (ones that should use the camera)

	for (size_t i = 0; i < platformVector.size(); i++)
	{
		platformVector[i]->Draw(target);
	}
	door.Draw(target);
	player.Draw(target);

	//for any ui reset the camera to the default view before drawing
	target.setView(target.getDefaultView());

	//draw UI objects (use the base view)
	if (!gameRunning)
	{
		endPanel.Draw(target);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			Restart();
		}
	}
}

void LevelScreen::TriggerEndState(bool win)
{
	gameRunning = false;
	endPanel.WinLossPanel(player.GetAlive());
	endPanel.StartAnimation();
}

void LevelScreen::Restart()
{
	player.SetPosition(200, 200);

	//clear out platforms before making new ones
	//make sure to delete BEFORE clearing
	for (size_t i = 0; i < platformVector.size(); ++i)
	{
		delete platformVector[i];
		platformVector[i] = nullptr;
	}
	platformVector.clear();

	platformVector.push_back(new Platform(sf::Vector2f(200, 400)));
	platformVector.push_back(new Platform(sf::Vector2f(1200, 500)));
	platformVector.push_back(new MovingPlatform(sf::Vector2f(300, 700), sf::Vector2f(300, 700), sf::Vector2f(1000, 700)));
	platformVector.push_back(new BreakingPlatform(sf::Vector2f(500, 400)));
	platformVector.push_back(new DeadlyPlatform(sf::Vector2f(700, 400), this));


	door.SetPosition(1200, 350);

	gameRunning = true;
}
