#include "buffer_object.hpp"

void BufferObject::create(){
    glGenBuffers(1, &id);
    created = true;
}

void BufferObject::dispose(){
    glDeleteBuffers(1, &id);
    created = false;
}

void BufferObject::bind(){
    glBindBuffer(id);
}

void BufferObject::allocate(const char* data, unsigned int size, Type type, AccessType accessType){
    glBufferData(type, size, data, accessType);
}

void BufferObject::write(const void* data, unsigned int offset, unsigned int size, Type type){
    glBufferSubData(type, offset, size, data);
}