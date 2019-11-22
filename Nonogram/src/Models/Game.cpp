#include "Game.h"
#include "Screens/ScreenMenu.h"
#include "../Utils/ResourceIdentifier.h"

Game::Game(Screen* firstScreen, std::string title, int width, int height) : screen(firstScreen) {
	this->width = width;
	this->height = height;
	this->context = new Context(new sf::RenderWindow(sf::VideoMode(this->width, this->height), title, sf::Style::Default, sf::ContextSettings(0, 0, 8)));

	changeScreen(firstScreen);
}

void Game::changeScreen(Screen* screen) {
	this->screen = screen;
	this->screen->load(this->context);
	this->screen->setOnChangeScreenListener([&](Screen* s) {
		changeScreen(s);
	});
}

void Game::show() {
	this->context->window->setFramerateLimit(60);
	this->context->window->setVerticalSyncEnabled(true);

	while (this->context->window->isOpen()) {
		sf::Event event;
		while (this->context->window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->context->window->close();
			} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				changeScreen(new ScreenMenu);
			} else {
				this->screen->onEvent(this->context, event);
			}
		}

		this->context->window->clear();

		this->screen->show(this->context);

		this->context->window->display();
	}
}