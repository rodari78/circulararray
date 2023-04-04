#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
  QueueArray(int capacity = 10) : CircularArray<T>(capacity) {}
  virtual ~QueueArray() {}

  void enqueue(T data) {
    if (this->is_full()) {
      throw "Cola esta llena";
    }
    this->insert_back(data);
  }

  T dequeue() {
    if (this->is_empty()) {
      throw "Cola está vacía";
    }
    return this->pop_front();
  }

  T &front() {
    if (this->is_empty()) {
      throw "Cola está vacia";
    }
    return this->get_front();
  }

  T &back() {
    if (this->is_empty()) {
      throw "Cola está vacía";
    }
    return this->get_back();
  }


};