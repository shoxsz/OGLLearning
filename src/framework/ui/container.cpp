#include "container.hpp"

bool Container::add(Widget* child, int layer){
	unsigned int layers = widgets.size();
	for (unsigned int i = 0; i < layers; i++){
		for (unsigned int j = 0; j < widgets[i].size(); j++){
			if (widgets[i][j] == child)
				return false;
		}
	}
	widgets[layers].push_back(child);
	child->setParent(owner);
	return true;
}

bool Container::remove(Widget* child){
	unsigned int layers = widgets.size();
	for (unsigned int i = 0; i < layers; i++){
		for (unsigned int j = 0; j < widgets[i].size(); j++){
			if (widgets[i][j] == child){
				widgets[i].erase(widgets[i].begin() + j);
				return true;
			}
		}
	}
	return false;
}

bool Container::removeLayer(int layer){
	WidgetMap::iterator it;
	if ((it = widgets.find(layer)) != widgets.end()){
		widgets.erase(it);
		return true;
	}
	return false;
}

bool Container::setWidgetLayer(Widget* widget, int layer){
	WidgetMap::iterator it;
	if ((it = widgets.find(layer)) != widgets.end()){
		if (remove(widget)){
			it->second.push_back(widget);
			return true;
		}
	}
	return false;
}

int Container::getWidgetLayer(Widget* widget){
	unsigned int layers = widgets.size();
	for (unsigned int i = 0; i < layers; i++){
		for (unsigned int j = 0; j < widgets[i].size(); j++){
			if (widgets[i][j] == widget){
				return i;
			}
		}
	}
	return 0;
}