#include "widget.hpp"

#include "box.hpp"
#include "utils/size.hpp"

Widget::Widget(){
	box = nullptr;
	parent = nullptr;
	clickable = false;
	draggable = false;
	drawer = nullptr;
	pressed = false;
	covered = false;
	dragged = false;
}

Widget::~Widget(){
	if (box->getKeyboardFocus() == this)
		box->setKeyboardFocus(nullptr);
	if (box->getMouseFocus() == this)
		box->setMouseFocus(nullptr);
}

void Widget::draw(){
	if (drawer)
		drawer->draw(this);
}

bool Widget::mouseDown(int x, int y, int button){
	Rect rect(realPosition(), size);
	bool inside = rect.inside(Point(x, y));

	//propagate to childs
	for(auto& child : childs){
		if(child->mouseDown(x, y, button)){
			return true;
		}
	}

	if(clickable && inside && onMouseDown(x, y, button)){
		pressed = true;
		getBox()->setMouseFocus(this);

		if(draggable && onDrag(x, y, x, y)){
			startDrag(x, y, x, y);
		}

		if(mouseDownCallback)
			mouseDownCallback(x, y, button);
		return true;
	}

	return false;
}

bool Widget::mouseUp(int x, int y, int button){
	Rect rect(realPosition(), size);
	bool inside = rect.inside(Point(x, y));

	//propagate to childs
	for(auto& child : childs){
		if(child->mouseUp(x, y, button)){
			return true;
		}
	}

	if(pressed && inside && onMouseUp(x, y, button)){
		pressed = false;
		getBox()->setMouseFocus(nullptr);

		if(dragged && onEndDrag(x, y))
			endDrag(x, y);

		if(mouseUpCallback)
			mouseUpCallback(x, y, button);

		return true;
	}

	return false;
}

bool Widget::mouseMove(int fromX, int fromY, int toX, int toY){
	Rect rect(realPosition(), size);
	bool f_inside = rect.inside(Point(fromX, fromY));
	bool t_inside = rect.inside(Point(toX, toY));

	//propagate to childs
	for(auto& child : childs){
		if(child->mouseMove(fromX, fromY, toX, toY)){
			return true;
		}
	}

	//if is being dragged no one else can receive the event
	if(dragged){
		if(onDrag(fromX, fromY, toX, toY)){
			drag(fromX, fromY, toX, toY);
		}
		return true;
	}

	//if is pressed no one else can receive the event
	if(pressed){
		if(onMouseMove(fromX, fromY, toX, toY)){
			if(mouseMoveCallback)
				mouseMoveCallback(fromX, fromY, toX, toY);
		}
		return true;
	}

	if((f_inside || t_inside) && onMouseMove(fromX, fromY, toX, toY)){
		if(t_inside){
			covered = true;
			getBox()->setMouseFocus(this);
		}else{
			covered = false;
			getBox()->setMouseFocus(nullptr);
		}

		if(mouseMoveCallback)
			mouseMoveCallback(fromX, fromY, toX, toY);
		
		//allow other widgets to catch the event since the mouse is moving out from this widget
		if(t_inside)
			return true;
	}

	return false;
}

bool Widget::mouseWheel(int scrolled){
}

bool Widget::keyDown(unsigned int key){
	if (editable){
		onKeyDown(key);
		if (keyDownCallback)
			keyDownCallback(key);
		return true;
	}
	return false;
}

bool Widget::keyUp(unsigned int key){
	if (editable){
		onKeyUp(key);
		if (keyUpCallback)
			keyUpCallback(key);
		return true;
	}
	return false;
}

bool Widget::textInput(const std::string& text){
	if (editable){
		onTextInput(text);
		if (textInputCallback)
			textInputCallback(text);
		return true;
	}
	return false;
}

void Widget::startDrag(int fromX, int fromY, int toX, int toY){
	dragged = true;
	drag(fromX, fromY, toX, toY);
	if (startDragCallback)
		startDragCallback(fromX, fromY, toX, toY);
}

void Widget::drag(int fromX, int fromY, int toX, int toY){
	position = calculateDrag(fromX, fromY, toX, toY);
	if (parent != nullptr){
		if (pos.x < 0)
			pos.x = 0;
		if (pos.x > parent->rect.w - rect.w)
			pos.x = parent->rect.w - rect.w;
		if (pos.y < 0)
			pos.y = 0;
		if (pos.y > parent->rect.h - rect.h)
			pos.y = parent->rect.h - rect.h;
	}
	if (dragCallback)
		dragCallback(fromX, fromY, toX, toY);
}

void Widget::endDrag(int x, int y){
	dragged = false;
	if (endDragCallback)
		endDragCallback(x, y);
}