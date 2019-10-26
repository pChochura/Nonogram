#include "Game.h"

Game::Game(std::string title, int width, int height) {
	this->title = title;
	this->width = width;
	this->height = height;
}

void Game::changeScreen(Screen screen) {
	this->screen = screen;
}

void Game::show() const {
	sf::RenderWindow window(sf::VideoMode(this->width, this->height), this->title, sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		this->screen.show(&window);

		window.display();
	}
}
