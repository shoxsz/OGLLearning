#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

#include "utils/point.hpp"
#include "utils/size.hpp"

#include <string>

class Event{
public:
    enum EventType{
        Mouse,
        Keyboard,
        TextInput
    };

    virtual EventType getType()const = 0;
};

class MouseEvent : public Event{
public:

    enum MouseEventType{
        MouseUp,
        MouseDown,
        MouseScroll,
        MouseMove,
        MouseDrag
    };


	MouseEvent(const Point& position = Point(0, 0)) : MouseEvent(false, false, false, position) {}

	MouseEvent(bool left, bool right, bool middle, const Point& position):
		leftButton(false),
		rightButton(false),
		middleButton(false),
		position(position){}

    virtual EventType getType()const{return Mouse;}
    virtual MouseEventType getMouseEventType()const = 0;

    void setLeft(bool left){leftButton = left;}
    void setRight(bool right){ rightButton = right;}
    void setMiddle(bool middle){ middleButton = middle;}

    void setPosition(const Point& position){
        this->position = position;
    }

    bool left()const{return leftButton;}
    bool right()const{return rightButton;}
    bool middle()const{return middleButton;}

    int getX()const{return position.x;}
    int getY()const{return position.y;}
    const Point& getPosition()const{return position;}

protected:
    bool leftButton;    //is left button pressed?
    bool rightButton;   //is right button pressed?
    bool middleButton;  //is middle button pressed?
    Point position;     //current mouse position
};

class MouseButtonEvent : public MouseEvent{
public:

    MouseButtonEvent(bool down = false, int clicks = 0) : MouseButtonEvent(false, false, false, Point(0, 0), clicks, down){}

	MouseButtonEvent(bool left, bool right, bool middle, const Point& position, int clicks, bool down) : 
		MouseEvent(left, right, middle, position) {
		this->clicks = clicks;
		this->type = (down ? MouseDown : MouseUp);
	}

    virtual MouseEventType getMouseEventType()const{return type;}

    void setMouseDown(bool down){type = (down ? MouseDown : MouseUp);}
    void setClicks(int clicks){this->clicks = clicks;}

    int getClicks()const{return clicks;}
    bool isDoubleClick()const{return clicks == 2;}

private:
    int clicks;
    MouseEventType type;
};

class MouseMoveEvent : public MouseEvent{
public:

    //copy the mouse buttons states and the position, the drag will be 0
    MouseMoveEvent(const MouseButtonEvent& button){
		fromMouseButtonEvent(button);
	}

    MouseMoveEvent(const Point& source = Point(0, 0), const Point& target = Point(0, 0)): MouseMoveEvent(false, false, false, source, target){}

	MouseMoveEvent(bool left, bool right, bool middle, const Point& source, const Point& target): MouseEvent(left, right, middle, source){
		setTarget(target);
	}

    virtual MouseEventType getMouseEventType()const{return MouseMove;}

	//copy the mouse buttons states and the position, the drag will be 0
	void fromMouseButtonEvent(const MouseButtonEvent& button) {
		this->position = button.getPosition();
		this->targetPosition = button.getPosition();
		this->leftButton = button.left();
		this->middleButton = button.middle();
		this->rightButton = button.right();
	}

    void setSource(const Point& source){this->position = source;}
    void setTarget(const Point& target){this->targetPosition = target;}

    const Point& getSourcePosition()const{return position;}
    const Point& getTargetPosition()const{return targetPosition;}
    Size getDrag()const{return (targetPosition - position).toSize();}

private:
    Point targetPosition;
};

class MouseScrollEvent : public MouseEvent{
public:

    //copy the mouse buttons states and the position, the scroll amount will be 0
	MouseScrollEvent(const MouseButtonEvent& button){
		fromMouseButtonEvent(button);
		scrolledX = 0;
		scrolledY = 0;
	}

	MouseScrollEvent(int scrolledX = 0, int scrolledY = 0): MouseScrollEvent(false, false, false, Point(0, 0), scrolledX, scrolledY){}

	MouseScrollEvent(const Point& position, int scrolledX, int scrolledY) :
		MouseScrollEvent(false, false, false, position, scrolledX, scrolledY){}

    MouseScrollEvent(bool left, bool right, bool middle, const Point& position, int scrolledX , int scrolledY) :
		MouseEvent(left, right, middle, position){
			setScrolledX(scrolledX);
			setScrolledY(scrolledY);
	}

    virtual MouseEventType getMouseEventType()const{return MouseScroll;}

	//copy the mouse buttons states and the position, the scroll amount will not be changed
	void fromMouseButtonEvent(const MouseButtonEvent& button) {
		this->position = button.getPosition();
		this->leftButton = button.left();
		this->middleButton = button.middle();
		this->rightButton = button.right();
	}

	void setScrolled(const Size& size){
		scrolledX = size.width;
		scrolledY = size.height;
	}

    void setScrolledX(int scrolledX){this->scrolledX = scrolledX;}
    void setScrolledY(int scrolledY){this->scrolledY = scrolledY;}

    int getScrolledX()const{return scrolledX;}
    int getScrolledY()const{return scrolledY;}

	Size getScrolled()const { return Size(scrolledX, scrolledY); }

private:
    int scrolledX;
    int scrolledY;
};

class KeyboardEvent : public Event{
public:

    enum KeyboardEventType{
        KeyDown,
        KeyUp
    };

    KeyboardEvent(unsigned char key = 0, unsigned char modifiers = 0, unsigned int repeat = 0, KeyboardEventType type = KeyDown):
    key(key), modifiers(modifiers), repeat(repeat), type(type){}

    virtual EventType getType()const{return Keyboard;}

    void setKey(unsigned char key){this->key = key;}
    void setModifiers(unsigned char modifiers){this->modifiers = modifiers;}
    void setRepeat(unsigned int repeat){this->repeat = repeat;}
    void setKeyboardEventType(KeyboardEventType type){this->type = type;}

    unsigned char getKey()const{return key;}
    unsigned char getModifiers()const{return modifiers;}
    unsigned int getRepeat()const{return repeat;}
    KeyboardEventType getKeyboardEventType()const{return type;}

private:
    unsigned char key;
    unsigned char modifiers;
    unsigned int repeat;
    KeyboardEventType type;
};

class TextInputEvent : public Event{
public:

    TextInputEvent(const std::string& text = "") : text(text){}

    virtual EventType getType()const{return TextInput;}

    void setText(const std::string& text){this->text = text;}
    const std::string& getText()const{return text;}

private:
    std::string text;
};

#endif