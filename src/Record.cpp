/* Record.cpp
REVISION HISTORY:
Rev. 1 - 24/07/04 Original by Sanchit Jain
-------------------------------------------------------*/
#include "../include/Globals.hpp"
#include "../include/Record.hpp"

template <class T>
Record<T>::Record(const char *id, T data): id(id), data(data){}

template <typename T>
char *Record<T>::getId() const{
    return id;
};

/*
Returns the ID member of Record template.
--------------------------------------------------------------------*/
template <typename T>
T Record<T>::getData() const{
    return data;
}

/*
Returns the data member of Record template.
--------------------------------------------------------------------*/
template <typename T>
void Record<T>::setID(const char* id){
    this->id = id;
}

/*
Set the ID member of Record template.
--------------------------------------------------------------------*/
template <typename T>
void Record<T>::setData(T &data){
    this->data = data;
}

/*
Set the data member of Record template.
--------------------------------------------------------------------*/
template <typename T>
char *extractID(const Record<T> &record){
    return record.getId();
}

/*
Retrieves the id of Record object and returns it.
--------------------------------------------------------------------*/