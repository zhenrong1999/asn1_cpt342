#ifndef READCSV_H
#define READCSV_H
#include "data.hpp"
#include "place.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <cctype>
#include <sstream>
bool read_csv(std::string filename, Data& database);
#endif