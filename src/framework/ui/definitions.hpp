#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_

#include <memory>
#include <unordered_map>

class Box;
class Widget;

typedef std::shared_ptr<Box> BoxPtr;
typedef std::shared_ptr<Widget> WidgetPtr;

#endif