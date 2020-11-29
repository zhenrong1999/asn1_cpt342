#include <iostream>
#include <forward_list>
class Place{
    public:
        int id;
        std::string place;
        std::string type_of_place;
        std::string state;
        std::forward_list<std::string> interest;
        std::string personality;
        std::string cost;
    Place();
    ~Place();
    void print();
};
