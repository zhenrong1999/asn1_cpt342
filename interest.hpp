#ifndef INTEREST_H
#define INTEREST_H
#include <forward_list>
#include <string>
class Interest
{
public:
  std::string interest;
  std::forward_list<int> places_related;
  Interest(std::string name,int place_hash_key);
  void insert_place_related(int place_hash_key);
  void remove_place_related(int place_hash_key);
  bool find_place_related(int place_hash_key);
};
#endif