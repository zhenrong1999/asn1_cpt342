#ifndef INFERENCEENGGINE_H
#define INFERENCEENGGINE_H
#include "data.hpp"
#include <algorithm>
#include <forward_list>
#include <iostream>
struct Score
{
  int place_hash_key;
  int score = 0;
  Score(int place_hash);

};
struct Input_data
{
  std::string cost;
  std::string personality;
  std::forward_list<std::string> interest_priority;
};

std::list<Score> find_optimum(Input_data input, Data database);
void print_score_list(std::list<Score> score_list, Data database);
#endif