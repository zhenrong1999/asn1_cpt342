#include "inference_engine.hpp"

Score::Score(int place_hash)
{
  place_hash_key = place_hash;
}

std::list<Score> find_optimum(Input_data input, Data database)
{
  std::list<Score> score_list;
  for (auto node : database.place_list) {
    score_list.push_front(Score(node.first));
    score_list.front().place_hash_key = node.first;
    if (input.personality == node.second.personality)
      score_list.front().score += 100;
    if (input.cost == node.second.cost)
      score_list.front().score += 100;

    for (auto interest : input.interest_priority) {
      if (node.second.find_interest(interest))
        score_list.front().score += 10;
    }
  }
  score_list.sort([](const Score &first, const Score &second) {
    return first.score > second.score;
  });
  return score_list;
}

void print_score_list(std::list<Score> score_list, Data database){
    std::cout<<"Score\tPlace\n";
    for(auto score_item:score_list){
        auto place = database.place_list.find(score_item.place_hash_key)->second;
        std::cout<<score_item.score<<'\t'<<place.place<<'\n';
    }
    
}
