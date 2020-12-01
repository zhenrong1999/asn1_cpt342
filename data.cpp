#include "data.hpp"

bool Data::insert_place(Place inserted)
{
  int place_hash_key = hash_func(inserted.place);
  if (place_list.end() == place_list.find(place_hash_key)) {
    place_list.insert(std::make_pair(place_hash_key, inserted));
    for (std::string interest : inserted.interest_list) {
      int hash_key = hash_func(interest);
      auto search = interest_list.find(hash_key);
      if (interest_list.end() == search) {
        interest_list.insert(std::make_pair(hash_key, Interest(interest, place_hash_key)));
      }else{
        search->second.insert_place_related(place_hash_key);
      }
    }
  } else {
    return false;
  }
  return true;
}

void Data::print_place_list()
{
  for (auto node : place_list) {
    node.second.print();
  }
}

void Data::print_interest_list()
{
  for (auto node : interest_list) {
    std::cout << node.second.interest << '\n';
    for (int i :node.second.places_related){
      std::cout << place_list.find(i)->second.place<<'\n';
    }
    std::cout<<'\n';
  }
}

int hash_func(std::string input)
{
  return std::hash<std::string>{}(input);
}