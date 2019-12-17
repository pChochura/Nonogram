#include "StageDifficultyMenu.h"
#include "../Actors/Button.h"
#include "../Actors/ButtonGroup.h"

void StageDifficultyMenu::init(Context* context) {
	context->textures.load(Textures::ButtonTutorial, "data/Textures/button_tutorial.png");
	context->textures.load(Textures::ButtonBabyStyle, "data/Textures/button_baby_style.png");
	context->textures.load(Textures::ButtonDecent, "data/Textures/button_decent.png");
	context->textures.load(Textures::ButtonImpresive, "data/Textures/button_impresive.png");
	context->textures.load(Textures::ButtonWorldClass, "data/Textures/button_world_class.png");
	context->textures.load(Textures::ButtonFromFile, "data/Textures/button_from_file.png");
	context->textures.load(Textures::DifficultyMenu, "data/Textures/difficulty_menu.png");

	context->textures.get(Textures::ButtonTutorial).setSmooth(true);
	context->textures.get(Textures::ButtonBabyStyle).setSmooth(true);
	context->textures.get(Textures::ButtonDecent).setSmooth(true);
	context->textures.get(Textures::ButtonImpresive).setSmooth(true);
	context->textures.get(Textures::ButtonWorldClass).setSmooth(true);
	context->textures.get(Textures::ButtonFromFile).setSmooth(true);

	context->fonts.load(Fonts::Arcon, "data/Fonts/Arcon.otf");

	context->sounds.load(Sounds::ButtonTap, "data/Sounds/tap_sound.wav");

	this->tapSound = context->sounds.get(Sounds::ButtonTap);

	this->view = context->window->getDefaultView();

	this->difficultyMenuSize = { 400, 500 };
	this->difficultyMenuPos = { (context->window->getSize().x - this->difficultyMenuSize.x) / 2.0f, (context->window->getSize().y - this->difficultyMenuSize.y) / 2.0f };

	this->buttons.push_back(
		(new Button(ID::ButtonTutorial, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 100.0f, difficultyMenuPos.y + 120.0f })
		->withPadding({ 50, 35 })
		->withTexture(context->textures.get(Textures::ButtonTutorial))
		->withText("TUTORIAL")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);
	this->buttons.push_back(
		(new Button(ID::ButtonBabyStyle, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 100.0f, difficultyMenuPos.y + 180.0f })
		->withPadding({ 50, 35 })
		->withTexture(context->textures.get(Textures::ButtonBabyStyle))
		->withText("BABY STYLE")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);
	this->buttons.push_back(
		(new Button(ID::ButtonDecent, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 100.0f, difficultyMenuPos.y + 240.0f })
		->withPadding({ 50, 35 })
		->withTexture(context->textures.get(Textures::ButtonDecent))
		->withText("DECENT")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);
	this->buttons.push_back(
		(new Button(ID::ButtonImpresive, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 100.0f, difficultyMenuPos.y + 300.0f })
		->withPadding({ 50, 35 })
		->withTexture(context->textures.get(Textures::ButtonImpresive))
		->withText("IMPRESIVE")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);
	this->buttons.push_back(
		(new Button(ID::ButtonWorldClass, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 100.0f, difficultyMenuPos.y + 360.0f })
		->withPadding({ 50, 35 })
		->withTexture(context->textures.get(Textures::ButtonWorldClass))
		->withText("WORLD CLASS")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);
	this->buttons.push_back(
		(new Button(ID::ButtonFromFile, { 200, ButtonSize::WrapContent }))
		->withPosition({ context->window->getSize().x / 2.0f - 100.0f, difficultyMenuPos.y + 420.0f })
		->withPadding({ 50, 35 })
		->withTexture(context->textures.get(Textures::ButtonFromFile))
		->withText("FROM FILE")
		->withTextFont(context->fonts.get(Fonts::Arcon))
		->withTextColor(sf::Color(255, 255, 255))
		->withTextSize(20)
		->build()
	);

	initClickListeners(context);
}

void StageDifficultyMenu::initClickListeners(Context* context) {
	for (auto& button : this->buttons) {
		button->setOnClickListener([&](Clickable* b, bool inside) {
			this->sound.setBuffer(this->tapSound);
			this->sound.play();
			switch (b->getId()) {
			case ID::ButtonTutorial:
				this->onClickListener(Difficulty::Tutorial);
				break;
			case ID::ButtonBabyStyle:
				this->onClickListener(Difficulty::BabyStyle);
				break;
			case ID::ButtonDecent:
				this->onClickListener(Difficulty::Decent);
				break;
			case ID::ButtonImpresive:
				this->onClickListener(Difficulty::Impresive);
				break;
			case ID::ButtonWorldClass:
				this->onClickListener(Difficulty::WorldClass);
				break;
			case ID::ButtonFromFile:
				this->onClickListener(Difficulty::FromFile);
				break;
			}
		});
	}
}

void StageDifficultyMenu::draw(Context* context) {
	context->window->setView(this->view);

	sf::Sprite sprite(context->textures.get(Textures::DifficultyMenu));
	sprite.setPosition(difficultyMenuPos);
	sprite.setScale(difficultyMenuSize.x / sprite.getLocalBounds().width, difficultyMenuSize.y / sprite.getLocalBounds().height);
	context->window->draw(sprite);

	sf::Text text("Nonogram", context->fonts.get(Fonts::Arcon), 40);
	text.setFillColor(sf::Color(20, 37, 70));
	text.setStyle(sf::Text::Bold);
	text.setOrigin(text.getLocalBounds().width / 2.0f, 0);
	text.setPosition({ context->window->getSize().x / 2.0f, difficultyMenuPos.y + 30 });
	context->window->draw(text);

	for (auto& button : this->buttons) {
		button->draw(context);
	}
}

bool StageDifficultyMenu::onEvent(Context* context, sf::Event event) {
	context->window->setView(this->view);

	for (auto& button : this->buttons) {
		if (button->onEvent(context, event)) {
			return true;
		}
	}

	return false;
}

void StageDifficultyMenu::setOnClickListener(std::function<void(Difficulty)> onClickListener) {
	this->onClickListener = onClickListener;
}