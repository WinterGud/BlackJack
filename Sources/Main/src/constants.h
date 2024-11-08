#pragma once
#include <string>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int CARD_WIDTH = WINDOW_WIDTH / 6;
constexpr int CARD_HEIGHT = WINDOW_HEIGHT / 4;

//to run BlackJack.exe set BASE_PATH to empty string "";
const std::string BASE_PATH = "..\\..\\..\\BlackJack\\Sources\\Main\\";
const std::string MUSIC_PATH = BASE_PATH + "music\\back_music.mp3";
const std::string BUTTON_PRESS_SOUND_PATH = BASE_PATH + "music\\button_press.mp3";
const std::string LOG_PATH = BASE_PATH + "log.txt";

const std::string testFront = BASE_PATH + "assets\\testFrontCard.png";
const std::string CARD_BACK_TEXTURE = BASE_PATH + "assets\\testBackCard.png";
const std::string TABLE_TEXTURE = BASE_PATH + "assets\\table.png";

const std::string FontPath = BASE_PATH + "fonts\\font.ttf";
