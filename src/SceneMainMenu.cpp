#include "SceneMainMenu.hpp"

void SceneMainMenu::initScene()
{
    // Textures
    m_ressourceManager.loadTexture(*m_renderer, "res/images/chessBoard.png", "chessBoard");

    SDL_QueryTexture(m_ressourceManager.getTexture("chessBoard"), NULL, NULL, &chessBoardRect.w, &chessBoardRect.h);
    chessBoardRect.x = (SCREEN_WIDTH / 2) - (chessBoardRect.w / 2);
    chessBoardRect.y = (SCREEN_HEIGHT / 2) - (chessBoardRect.h / 2);

    // Fonts
    m_ressourceManager.loadTextureFromFont(
        *m_renderer,
        "res/fonts/TravelingTypewriter.ttf", "Font_TravelingTypewriter", 40,
        "Font_TravelingTypewriter",
        "LE JEU D'ECHECS !", { 0, 0, 0, 255 }
    );

    SDL_QueryTexture(m_ressourceManager.getTexture("Font_TravelingTypewriter"), NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = (SCREEN_WIDTH / 2) - (textRect.w / 2);
    textRect.y = 100;

    // Musics
    m_ressourceManager.loadMusic("res/musics/background_music.ogg", "background_music");
    //Mix_PlayMusic(m_ressourceManager.getMusic("background_music"), -1);
    //Mix_VolumeMusic(10);

    // Chunks
    m_ressourceManager.loadChunk("res/sounds/sound.wav", "sound");

    // Callbacks
    m_inputManager.setMouseCallback(SDL_MOUSEBUTTONDOWN, [this](Uint8 button) { onMouseClick(button); });
}

void SceneMainMenu::cleanScene()
{
    // Textures
    m_ressourceManager.unloadTexture("chessBoard");
    
    // Fonts
    m_ressourceManager.unloadFont("Font_TravelingTypewriter");
    m_ressourceManager.unloadTexture("Font_TravelingTypewriter");

    // Musics
    Mix_HaltMusic();
    m_ressourceManager.unloadMusic("background_music");

    // Chunks
    m_ressourceManager.unloadChunk("sound");

    // Callbacks
    m_inputManager.clearCallbacks();
}

void SceneMainMenu::onMouseClick(Uint8 button)
{
    std::cout << "Mouse click !" << std::endl;
    std::cout << chessBoardRect.x << std::endl;
}

void SceneMainMenu::update(float deltaTime) {
    // Update here
    if (m_inputManager.isKeyboardKeyPressed(SDLK_ESCAPE) == true)
    {
        m_sceneManager.setCurrentScene("exitGame");
    }

    //std::cout << 1 / deltaTime << std::endl; // FPS
}

void SceneMainMenu::render() {
    SDL_SetRenderDrawColor(*m_renderer, mainMenuBackgroundColor.r, mainMenuBackgroundColor.g, mainMenuBackgroundColor.b, mainMenuBackgroundColor.a);
    SDL_RenderClear(*m_renderer);

    // Draw here
    SDL_RenderCopy(*m_renderer, m_ressourceManager.getTexture("chessBoard"), NULL, &chessBoardRect);
    SDL_RenderCopy(*m_renderer, m_ressourceManager.getTexture("Font_TravelingTypewriter"), NULL, &textRect);

    SDL_RenderPresent(*m_renderer);
}