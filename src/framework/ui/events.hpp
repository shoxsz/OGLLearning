#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

#include "utils/point.hpp"
#include "utils/size.hpp"

#include <string>

typedef Size Drag;

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

    MouseEvent():
        leftButton(false), 
        rightButton(false),
        middleButton(false){}

    virtual EventType getType()const{return Mouse;}
    virtual MouseEventType getMouseEventType()const = 0;

    void setLeft(bool left)const{leftButton = left;}
    void setRight(bool right)const{leftLeft = right;}
    void setMiddle(bool middle)const{leftMiddle = middle;}

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

class MouseMoveEvent : public MouseEvent{
public:
    MouseMoveEvent(): MouseMoveEvent(){}
    MouseMoveEvent(const Point& source, const Point& target) : MouseMoveEvent(){
        setSource(sourcePosition);
        setTarget(target);
    }

    virtual MouseEventType getMouseEventType()const{return MouseMove;}

    void setSource(const Point& source){this->sourcePosition = source;}
    void setTarget(const Point& target){this->position = target;}

    const Point& getSourcePosition()const{return sourcePosition;}
    const Point& getTargetPosition()const{return position;}

private:
    Point sourcePosition;
};

class MouseButtonEvent : public MouseEvent{
public:

    MouseButtonEvent(bool down = false, int clicks = 0) : MouseEvent(), type(down ? MouseDown : MouseUp), clicks(clicks){}

    virtual MouseEventType getMouseEventType()const{return type;}

    void setMouseDown(bool down){type = (down ? MouseDown : MouseUp);}
    void setClicks(int clicks){this->clicks = clicks;}

    int getClicks()const{return clicks;}
    bool isDoubleClick()const{return clicks == 2;}

private:
    int clicks;
    MouseEventType type;
};

class MouseScrollEvent : public MouseEvent{
public:

    MouseScrollEvent(int scrolledX = 0, int scrolledY = 0) : MouseEvent(), scrolledX(scrolledX), scrolledY(scrolledY), type(MouseScroll){}

    virtual MouseEventType getMouseEventType()const{return MouseScroll;}

    void setScrolledX(int scrolledX){this->scrolledX = scrolledX;}
    void setScrolledY(int scrolledY){this->scrolledY = scrolledY;}

    int getScrolledX()const{return scrolledX;}
    int getScrolledY()const{return scrolledY;}

private:
    int scrolledX;
    int scrolledY;
};

class MouseDragEvent : public MouseEvent{
public:

    MouseDragEvent(int draggedX = 0, int draggedY = 0):MouseMoveEvent(Drag(draggedX, draggedY)){}
    MouseDragEvent(const Drag& drag)drag(drag){}

    virtual MouseEventType getMouseEventType()const{return MouseDrag;}

    void setDrag(const Drag& drag){this->drag = drag;}
    void setDraggedX(int draggedX){this->drag.w = draggedX;}
    void setDraggedY(int draggedY){this->drag.h = draggedY;}

    int getDraggedX()const{return drag.x;}
    int getDraggedY()const{return drag.y;}
    Drag getDrag()const{return drag;}

private:
    Drag drag;
};

class KeyboardEvent : public Event{
public:

    enum KeyboardEventType{
        KeyDown,
        KeyUp
    };

    KeyboardEvent(unsigned char key = 0, unsigned char modifiers = 0, unsigned int repeat = 0, KeyboardEventType type = KeyDown):
    key(key), modifiers(modifiers), repeat(repeat), type(isDown ? KeyDown : keyUp){}

    virtual EventType getType()const{return Keyboard;}

    void setKey(unsigned char key){this->key = key;}
    void setModifiers(unsigned char modifiers){this->modifiers = modifiers;}
    void setRepeat(unsigned int repeat){this->repeat = repeat;}
    void setKeyboardEventType(KeyboardEventType type){this->type = type;}

    unsigned char getKey()const{return key;}
    unsigned char getModifiers()const{return modifiers;}
    unsigned int repeat()const{return repeat;}
    KeyboardEventType getKeyboardEventType()const{return type;}

private:
    unsigned char key;
    unsigned char modifiers;
    unsigned int repeat;
    KeyboardEventType type;
};

class TextInputEvent : public Event{
public:

    TextInput(const std::string& text = "") : text(text){}

    virtual EventType getType()const{return TextInput;}

    void setText(const std::string& text){this->text = text;}
    const std::string& getText()const{return text;}

private:
    std::string text;
};

#endif