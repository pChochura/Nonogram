#pragma once
#include <functional>

////////////////////////////////////////////////////////////
//	Interface providing onClickListener.
////////////////////////////////////////////////////////////
class Clickable {
public:
	void setOnClickListener(std::function<void(Clickable*, bool)> onClickListener);
	int getId() const;

protected:
	// Indicates that the user clicked on the Clickable element. Second arguments tells if clicked inside or outside the element
	std::function<void(Clickable*, bool)> onClickListener;
	int id;
};