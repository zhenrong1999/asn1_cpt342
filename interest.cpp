#include "interest.hpp"
Interest::Interest(std::string name,int place_hash_key){
    interest=name;
    insert_place_related(place_hash_key);
}

void Interest::insert_place_related(int place_hash_key)
{
  if (!find_place_related(place_hash_key))
    places_related.push_front(place_hash_key);
}

void Interest::remove_place_related(int place_hash_key){
    places_related.remove(place_hash_key);
}

bool Interest::find_place_related(int place_hash_key)
{
  bool found = false;
  for (int hash_key : places_related) {
    if (hash_key == place_hash_key) {
      found = true;
      break;
    }
  }
  return found;
}