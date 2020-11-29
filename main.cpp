#include "readcsv.hpp"
#include <iostream>
#include <list>
#include <map>
#include <string>

struct Data
{
  std::list<Place> place_db;
  std::map<int, std::string> interest_tag;
  std::map<int, std::string> place_tag;
};


int main()
{
  system("clear");
  Data db;
  db.interest_tag.insert(std::make_pair(std::hash<std::string>{}("nature"), "nature"));
  db.interest_tag.insert(std::make_pair(std::hash<std::string>{}("highland"), "highland"));
  db.interest_tag.insert(std::make_pair(std::hash<std::string>{}("npc"), "npc"));
  std::cout << std::hash<std::string>{}("nature") << '\n';
  std::cout << std::hash<std::string>{}("highland") << '\n';
  std::cout << std::hash<std::string>{}("nature") << '\n';
  auto search = db.interest_tag.find(std::hash<std::string>{}("nature"));
  if (db.interest_tag.end() != search)
    std::cout << "found " << search->second << '\n';
  //db.interest_tag.value_comp
  //read_csv("places.csv");
}