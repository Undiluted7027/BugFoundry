#include "Globals.hpp"

template <class T>
class Record{
    private:
        char *id;
        T data;
    public:
        Record(const char *id, T data): id(id), data(data){}

        char *getId() const;
        T getData() const;
        void setID(const char *id);
        void setData(T &data);
};



