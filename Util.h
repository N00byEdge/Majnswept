#pragma once
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <random>
#include "SFML/Graphics.hpp"

#define tilesize 16

using namespace std;

struct Location {

    size_t x;
    size_t y;

};

void loadAssets ( );
