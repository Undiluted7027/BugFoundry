#include "Globals.hpp"

template <class T>
class Record{
    private:
        T id;
    public:
        Record(T id): id(id){}
        virtual ~Record() {}

        T getId() const{
            return id;
        };
        void setID(T id){
            this->id = id;
        }
};

