#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    bool isSorted=false;
    
public:
    CircularArray(int _capacity = 10);
    virtual ~CircularArray(){}
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T& operator[](int);    
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");


private:
    int next(int);
    int prev(int);
   
};

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;//empty
}

template <class T>
bool CircularArray<T>::is_empty(){
    return (this->front == -1 && this->back==-1);
}


template <class T>
bool CircularArray<T>::is_full(){
    cout <<this->size() << endl;
    return (this->capacity == this->size());
}

template <class T>
void CircularArray<T>::push_front(T data){
    if (this->is_full()){
        throw "Array lleno";
    }
    if (this->is_empty()) this->back= this->front=0;
    else this->front = this->prev(this->front);
    this->array[this->front] = data; 
    this->isSorted=false;
}

template <class T>
void CircularArray<T>::push_back(T data){

    if (this->is_full()){
        throw "Array lleno";
    }

    if (this->is_empty()) this->back= this->front=0;
    else this->back = this->next(this->back); 
    this->array[this->back] = data;
    this->isSorted=false;

}

template <class T>
void CircularArray<T>::insert(T data, int pos){

    if (this->is_full()) throw "Array lleno";
    if (pos >= this->capacity) throw "Posición invalida";
    if (pos >= this->size()) throw "Posición invalida";

    if (pos==0) this->push_front(data);
    if (pos==this->size()-1) this->push_back(data);

    for (int i = this->size(); i>pos;i--)
    {
        array[(this->front+i) % this->capacity] = array[(this->front+i-1)% this->capacity];
    }

    array[(this->front+pos) % this->capacity] =data;
    this->back = this->next(this->back);

}

template <class T>
void CircularArray<T>::reverse(){
    
    int cant = this->size()/2;
    int desc = this->front + this->size()-1;
    
    for (int i=0; i<cant; i++){

        swap(array[(i+this->front) % this->capacity], array[(desc) % this->capacity]);
        desc--;        
    }
    this->isSorted=false;
    
}

template <class T>
void CircularArray<T>::sort(){

    for (int i = 0; i < this->size(); i++) {
        for (int j = this->front; j < this->front + this->size() - 1; j++) {
            if (array[j % this->capacity]  > array[(j + 1) % this->capacity]) {
                swap(array[j % this->capacity], array[(j + 1) % this->capacity]);
            }
        }
    }
    this->isSorted=true;
}


template <class T>
string CircularArray<T>::to_string(string sep){
    
    if (this->is_empty()) throw "No existen datos";

    string sresult="";

    int pos= this->front;
    while (pos != this->back){
        sresult += std::to_string(array[pos])+sep;
        pos = this->next(pos);
        if (this->back==pos && this->front!=this->back) sresult += std::to_string(array[pos])+sep;
    } ;
    return sresult;
}

template <class T>
T CircularArray<T>::pop_front(){

    if (this->is_empty()){
        throw "Array vacío";
    }
    T eliminado = array[this->front];
    if (this->front== this->back) this->front = this->back =-1;
    else this->front =  this->next(this->front);

    return eliminado;
}

template <class T>
T CircularArray<T>::pop_back(){
    if (this->is_empty()){
        throw "Array vacío";
    }
    T eliminado = array[this->back];
    if (this->front== this->back) this->front = this->back =-1;
    else this->back =  this->prev(this->back);
    
    return eliminado;
}

template <class T>
int CircularArray<T>::size(){

    int elements=0;
    
    if ((this->back -this->front) >=0) elements = this->back -this->front + 1;
    else elements = this->back + this->capacity - this->front + 1;
    return elements;
}

template <class T>
void CircularArray<T>::clear(){

    this->front= -1;
    this->back = -1;

}

template <class T>
bool CircularArray<T>::is_sorted(){
    return this->isSorted;
}

template <class T>
int CircularArray<T>::next(int i){
    return (i+1)% this->capacity;
}

template <class T>
int CircularArray<T>::prev(int i){
    return (i==0) ? this->capacity-1 : (i-1)% this->capacity;
}

template <class T>
T& CircularArray<T>::operator[](int i){
    if ((this->front+i)>=capacity) {
        throw "Indice no existe";
    }
    return this->array[(this->front+i) % this->capacity];
} 