#include "Globals.hpp"
#include "Record.hpp"

template <class T, class Q>
Record<T, Q>::Record(T id, Q data): id(id), data(data){}

template 
T Record::getId() const{
    return id;
};

Q Record::getData() const{
    return data;
}
void Record::setID(T id){
    this->id = id;
}
void Record::setData(Q data){
    this->data = data;
}

template <typename T, typename Q>
Q extractID(const Record<T, Q> &record){
    return record.getId();
}
