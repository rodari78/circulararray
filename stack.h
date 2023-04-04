#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
public:
  void insert_back(T data) { this->push_back(data); }

  T remove_back() { return this->pop_back(); }

  T get_back() { return (*this)[this->size() - 1]; }
  
};