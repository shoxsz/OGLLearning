#include "buffer_object.hpp"

void BufferObject::create(Type type, AccessType access){
    this->type = type;
    this->accessType = access;
    glGenBuffers(1, &id);
}

void BufferObject::dispose(){
    glDeleteBuffers(1, &id);
}

void BufferObject::bind(){
    glBindBuffer(id);
}

void BufferObject::allocate(const char* data, unsigned int size){
    glBufferData(type, size, data, size);
}

void BufferObject::write(const void* data, unsigned int offset, unsigned int size){
    glBufferSubData(type, offset, size, data);
}