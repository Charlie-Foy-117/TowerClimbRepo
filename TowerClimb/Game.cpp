#include "Game.h"
#include "Screen.h"

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Tower Climb", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
	, currentScreen(nullptr)
{
	//window setup
	window.setMouseCursorVisible(false);

	//TODO: Setup screens
}

void Game::RunGameLoop()
{
	//repeat as long as the window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}
}

void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		//close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	//TODO: Update current screen
	if (currentScreen)
	{
		currentScreen->Update(frameTime);
	}

	//TODO: Handle changes to other screens
}

void Game::Draw()
{
	window.clear();
	
	//TODO: Draw current screen
	if (currentScreen)
	{
		currentScreen->Draw(window);
	}

	window.display();
}
