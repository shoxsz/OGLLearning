#ifndef _DRAWER_
#define _DRAWER_

#include <memory>

class Widget;

/*Um Drawer é utilizado para renderizar um widget, todas as etapas de renderização são feitas
pelo usuário da API*/
class Drawer{
public:
	virtual ~Drawer(){}
	virtual void draw(Widget* widget) = 0;
};

typedef std::shared_ptr<Drawer> DrawerPtr;

#endif