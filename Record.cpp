#include "Globals.hpp"
#include "Record.hpp"

template <class T>
Record<T>::Record(const char *id, T data): id(id), data(data){}

template <typename T>
char *Record<T>::getId() const{
    return id;
};

template <typename T>
T Record<T>::getData() const{
    return data;
}

template <typename T>
void Record<T>::setID(const char* id){
    this->id = id;
}

template <typename T>
void Record<T>::setData(T &data){
    this->data = data;
}

template <typename T>
char *extractID(const Record<T> &record){
    return record.getId();
}
