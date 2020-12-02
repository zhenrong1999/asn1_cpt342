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


    if (input.cost == node.second.cost)
      score_list.front().score += 100;
    else if (input.cost == "")
      score_list.front().score += 50;

    if ("I" == node.second.personality) {
      score_list.front().score += 100 * input.personality_tendency / input.personality_max_tendency;
    } else {
      score_list.front().score += 100 - 100 * input.personality_tendency / input.personality_max_tendency;
    }

    int weight = 100;
    int iteration = 1;
    for (auto interest : input.interest_priority) {
      if (iteration++ < input.interest_priority.size())
          weight /= 2;
      if (node.second.find_interest(interest)) {
        score_list.front().score += weight;
      }
    }
  }
  score_list.sort([](const Score &first, const Score &second) {
    return first.score > second.score;
  });
  return score_list;
}

void print_score_list(std::list<Score> score_list, Data database)
{
  std::cout << "Score\tPlace\n";
  for (auto score_item : score_list) {
    auto place = database.place_list.find(score_item.place_hash_key)->second;
    std::cout << score_item.score << '\t' << place.place << '\n';
  }
}
void Input_data::personality_inferece()
{
  if (personality_tendency > 2) {
    personality = "I";
  } else if (personality_tendency < 2) {
    personality = "D";
  }
}