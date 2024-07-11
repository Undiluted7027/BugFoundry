#include "Globals.hpp"

template <class T, class Q>
class Record{
    private:
        T id;
        Q data;
    public:
        Record(T id): id(id){}
        virtual ~Record() {}

        T getId() const{
            return id;
        };
        Q getData() const{
            return data;
        }
        void setID(T id){
            this->id = id;
        }
        void setData(Q data){
            this->data = data;
        }
};

