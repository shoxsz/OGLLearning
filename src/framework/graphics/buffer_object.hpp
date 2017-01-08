#ifndef _BUFFER_OBJECT_HPP_
#define _BUFFER_OBJECT_HPP_

#include <GL/glew.h>

#include "enums.hpp"

class BufferObject{
public:
    BufferObject():created(false), id(0){}

    void create(Type type);
    void dispose();

    void bind();
    
    //glBufferData
    void allocate(const void* data, unsigned int size, AccessType accessType);
    //glBufferSubdata
    void write(const void* data, unsigned int offset, unsigned int size);

    bool isCreated()const{return created;}

private:
	Type type;
    bool created;
    unsigned int id;
};

#endif