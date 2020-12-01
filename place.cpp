#include "place.hpp"


Place::Place() {}
Place::~Place()
{
  interest_list.clear();
}
void Place::print()
{
  std::cout << "Place: " << place << '\n';
  std::cout << "Type: " << type_of_place << '\n';
  std::cout << "State: " << state << '\n';
  std::cout << "Interest: \n";
  for (std::string i : interest_list) {
    std::cout << '\t' << i << '\n';
  }
  std::cout << "Personality: " << personality << '\n';
  std::cout << "Cost: " << cost << "\n\n";
}
bool Place::find_interest(std::string interest_to_find)
{
  bool found = false;
  for (std::string interest : interest_list) {
    if (interest == interest_to_find) {
      found = true;
      break;
    }
  }
  return found;
}