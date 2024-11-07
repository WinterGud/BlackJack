#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void init();
    
    void loadButtonPressSound(const std::string& path);
    void playButtonPressSound() const;
    void loadBackgroundMusic(const std::string& path);
    void playBackgroundMusic(int loops = -1);
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();

private:
    Mix_Music* m_backgroundMusic = nullptr;
    Mix_Chunk* m_buttonPressSound = nullptr; 
};