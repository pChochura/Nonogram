#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "Stage.h"
#include "../Actors/Actor.h"
#include "../Drawables/MultilineText.h"
#include "../../Utils/ResourceIdentifier.h"

class StageMessage : public Stage {
public:
	virtual void init(Context*) override;
	virtual void draw(Context*) override;
	virtual bool onEvent(Context*, sf::Event) override;
	void setOnOkClickListner(std::function<void(void)>);
	void setMessage(std::string);

private:
	void initClickListeners(Context*);

private:
	MultilineText text;

	sf::Vector2f messageMenuSize;
	sf::Vector2f messageMenuPos;
	std::function<void(void)> onOkClickListener;
	std::string message;
	sf::SoundBuffer tapSound;
	sf::Sound sound;
	std::vector<Actor*> buttons;

	enum ID {
		ButtonOk = (1 << 0)
	};
};