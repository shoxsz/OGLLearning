#ifndef _POINTER_ALLOCATOR_HPP_
#define _POINTER_ALLOCATOR_HPP_

#include <memory>

/*allocator for use with raw pointer and stl containers

for example:
    std::vector<int*, pointer_allocator<int*>>

this calss considers that the type in the container is a vector
and deallocates it as one*/

template<class type>
class pointer_allocator{
public:
    typedef type value_type;
    pointer_allocator(){}

    value_type* allocate(std::size_t n){
        value_type* data = new value_type[n];

        for(unsigned int i = 0; i < n; i++)
            data[i] = nullptr;
            
        return data;
    }

    void deallocate(value_type* data, std::size_t n){
        for(unsigned int i = 0; i < n; i++){
            delete [] (data[i]);
        }
        delete data;
    }
};

template <class value_type, class U>
bool operator==(const pointer_allocator<value_type>&, const pointer_allocator<U>&){
    return true;
}

template <class value_type, class U>
bool operator!=(const pointer_allocator<value_type>&, const pointer_allocator<U>&){
    return false;
}


#endif