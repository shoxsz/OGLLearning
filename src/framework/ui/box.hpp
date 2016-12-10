#ifndef _BOX_
#define _BOX_

#include "definitions.hpp"
#include "widget.hpp"

#include <memory>

class Box{
public:
	Box(){
		root = nullptr;
		mouseFocus = nullptr;
		keyboardFocus = nullptr;
	}

	virtual ~Box(){}

	virtual void poll() = 0;

	void setRoot(WidgetPtr root){
		this->root = root;
		this->root->setBox(this);
	}

	WidgetPtr getRoot()const{ return root; }

	void setMouseFocus(Widget* mouseFocus){ this->mouseFocus = mouseFocus; }
	Widget* getMouseFocus()const{ return mouseFocus; }

	void setKeyboardFocus(Widget* keyboardFocus){ this->keyboardFocus = keyboardFocus; }
	Widget* getKeyboardFocus(){ return keyboardFocus; }

protected:
	WidgetPtr root;
	Widget* mouseFocus;
	Widget* keyboardFocus;
};

#endif