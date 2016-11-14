#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

#include <map>
#include <vector>
#include <memory>

#include "widget.hpp"

typedef std::map<int, std::vector<Widget*>> WidgetMap;

class Container{
public:
	Container(Widget* owner){
		this->owner = owner;
	}

	/*adiciona o widget ao container caso ainda não esteja adicionado*/
	bool add(Widget* child, int layer);
	/*remove o widget caso exista no container*/
	bool remove(Widget* child);
	/*remove a camada especificada*/
	bool removeLayer(int layer);
	/*retorna o mapa de widgets*/
	WidgetMap& getWidgets(){ return widgets; }
	/*obtém a lista de widgets da camda pedida*/
	std::vector<Widget*>& widgetList(int layer){ return widgets[layer]; };
	/*coloca o widget na camada especificada*/
	bool setWidgetLayer(Widget* widget, int layer);
	/*retorna a camada do widget*/
	int getWidgetLayer(Widget* widget);

	Widget* getOwner()const{ return owner; }
	unsigned int countLayers()const{ return widgets.size(); }

private:
	Widget* owner;	/*owner of the container*/
	WidgetMap widgets;
};

#endif