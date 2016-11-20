#ifndef _VERTEX_ARRAY_HPP_
#define _VERTEX_ARRAY_HPP_

#include "utils\point.hpp"

/*represents a buffer to fill with generic vertices data*/
template<typename t>
class VertexArray{
public:

private:
    std::vector<t> data;
};

#endif