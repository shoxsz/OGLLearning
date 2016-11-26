#ifndef _POINTER_ALLOCATOR_HPP_
#define _POINTER_ALLOCATOR_HPP_

#include <memory>

/*allocator for raw pointers*/

template<class T, bool is_char>
class pointer_allocator{
  typedef T value_type;

  pointer_allocator(){}

  template <class U> pointer_allocator(const pointer_allocator<U>& other);

  T* allocate(std::size_t n){
      T* data = new T[n];

      if(is_char)
        data[n-1] = '\0';

      return data;
  }

  void deallocate(T* data, std::size_t n){
      delete [] data;
  }
};
template <class T, class U>
bool operator==(const pointer_allocator<T>&, const pointer_allocator<U>&){
    return true;//the deallocate method can deallocate any type
}

template <class T, class U>
bool operator!=(const pointer_allocator<T>&, const pointer_allocator<U>&){
    return false;
}

#endif