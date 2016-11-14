#ifndef _BOX_
#define _BOX_

#include <memory>
#include "widget.hpp"

class Box{
public:
	Box(){
		root = nullptr;
		mouseFocus = nullptr;
		keyboardFocus = nullptr;
	}

	virtual ~Box(){}

	/*process and dispatch events*/
	virtual void act() = 0;

	void setRoot(WidgetPtr root){
		this->root = root;
		this->root->setBox(this);
	}

	WidgetPtr getRoot()const{ return root; }

	/*release the mouse focus and throw a mouseMove event in the specified position*/
	void releaseMouse(int x, int y){
		mouseFocus = nullptr;
		root->mouseMove(x, y, x, y);
	}

	void setMouseFocus(Widget* mouseFocus){ this->mouseFocus = mouseFocus; }
	Widget* getMouseFocus()const{ return mouseFocus; }

	void setKeyboardFocus(Widget* keyboardFocus){ this->keyboardFocus = keyboardFocus; }
	Widget* getKeyboardFocus(){ return keyboardFocus; }

protected:
	WidgetPtr root;
	Widget* mouseFocus;
	Widget* keyboardFocus;
};

typedef std::shared_ptr<Box> BoxPtr;

#endif