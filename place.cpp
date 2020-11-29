#include "place.hpp"

Place::Place() {}
Place::~Place() {
    interest.clear();
}
void Place::print()
{
  std::cout << "Place: " << place << '\n';
  std::cout << "Type: " << type_of_place << '\n';
  std::cout << "State: " << state << '\n';
  std::cout << "Interest: \n";
  for (std::string i : interest) {
    std::cout << '\t' << i << '\n';
  }
  std::cout << "Personality: " << personality << '\n';
  std::cout << "Cost: " << cost << "\n\n";
}
