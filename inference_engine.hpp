#ifndef INFERENCEENGGINE_H
#define INFERENCEENGGINE_H
#include "data.hpp"
#include <algorithm>
#include <deque>
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
  unsigned int personality_tendency = 0;
  unsigned int personality_max_tendency;
  std::list<std::string> interest_priority;
void personality_inferece();

};

std::list<Score> find_optimum(Input_data input, Data database);
void print_score_list(std::list<Score> score_list, Data database);
#endif