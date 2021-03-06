#include "widget.hpp"

#include "box.hpp"
#include "utils/size.hpp"

Widget::Widget(){
	box = nullptr;
	parent = nullptr;
	zOrder = 0;
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

	//propagate to childs
	for (auto& layer : childs) {
		for (WidgetPtr& child : layer.second) {
			child->draw();
		}
	}
}

bool Widget::mouseDown(const MouseButtonEvent& button){
	Rect rect = getRect();
	bool inside = rect.inside(button.getPosition());

	//propagate to childs
	for(auto& layer : childs){
		for(WidgetPtr& child : layer.second){
			if (child->mouseDown(button))
				return true;
		}
	}

	if(clickable && inside && onMouseDown(button)){
		MouseMoveEvent drag(button);

		pressed = true;
		box->setMouseFocus(this);

		if(draggable && onDrag(drag)){
			startDrag(drag);
		}

		if(mouseDownCallback)
			mouseDownCallback(*this, button);
		return true;
	}

	return false;
}

bool Widget::mouseUp(const MouseButtonEvent& button){
	Rect rect = getRect();
	bool inside = rect.inside(button.getPosition());

	//propagate to childs
	for (auto& layer : childs) {
		for (WidgetPtr& child : layer.second) {
			if (child->mouseUp(button))
				return true;
		}
	}

	if (pressed && onMouseUp(button)) {
		pressed = false;

		if (editable)
			box->setKeyboardFocus(this);

		if (!inside && covered) {
			covered = false;
			box->setMouseFocus(nullptr);
		}

		if (dragged) {
			MouseMoveEvent drag(button);
			if (onEndDrag(drag))
				endDrag(drag);
		}

		if (mouseUpCallback)
			mouseUpCallback(*this, button);

		return true;
	}

	return false;
}

bool Widget::mouseMove(const MouseMoveEvent& move){
	Rect rect = getRect();
	bool s_inside = rect.inside(move.getSourcePosition());
	bool t_inside = rect.inside(move.getTargetPosition());

	//if is being dragged no one else can receive the event
	if (dragged) {
		if (onDrag(move)) {
			drag(move);
		}
		return true;
	}

	//if is pressed no one else can receive the event
	if (pressed) {
		if (onMouseMove(move)) {
			if (mouseMoveCallback)
				mouseMoveCallback(*this, move);
		}
		return true;
	}

	//propagate to childs
	for (auto& layer : childs) {
		for (WidgetPtr& child : layer.second) {
			if (child->mouseMove(move)) {
				covered = false;
				return true;
			}
		}
	}

	if((s_inside || t_inside) && onMouseMove(move)){
		if(t_inside){
			covered = true;
			getBox()->setMouseFocus(this);
		}else{
			covered = false;
			getBox()->setMouseFocus(nullptr);
		}

		if(mouseMoveCallback)
			mouseMoveCallback(*this, move);
		
		//return false if (!t_inside) to allow other widgets to catch the event since the mouse is moving out from this widget
		if(t_inside)
			return true;
	}

	return false;
}

bool Widget::mouseScroll(const MouseScrollEvent& scroll){
	//propagate to childs
	for (auto& layer : childs) {
		for (WidgetPtr& child : layer.second) {
			if (child->mouseScroll(scroll))
				return true;
		}
	}

	if(covered && onMouseScroll(scroll)){
		scrolledPosition += scroll.getScrolled();

		if(mouseScrollCallback)
			mouseScrollCallback(*this, scroll);
		return true;
	}
	return false;
}

bool Widget::keyDown(const KeyboardEvent& keyboard){
	if (editable && onKeyDown(keyboard)){
		if (keyDownCallback)
			keyDownCallback(*this, keyboard);
		return true;
	}
	return false;
}

bool Widget::keyUp(const KeyboardEvent& keyboard){
	if (editable && onKeyUp(keyboard)){
		if (keyUpCallback)
			keyUpCallback(*this, keyboard);
		return true;
	}
	return false;
}

bool Widget::textInput(const TextInputEvent& input){
	if (editable && onTextInput(input)){
		if (textInputCallback)
			textInputCallback(*this, input);
		return true;
	}
	return false;
}

void Widget::addChild(WidgetPtr child) {
	childs[child->zOrder].push_back(child);
	child->parent = this;
	child->setBox(this->box);
}

void Widget::removeChild(WidgetPtr child) {
	if (child->parent == this) {
		child->parent = nullptr;
		child->setBox(nullptr);
		childs[child->zOrder].remove(child);
	}
}

void Widget::startDrag(const MouseMoveEvent& drag){
	dragged = true;
	this->drag(drag);
	if (startDragCallback)
		startDragCallback(*this, drag);
}

void Widget::drag(const MouseMoveEvent& drag){
	position += Point(calculateDrag(drag));
	if (parent != nullptr){
		if (position.x < 0)
			position.x = 0;
		if (position.x > parent->size.width - size.width)
			position.x = parent->size.width - size.width;
		if (position.y < 0)
			position.y = 0;
		if (position.y > parent->size.height - size.height)
			position.y = parent->size.height - size.height;
	}
	if (dragCallback)
		dragCallback(*this, drag);
}

void Widget::endDrag(const MouseMoveEvent& drag){
	dragged = false;
	if (endDragCallback)
		endDragCallback(*this, drag);
}

void Widget::swapZOrder(Widget* child, int newOrder) {
	if (child->parent == this) {
		WidgetPtr ptr(child);
		childs[child->zOrder].remove(ptr);
		childs[newOrder].push_back(ptr);
	}
}