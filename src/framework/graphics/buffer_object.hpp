#ifndef _BUFFER_OBJECT_HPP_
#define _BUFFER_OBJECT_HPP_

#include <gl/glew.h>

#include "enums.hpp"

class BufferObject{
public:
    BufferObject():created(false), id(0){}

    void create();
    void dispose();

    void bind();
    
    //glBufferData
    void allocate(const void* data, unsigned int size, Type type, AccessType accessType);
    //glBufferSubdata
    void write(const void* data, unsigned int offset, unsigned int size, Type type);

    bool isCreated()const{return created;}

private:
    bool created;
    unsigned int id;
};

#endif