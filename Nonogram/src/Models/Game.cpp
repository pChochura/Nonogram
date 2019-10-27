#include "Game.h"
#include "../Utils/ResourceIdentifier.h"

Game::Game(Screen& firstScreen, std::string title, int width, int height) : screen(firstScreen) {
	this->title = title;
	this->width = width;
	this->height = height;
	this->context = new Context(new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->title, sf::Style::Titlebar | sf::Style::Close));

	this->screen.load(this->context);
}

void Game::changeScreen(Screen& screen) {
	this->screen = screen;
	this->screen.load(this->context);
}

void Game::show() {
	this->context->window->setFramerateLimit(60);

	while (this->context->window->isOpen()) {
		sf::Event event;
		while (this->context->window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->context->window->close();
			}
		}

		this->context->window->clear();

		this->screen.show(this->context);

		this->context->window->display();
	}
}
