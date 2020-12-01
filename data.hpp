#ifndef DATA_H
#define DATA_H
#include "place.hpp"
#include "interest.hpp"
#include <iostream>
#include <list>
#include <map>
struct Data
{
  std::map<int, Place> place_list;
  std::map<int, Interest> interest_list;

  bool insert_place(Place inserted);
  void print_place_list();
  void print_interest_list();
};
int hash_func(std::string);
#endif