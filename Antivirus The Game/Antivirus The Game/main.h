#pragma once

#include <stdio.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <fstream>
#include <cassert>

#include <Windows.h>
#include <time.h>

using namespace std;

extern float scaleSize;
extern bool fmode;
extern sf::Font defaultFont;
const sf::String GAME_TITLE = "Antivirus: The Game";
const sf::String GAME_VERSION = "0.9.2";

const int SCREEN_WIDTH_DEFAULT=3200; // 3200
const int SCREEN_HEIGHT_DEFAULT=2400; // 2400

void createWindow(sf::RenderWindow &,bool);
string to_string_with_precision(float a_value, int n);
bool isNewUpdate(bool);