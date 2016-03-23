#pragma once
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <random>
#include "SFML/Graphics.hpp"

static const size_t npos = -1;

static float maxFPS;
static int sleepRecalculatePeriod;

static std::random_device randomDevice;
static std::mt19937 mersenneTwister ( randomDevice ( ) );

using namespace std;

struct Location {

    size_t x;
    size_t y;

};

void loadAssets ( size_t tilesize );
