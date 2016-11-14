#ifndef _WIDGET_
#define _WIDGET_

#include <map>
#include <list>
#include <string>
#include <functional>
#include <memory>
#include <vector>

#include "drawer.hpp"
#include "rectangle.hpp"

class Box;
class Container;

class Widget{
public:
	/*callbacks para eventos*/

	typedef std::function<void(int, int, int)> OnMouseButtonDown;
	typedef std::function<void(int, int, int)> OnMouseButtonUp;
	typedef std::function<void(int, int, int, int)> OnMouseMove;
	typedef std::function<void(int)> OnMouseScroll;
	typedef std::function<void(int, int, int, int)> OnStartDrag;
	typedef std::function<void(int, int, int, int)> OnDrag;
	typedef std::function<void(int, int)> OnEndDrag;
	typedef std::function<void(unsigned int)> OnKeyDown;
	typedef std::function<void(unsigned int)> OnKeyUp;
	typedef std::function<void(const std::string&)> OnTextInput;

	Widget();
	virtual ~Widget();

	void setBox(Box* box){ this->box = box; }
	Box* getBox(){ return box; }

	void draw();

	/*seta a área do widget, o widget é posicionado em relação ao seu pai*/
	void setShape(const Rect& rect){ this->rect = rect; }
	Rect& getShape(){ return rect; }
	const Rect& getShape()const{ return rect; }
	Position& getPosition(){ return pos; }
	const Position& getPosition()const{ return pos; }

	void setDrawer(DrawerPtr drawer){ this->drawer = drawer; }
	DrawerPtr getDrawer()const{ return drawer; }

	void makeClickable(bool clickable){ this->clickable = clickable; }
	bool isClickable()const{ return clickable; }

	void makeDraggable(bool draggable){ this->draggable = draggable; }
	bool isDraggable()const{ return draggable; }
	
	void makeEditable(bool editable){ this->editable = editable; }
	bool isEditable()const{ return editable; }

	/*retorna a forma não relativa ao pai do widget*/
	Position getRealPosition()const{
		if (parent != nullptr)
			return pos + parent->getRealPosition();
		return pos;
	}

	/*state*/

	bool isPressed()const{ return pressed; }
	bool isCovered()const{ return covered; }
	bool isDragged()const{ return dragged; }

	/*events*/
	
	bool mouseDown(int x, int y, int button);
	bool mouseUp(int x, int y, int button);
	bool mouseMove(int fromX, int fromY, int toX, int toY);
	bool mouseWheel(int scrolled);
	bool keyDown(unsigned int key);
	bool keyUp(unsigned int key);
	bool textInput(const std::string& text);

	Container* getContainer()const{ return container.get(); }

	void setParent(Widget* parent){ 
		this->parent = parent;
		setBox(parent->box);
	}

	Widget* getParent(){ return parent; }

	void setOnMouseButtonDown(OnMouseButtonDown mouseDown){ this->mouseDownCallback = mouseDown; }
	void setOnMouseButtonUp(OnMouseButtonUp mouseUp){ this->mouseUpCallback = mouseUp; }
	void setOnMouseMove(OnMouseMove mouseMove){ this->mouseMoveCallback = mouseMove; }
	void setOnMouseScroll(OnMouseScroll mouseScroll){ this->mouseScrollCallback = mouseScroll; }
	void setOnStartDrag(OnStartDrag startDrag){ this->startDragCallback = startDrag; }
	void setOnDrag(OnDrag drag){ this->dragCallback = drag; }
	void setOnDragEnd(OnEndDrag endDrag){ this->endDragCallback = endDrag; }
	void setOnKeyDown(OnKeyDown keyDown){ this->keyDownCallback = keyDown; }
	void setOnKeyUp(OnKeyUp keyUp){ this->keyUpCallback = keyUp; }
	void setOnTextInput(OnTextInput textInput){ this->textInputCallback = textInput; }

protected:
	/*eventos para serem tratados pelas classes filhas*/

	virtual void onMouseMove(int fromX, int fromY, int toX, int toY){}
	virtual void onMouseDown(int x, int y, int button){}
	virtual void onMouseUp(int x, int y, int button){}
	virtual void onMouseScroll(int scrolled){}
	virtual void onStartDrag(int fromX, int fromY, int toX, int toY){}
	virtual void onDrag(int fromX, int fromY, int toX, int toY){}
	virtual void onEndDrag(int x, int y){}
	virtual void onKeyDown(unsigned int key){}
	virtual void onKeyUp(unsigned int key){}
	virtual void onTextInput(const std::string& text){}

private:
	void startDrag(int fromX, int fromY, int toX, int toY);
	void drag(int fromX, int fromY, int toX, int toY);
	void endDrag(int x, int y);
protected:
	Box* box;
	Widget* parent;
	std::unique_ptr<Container> container;

	bool clickable;
	bool draggable;
	bool editable;
	
	DrawerPtr drawer;
	Rect rect;
	Position pos;

	/*flags de estado*/

	bool pressed;	/*mouse is down or not*/
	bool covered;	/*mouse is over or not*/
	bool dragged;	/*is being dragged or not*/

	/*callbacks*/
	OnMouseButtonDown mouseDownCallback;
	OnMouseButtonUp mouseUpCallback;
	OnMouseMove mouseMoveCallback;
	OnMouseScroll mouseScrollCallback;
	OnStartDrag startDragCallback;
	OnDrag dragCallback;
	OnEndDrag endDragCallback;
	OnKeyDown keyDownCallback;
	OnKeyUp keyUpCallback;
	OnTextInput textInputCallback;
};

typedef std::shared_ptr<Widget> WidgetPtr;

#endif