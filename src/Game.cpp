#include "Game.hpp"

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr), frameStart(0), frameTime(0), deltaTime(0)
{

}

Game::~Game()
{
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    if(renderer) { SDL_DestroyRenderer(renderer); }
    if(window) { SDL_DestroyWindow(window); }
    SDL_Quit();
}

int Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    // Déclaration des flags
    int windowFlags = SDL_WINDOW_SHOWN;
    if(fullscreen) { windowFlags |= SDL_WINDOW_FULLSCREEN; }

    int rendererFlags = SDL_RENDERER_ACCELERATED;
    
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error SDL_Init : " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
    if(!window)
    {
        std::cerr << "Error SDL_CreateWindow : " << SDL_GetError() << std::endl;
        return -2;
    }
    
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(!renderer)
    {
        std::cerr << "Error SDL_CreateWindow : " << SDL_GetError() << std::endl;
        return -3;
    }

    // SDL_image
    if((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    {
        std::cerr << "Error IMG_Init : " << SDL_GetError() << std::endl;
        return -4;
    }

    // SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        std::cerr << "Error Mix_OpenAudio : " << SDL_GetError() << std::endl;
        return -5;
    }

    // SDL_ttf
    if(TTF_Init() != 0) { 
		std::cerr << "Error TTF_Init : " << SDL_GetError() << std::endl;
        return -6;
	}

    if(SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_WARP_MOTION, "1") != SDL_TRUE)
    {
		std::cerr << "Error SDL_SetHint : " << SDL_GetError() << std::endl;
        return -6;
    }

    initManagers();

    return 0;
}

void Game::initManagers()
{
    // RessourceManager
    ressourceManager = std::make_unique<RessourceManager>();

    // InputManager
    inputManager = InputManager();

    // SceneManager
    sceneManager = std::make_unique<SceneManager>();

    sceneManager->addScene("SceneMainMenu", std::make_unique<SceneMainMenu>(window, &renderer, *sceneManager, *ressourceManager, inputManager));

    sceneManager->setCurrentScene("SceneMainMenu");
}

void Game::run()
{
    isRunning = true;

    while(running())
    {
        frameStart = SDL_GetTicks64();

        update();
        if(running()) { render(); }

        frameTime = SDL_GetTicks64() - frameStart;

        if(1000 / TARGET_FRAMERATE > frameTime)
        {
            SDL_Delay((1000 / TARGET_FRAMERATE) - static_cast<Uint32>(frameTime));
        }

        deltaTime = (SDL_GetTicks64() - frameStart) / 1000.0f;
    }
}

void Game::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            sceneManager->setCurrentScene("exitGame");
            break;

        // Mouse
        case SDL_MOUSEWHEEL:
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            inputManager.updateMouse(event);
            break;

        // Keyboard
        case SDL_KEYUP:
        case SDL_KEYDOWN:
        case SDL_TEXTEDITING:
        case SDL_TEXTINPUT:
        case SDL_KEYMAPCHANGED:
        case SDL_TEXTEDITING_EXT:
            inputManager.updateKeyboard(event);
            break;

        default:
            break;
        }
    }

    if(sceneManager->getCurrentScene() != "exitGame") { sceneManager->updateCurrentScene(deltaTime); }

    if(sceneManager->getCurrentScene() == "exitGame") { isRunning = false; }
}

void Game::render()
{
    sceneManager->renderCurrentScene();
}

bool Game::running()
{
    return isRunning;
}