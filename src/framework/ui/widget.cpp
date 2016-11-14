#include "widget.hpp"

#include "box.hpp"
#include "container.hpp"

Widget::Widget(){
	box = nullptr;
	parent = nullptr;
	container = std::unique_ptr<Container>(new Container(this));
	clickable = false;
	draggable = false;
	drawer = nullptr;
	pressed = false;
	covered = false;
	dragged = false;
}

Widget::~Widget(){
	if (parent != nullptr)
		parent->container->remove(this);
	if (box->getKeyboardFocus() == this)
		box->setKeyboardFocus(nullptr);
	if (box->getMouseFocus() == this)
		box->setMouseFocus(nullptr);
}

void Widget::draw(){
	if (drawer)
		drawer->draw(this);

	WidgetMap wmap = container->getWidgets();
	for (const std::pair<int, std::vector<Widget*>>& layer : wmap){
		for (Widget* w : layer.second){
			w->draw();
		}
	}
}

bool Widget::mouseDown(int x, int y, int button){
	Position realPos = getRealPosition();
	/*nenhum dos filhos aceitou o evento, tenta capturar*/
	if (clickable && covered){
		if (rect.isInside(realPos, Position(x, y))){
			pressed = true;
			box->setKeyboardFocus(this);
			onMouseDown(x, y, button);
			if (mouseDownCallback)
				mouseDownCallback(x, y, button);
			return true;
		}
	}

	return false;
}

bool Widget::mouseUp(int x, int y, int button){
	Position realPos = getRealPosition();
	/*mouse up só deve ser chamado pela box caso esse widget seja o mouseFocus*/
	if (pressed){
		pressed = false;
		onMouseUp(x, y, button);
		if (mouseUpCallback)
			mouseUpCallback(x, y, button);
		endDrag(x, y);

		if (!rect.isInside(realPos, Position(x, y))){
			covered = false;
			box->releaseMouse(x, y);
		}
		return true;
	}
	return false;
}

bool Widget::mouseMove(int fromX, int fromY, int toX, int toY){
	Position realPos = getRealPosition();

	/*se estiver pressionado, enquanto o mouse se move não permite a captura do evento a ninguém*/
	if (!pressed){
		WidgetMap& wmap = container->getWidgets();
		/*verifica se algum filho capturou o evento*/
		for (const std::pair<int, std::vector<Widget*>>& layer : wmap){
			for (Widget* w : layer.second){
				if (w->mouseMove(fromX, fromY, toX, toY)){
					covered = false;
					return true;
				}
			}
		}
	}
	else{
		/*dragging*/
		if (!dragged && draggable){
			startDrag(fromX, fromY, toX, toY);
		}
		else if (dragged){
			drag(fromX, fromY, toX, toY);
		}
		return true;
	}

	if (rect.isInside(realPos, Position(fromX, fromY)) || rect.isInside(realPos, Position(toX, toY))){
		/*call user callbacks*/
		onMouseMove(fromX, fromY, toX, toY);
		if (mouseMoveCallback)
			mouseMoveCallback(fromX, fromY, toX, toY);

		covered = true;
		box->setMouseFocus(this);
		return true;
	}else{
		covered = false;
		box->setMouseFocus(nullptr);
		return false;
	}
}

bool Widget::mouseWheel(int scrolled){
	onMouseScroll(scrolled);
	if (mouseScrollCallback)
		mouseScrollCallback(scrolled);
	return true;
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
	onStartDrag(fromX, fromY, toX, toY);
	if (startDragCallback)
		startDragCallback(fromX, fromY, toX, toY);
}

void Widget::drag(int fromX, int fromY, int toX, int toY){
	pos.x += toX - fromX;
	pos.y += toY - fromY;
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
	onDrag(fromX, fromY, toX, toY);
	if (dragCallback)
		dragCallback(fromX, fromY, toX, toY);
}

void Widget::endDrag(int x, int y){
	dragged = false;
	onEndDrag(x, y);
	if (endDragCallback)
		endDragCallback(x, y);
}