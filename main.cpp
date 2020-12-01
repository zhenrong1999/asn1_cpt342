#include "data.hpp"
#include "inference_engine.hpp"
#include "readcsv.hpp"
#include <iostream>
#include <string>

using namespace std;
const char *clear_screen = "clear";
string Q_cost_screen()
{
  system(clear_screen);
  int choice;
  string cost;
  cout << "Whats is your cost spent for the trip?\n";
  cout << "1. High Cost (above RM 5000 per person)\n";
  cout << "2. Low Cost (below RM 5000 per person)\n";
  cout << "Input the number for your answer.\n";
  cin >> choice;
  if (choice == 1)
    cost = "high";
  else if (choice == 2)
    cost = "low";
  else
    cost = Q_cost_screen();
  return cost;
}

string Q_personality_screen()
{
  system(clear_screen);
  int choice;
  string personality;
  cout << "Whats is your personality?\n";
  cout << "1. I\n";
  cout << "2. D\n";
  cout << "Input the number for your answer.\n";
  cin >> choice;
  if (choice == 1)
    personality = "I";
  else if (choice == 2)
    personality = "D";
  else
    personality = Q_personality_screen();
  return personality;
}

bool find_interest(string interest_to_find, const forward_list<string> &interest_list)
{
  bool found = false;
  for (string interest : interest_list) {
    if (interest == interest_to_find) {
      found = true;
      break;
    }
  }
  return found;
}

void Q_interest_screen(forward_list<string> &interest_priority, const map<int, Interest> &interest_list)
{
  int choice;
  int interest_hash_key[interest_list.size()];
  int i = 0;
  for (const auto node : interest_list)
    interest_hash_key[i++] = node.first;
  do {
    system(clear_screen);

    cout << "Whats are you interested in?\n";
    i = 0;
    for (const auto node : interest_list) {
      if (!find_interest(node.second.interest, interest_priority))
        cout << ++i << ' ' << node.second.interest << '\n';
      else
        i++;
    }
    cout << "0 for submit.\n";
    cout << "Input the number for your answer.\n";
    cin >> choice;
    if(i<=interest_list.size()&&i>0){
      interest_priority.push_front(interest_list.find(interest_hash_key[choice-1])->second.interest);
    }
  } while (choice != 0);
}

int main()
{
  system(clear_screen);
  Data db;
  //db.interest_list.insert(std::make_pair(std::hash<std::string>{}("nature"), "nature"));
  //db.interest_list.insert(std::make_pair(std::hash<std::string>{}("highland"), "highland"));
  //db.interest_list.insert(std::make_pair(std::hash<std::string>{}("npc"), "npc"));
  //std::cout << std::hash<std::string>{}("nature") << '\n';
  //std::cout << std::hash<std::string>{}("highland") << '\n';
  //std::cout << std::hash<std::string>{}("nature") << '\n';
  //auto search = db.interest_list.find(std::hash<std::string>{}("nature"));
  //if (db.interest_list.end() != search)
  //  std::cout << "found " << search->second << '\n';
  //db.interest_list.value_comp

  read_csv("places.csv", db);
  std::cout << "Place List:\n";
  db.print_place_list();
  std::cout << "Interest List:\n";
  db.print_interest_list();
  Input_data input;
  input.cost = Q_cost_screen();
  input.personality = Q_personality_screen();
  Q_interest_screen(input.interest_priority, db.interest_list);
  std::list<Score> result = find_optimum(input, db);
  auto suggest = result.front();
  auto place = db.place_list.find(suggest.place_hash_key)->second;
  system(clear_screen);
  place.print();
  std::cout << "Score: " << suggest.score << '\n';

  print_score_list(result, db);
}