#include "readcsv.hpp"

bool read_csv(std::string filename, Data& database)
{
  std::ifstream fileopened(filename, std::ios::in);
  bool openned = fileopened.is_open();
  if (!openned) {
    std::cout << "failed to open " << filename << '\n';
  } else {
    std::string line;
    fileopened.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(fileopened, line)) {
      Place temp_place;
      std::string interest_line, interest;
      std::istringstream input(line);
      std::getline(input, temp_place.place, ',');
      std::getline(input, temp_place.type_of_place, ',');
      std::getline(input, temp_place.state, ',');
      if (input.peek() == '\"') {
        input.ignore(1, '\"');
        std::getline(input, interest_line, '\"');
        std::istringstream interestss(interest_line);
        while (std::getline(interestss, interest, ',')) {
          temp_place.interest_list.push_front(interest);
        };
        input.ignore(1, ',');
      } else {
        std::getline(input, interest, ',');
        temp_place.interest_list.push_front(interest);
      }
      std::getline(input, temp_place.personality, ',');
      std::getline(input, temp_place.cost, ',');
      for(char& i: temp_place.cost)
        i=std::tolower(i);
      //temp_place.print();
      database.insert_place(temp_place);
    }
  }
  fileopened.close();
  return openned;
}