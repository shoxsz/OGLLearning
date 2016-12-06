#ifndef _WIDGET_
#define _WIDGET_

#include "definitions.hpp"
#include "drawer.hpp"
#include "utils/point.hpp"
#include "utils/size.hpp"

#include <map>
#include <list>
#include <string>
#include <functional>
#include <memory>
#include <vector>

/*
	An widget is a generic 2D UI element that have a rectangular shape and interacts with the mouse and keyboard,
	it can be:
		pressed, dragged, scrolled and written.
	This class provides a functional but simple widget.
	Each widget have a child list that it will use to propagate events.
	Events propagation:
		Mouse button down:
			A widget first repass this event to its childs and return when a child has caught
			the event, if no child has caught the event then the widget will process it:
				A virtual method that can be overriden by a child class will be called to process the
				event, if it returns true the widget has caught the event and so it will mark itself
				as the mouse focus within its Box and pressed, finally it will call the user defined
				callback to inform about the event.
		Mouse button up:
			A widget first repass this event to its childs and return when a child has caught
			the event, if no child has caught the event then the widget will process it:
				A virtual method that can be overriden by a child class will be called to process the
				event, if it returns true the widget has caught the event and so it will unmark itself
				as the mouse focus and unpressed, finally it will call the user defined callback to inform
				about the event.
		Mouse move:
			A widget first repass this event to its childs and return when a child has caught
			the event, if no child has caught the event then the widget will process it:
				A virtual method that can be overriden by a child class will be called to process the
				event, if it returns true the widget has caught the event and so it will mark itself
				as the mouse focus within its Box and will be marked as covered, finally it will call 
				the user defined callback to inform about the event.
		Mouse scroll:
			A widget first repass this event to its childs and return when a child has caught
			the event, if no child has caught the event then the widget will process it:
				A virtual method that can be overriden by a child class will be called to process the
				event, if it returns true the widget has caught the event and so it will call the user
				defined callback to inform about the event.
		Drag events:
			This are secondary events that are generated when the widget are marked as draggable and has
			received some mouse event. This event is only processed by a widget if the widget is marked 
			as the mouse focus in its Box and is marked as draggable.
			Drag start:
				The widget will call a virtual method that can be inherited by a child class to process the
				event, if it returns true the widget has caught the event and so it will mark itself as dragged
				and then call the user callback to inform about the event.
			Drag:
				If a widget is being dragged it will call a virtual method that can be inherited by a child class to 
				process the event, if it returns true the widget has caught the event and so it will call the user
				callback to inform about the event.
			Drag end:
				If a widget is being dragged it will call a virtual method that can be inherited by a child class to
				process the event, if it returns true the widget has caught the event and so it will unmark itself as
				dragged and will call a user defined callback to inform about the event.
			Keyboard events: key down/up & text input
				This events have no propagation, they will just be repassed to child classes to process it and call
				user defined callbacks.
	Drawning:
		Each widget first draw itself and then call the childs draw methods, the widget uses a Drawer that is responsible
		for the drawning.
*/

class Widget{
public:
	/*events callbacks*/

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
	Box* getBox(){ return (parent == nullptr ? box : parent->box); }

	void draw();

	/*Specify the area used by this widget*/
	void setSize(const SizeI& size){ this->size = size; }
	SizeI& getSisze(){ return size; }
	const SizeI& getSize()const{ return size; }
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

	/*returns the position relative to the window*/
	Position getScreenPosition()const{
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

	/*return the container that holds this widget children*/
	ContainerPtr getContainer()const{ return container.get(); }

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
	/*overriden in child classes, must return true if the widget must catch the event or false
	otherwise*/

	virtual bool onMouseMove(int fromX, int fromY, int toX, int toY){ return true; }
	virtual bool onMouseDown(int x, int y, int button){ return true; }
	virtual bool onMouseUp(int x, int y, int button){ return true; }
	virtual bool onMouseScroll(int scrolled){ return true; }
	virtual bool onStartDrag(int fromX, int fromY, int toX, int toY){ return true; }
	virtual bool onDrag(int fromX, int fromY, int toX, int toY){ return true; }
	virtual bool onEndDrag(int x, int y){ return true; }
	virtual bool onKeyDown(unsigned int key){ return true; }
	virtual bool onKeyUp(unsigned int key){ return true; }
	virtual bool onTextInput(const std::string& text){ return true; }

	virtual Point calculateDrag(int fromX, int fromY, int toX, int toY){ return Point(toX - fromX, toY - fromY); }

	void startDrag(int fromX, int fromY);
	void drag(int fromX, int fromY, int toX, int toY);
	void endDrag(int x, int y);
protected:
	Box* box;
	Widget* parent;
	std::map<int, WidgetPtr> childs;

	DrawerPtr drawer;
	PointI position;
	SizeI size;

	bool clickable;
	bool draggable;
	bool editable;

	/*state flags*/

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