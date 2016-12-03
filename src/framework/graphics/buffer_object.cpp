#include "buffer_object.hpp"

void BufferObject::create(Type type){
    glGenBuffers(1, &id);
	this->type = type;
    created = true;
}

void BufferObject::dispose(){
    glDeleteBuffers(1, &id);
    created = false;
}

void BufferObject::bind(){
	glBindBuffer(type, id);
}

void BufferObject::allocate(const void* data, unsigned int size, AccessType accessType){
    glBufferData(type, size, data, accessType);
}

void BufferObject::write(const void* data, unsigned int offset, unsigned int size){
    glBufferSubData(type, offset, size, data);
}