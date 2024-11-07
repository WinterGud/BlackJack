#include "SoundManager.h"

#include "Logger.h"
#include "Renderer.h"

SoundManager::SoundManager()
{
    if (Mix_Init(MIX_INIT_MP3) == 0)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
            "SDL_mixer initialization failed: " + std::string(Mix_GetError()) + '\n');
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
            "SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError()) + '\n');
    }
}

SoundManager::~SoundManager()
{
    if (m_buttonPressSound)
    {
        Mix_FreeChunk(m_buttonPressSound);
    }
    if (m_backgroundMusic)
    {
        Mix_FreeMusic(m_backgroundMusic);
    }
    Mix_CloseAudio();
    Mix_Quit();
}

void SoundManager::loadButtonPressSound(const std::string& path)
{
    m_buttonPressSound = Mix_LoadWAV(path.c_str());
    if (!m_buttonPressSound)
    {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
         "Failed to load button press sound: " + std::string(Mix_GetError()) + '\n');
    }
}

void SoundManager::playButtonPressSound() const
{
    if (m_buttonPressSound) {
        Mix_PlayChannel(-1, m_buttonPressSound, 0);
    }
}

void SoundManager::loadBackgroundMusic(const std::string& path)
{
    m_backgroundMusic = Mix_LoadMUS(path.c_str());
    if (!m_backgroundMusic) {
        Logger::getInstance(Renderer::getInstance().getWindowParams().LOG_PATH).log(
            WARNING,
         "Failed to load background music: " + std::string(Mix_GetError()) + '\n');
    }
}

void SoundManager::playBackgroundMusic(int loops)
{
    if (m_backgroundMusic) {
        Mix_PlayMusic(m_backgroundMusic, loops);
    }
}

void SoundManager::stopBackgroundMusic()
{
    Mix_HaltMusic();
}

void SoundManager::pauseBackgroundMusic()
{
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void SoundManager::resumeBackgroundMusic()
{
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}