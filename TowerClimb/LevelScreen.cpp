#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"
#include "Game.h"
#include <fstream>
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, platformVector()
	, player()
	, door(this)
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, camera()
	, currentLevel(1)
{
	Restart();
	//LoadLevel("Level1");
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

		//if (player.GetPosition().y > )
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

bool LevelScreen::LoadNextLevel()
{
	return LoadLevel(currentLevel + 1);
}

void LevelScreen::Restart()
{
	LoadLevel(currentLevel);
}

bool LevelScreen::LoadLevel(int levelNumber)
{
	//construct level name from number
	std::string levelName = "Level" + std::to_string(levelNumber);

	bool success = LoadLevel(levelName);
	
	if (success)
	{
		currentLevel = levelNumber;
	}

	return success;
}

bool LevelScreen::LoadLevel(std::string fileName)
{
	//open the level file
	std::ifstream inFile;
	std::string filePath = "Assets/Levels/" + fileName + ".txt";

	inFile.open(filePath);

	//Make sure the file was actually opened
	if (!inFile)
	{
		//file was not opened
		return false;
	}

	//clear out platforms before making new ones
	//make sure to delete BEFORE clearing
	for (size_t i = 0; i < platformVector.size(); ++i)
	{
		delete platformVector[i];
		platformVector[i] = nullptr;
	}
	platformVector.clear();

	//set the starting x and y cooridnates used to position or level objects
	float x = 0.0f;
	float y = 0.0f;

	//define the spacing we will use for our grid
	const float X_SPACE = 150.0f;
	const float Y_SPACE = 150.0f;

	//read each character one by one from the file
	char ch;
	//each time, try to read the next character
	//if successful, execute the body of loop
	//the "noskipws" means our input from the file will include the white space(spaces and new lines)
	while (inFile >> std::noskipws >> ch)
	{
		//perform actions based on what character was read in

		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
		}
		else if (ch == 'N')
		{
			platformVector.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == 'B')
		{
			platformVector.push_back(new BreakingPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'D')
		{
			platformVector.push_back(new DeadlyPlatform(sf::Vector2f(x, y), this));
		}
		else if (ch == 'M')
		{
			platformVector.push_back(new MovingPlatform(sf::Vector2f(x, y), sf::Vector2f(0, y), sf::Vector2f(gamePointer->GetWindow()->getSize().x, y)));
		}
		else if (ch == 'O')
		{
			door.SetPosition(x, y);
		}
		else if (ch == '-')
		{
			//do nothing - empty space
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	//close file no that we are done with it
	inFile.close();

	//set out game to start
	gameRunning = true;
	//return true because we successfully loaded the file
	return true;
}
