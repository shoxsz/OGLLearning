#ifndef _DRAWER_
#define _DRAWER_

#include "definitions.hpp"

#include <memory>

class Drawer{
public:
	virtual ~Drawer(){}
	virtual void draw(Widget* widget) = 0;
};

typedef std::shared_ptr<Drawer> DrawerPtr;

#endif