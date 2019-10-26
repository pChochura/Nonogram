#include "Screen.h"

Screen::Screen(std::vector<Stage*> stages, std::string title, int width, int height) {
	this->stages = stages;
	this->width = width;
	this->height = height;
}

void Screen::show() const {
	sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		for (auto& stage : stages) {
			stage->draw(&window);
		}

		window.display();
	}
}