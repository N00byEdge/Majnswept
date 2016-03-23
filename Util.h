#pragma once
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <random>
#include "SFML/Graphics.hpp"

#define tilesize 16

static std::random_device randomDevice;
static std::mt19937 mersenneTwister ( randomDevice ( ) );

using namespace std;

struct Location {

    size_t x;
    size_t y;

};

static sf::Texture tileTexture1;
static sf::Texture tileTexture2;
static sf::Texture tileTexture3;
static sf::Texture tileTexture4;
static sf::Texture tileTexture5;
static sf::Texture tileTexture6;
static sf::Texture tileTexture7;
static sf::Texture tileTexture8;
static sf::Texture tileTextureBomb;
static sf::Texture tileTextureFlag;
static sf::Texture tileTextureEmpty;
static sf::Texture tileTextureHidden;
static sf::Texture tileTextureNoBomb;
static sf::Texture tileTextureQuestionMark;

void loadAssets ( size_t tilesize );
