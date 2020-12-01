#ifndef PLACE_H
#define PLACE_H
#include <forward_list>
#include <iostream>


class Place
{
public:
  std::string place;
  std::string type_of_place;
  std::string state;
  std::forward_list<std::string> interest_list;
  std::string personality;
  std::string cost;
  Place();
  ~Place();
  void print();
  bool find_interest(std::string place_hash_key);
};
#endif