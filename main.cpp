#include "data.hpp"
#include "inference_engine.hpp"
#include "readcsv.hpp"
#include <iostream>
#include <string>

using namespace std;

void ClearScreen()
{
  system("CLS");
  //cout << string( 100, '\n' );
}

int Q_screen(string quetions, deque<string> options)
{
  int choice;
  int i;
  do {
    i = 0;
    ClearScreen();
    cout << quetions << '\n';
    for (auto option : options)
      cout << ++i << ". " << option << '\n';
    cout << "Input the number for your answer.\n";
    cin >> choice;
  } while (choice > options.size() || choice < 1);

  return choice;
}


string Q_cost_screen()
{
  ClearScreen();
  int choice = Q_screen("What is your money spent for the trip?", deque<string>{ "Affort to spend more (above RM 1000 per person per night)", "Budget is tight (below RM 1000 per person per night)" });
  string cost;
  if (choice == 1)
    cost = "high";
  else if (choice == 2)
    cost = "low";
  else
    cost = Q_cost_screen();
  return cost;
}

Input_data Q_test()
{
  string questions = "Which do you prefer?";
  deque<deque<string>> option_list = {
    //Prefer Luxury/ budget
    { "luxury travel", "budget travel" },
    //Prefer outdoors/indoor
    { "outdoor activity", "indoor activity" },
    //Prefer having more info/less info
    { "to have less info about the trip", "to have more info about the trip" },
    //Prefer planned/ not-planned
    { "advanture", "planned trip" }
  };
  string cost = Q_cost_screen();
  int choices[option_list.size()];
  int i = 0;
  for (auto options : option_list) {
    choices[i++] = Q_screen(questions, options);
  }

  Input_data input_data;
  if (choices[0] == 1 && cost == "high") {
    input_data.cost = "high";
  } else if (choices[0] == 2 && cost == "low") {
    input_data.cost = "low";
  } else {
    input_data.cost = "";
  }
  input_data.personality_max_tendency = 3;
  input_data.personality_tendency = 0;
  for (int j : { 1, 2, 3 }) {
    if (choices[j] == 1) {
      input_data.personality_tendency++;
    }
  }
  return input_data;
}


bool find_interest(string interest_to_find, const list<string> &interest_list)
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

void Q_interest_screen(list<string> &interest_priority, const map<int, Interest> &interest_list)
{
  int choice;
  int interest_hash_key[interest_list.size()];
  int i = 0;
  for (const auto node : interest_list)
    interest_hash_key[i++] = node.first;
  do {
    ClearScreen();
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
    if (choice <= interest_list.size() && choice > 0) {
      interest_priority.push_front(interest_list.find(interest_hash_key[choice - 1])->second.interest);
    }
  } while (choice != 0);
}

int main()
{
  ClearScreen();
  Data db;
  read_csv("places.csv", db);
  std::cout << "Place List:\n";
  db.print_place_list();
  std::cout << "Interest List:\n";
  db.print_interest_list();
  Input_data input;
  input = Q_test();
  Q_interest_screen(input.interest_priority, db.interest_list);
  cout << "Inferencing\n";
  std::list<Score> result = find_optimum(input, db);
  auto suggest = result.front();
  auto place = db.place_list.find(suggest.place_hash_key)->second;
  ClearScreen();
  std::cout << "Score: " << suggest.score << '\n';
  place.print();

  print_score_list(result, db);
}
