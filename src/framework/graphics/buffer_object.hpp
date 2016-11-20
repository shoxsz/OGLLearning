#ifndef _BUFFER_OBJECT_HPP_
#define _BUFFER_OBJECT_HPP_

#include <SDL_opengl.h>

class BufferObject{
public:
    enum Type{
        Array = GL_ARRAY_BUFFER,
        Index = GL_ELEMENT_ARRAY_BUFFER
    }

    enum AccessType{

    }

    void create(Type type, AccessType access);
    void dispose();

    void bind();
    
    void allocate(const void* data, unsigned int dize);
    void write(const void* data, unsigned int offset, unsigned int size);

    Type getType()const{return type;}
    AccessType getAccessType()const{return acessType;}

private:
    Type type;
    AccessType accessType;
    unsigned int id;
    unsigned int size;
};

#endif