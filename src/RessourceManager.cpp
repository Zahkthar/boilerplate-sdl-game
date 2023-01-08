#include "RessourceManager.hpp"

RessourceManager::RessourceManager() : textures(), fonts()
{
    
}

RessourceManager::~RessourceManager()
{

}

/*
 * Textures
 */

static SDL_Texture* loadTextureHelper(SDL_Renderer* renderer, const char* path) {
    SDL_Texture* texture = nullptr;

    texture = IMG_LoadTexture(renderer, path);
    if (texture == nullptr)
    {
        std::cerr << "Unable to load texture from " << path << ". Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

void RessourceManager::loadTexture(SDL_Renderer *renderer, const std::string &path, const std::string &textureName)
{
    textures[textureName] = SDL_Texture_ptr(loadTextureHelper(renderer, path.c_str()));
}

void RessourceManager::loadTexture(SDL_Texture *texture, const std::string &textureName)
{
    textures[textureName] = SDL_Texture_ptr(texture);
}

void RessourceManager::unloadTexture(const std::string &textureName)
{
    textures.erase(textureName);
}

SDL_Texture *RessourceManager::getTexture(const std::string &textureName)
{
    return textures[textureName].get();
}

/*
 * Fonts
 */

static TTF_Font *loadFontHelper(const char* path, const int fontSize)
{
    TTF_Font *font = nullptr;

    font = TTF_OpenFont(path, fontSize);
    if(font == nullptr)
    {
        std::cerr << "Unable to load font from " << path << ". Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return font;
}

void RessourceManager::loadFont(const std::string &path, const int fontSize, const std::string &fontName)
{
    fonts[fontName] = TTF_Font_ptr(loadFontHelper(path.c_str(), fontSize));
}

void RessourceManager::loadFont(TTF_Font *font, const std::string &fontName)
{
    fonts[fontName] = TTF_Font_ptr(font);
}

void RessourceManager::unloadFont(const std::string &fontName)
{
    fonts.erase(fontName);
}

TTF_Font *RessourceManager::getFont(const std::string &fontName)
{
    return fonts[fontName].get();
}

/*
 * Musics
 */

static Mix_Music *loadMusicHelper(const char* path)
{
    Mix_Music *music = nullptr;

    music = Mix_LoadMUS(path);
    if(music == nullptr)
    {
        std::cerr << "Unable to load music from " << path << ". Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return music;
}

void RessourceManager::loadMusic(const std::string &path, const std::string &musicName)
{
    musics[musicName] = Mix_Music_ptr(loadMusicHelper(path.c_str()));
}

void RessourceManager::loadMusic(Mix_Music *music, const std::string &musicName)
{
    musics[musicName] = Mix_Music_ptr(music);
}

void RessourceManager::unloadMusic(const std::string &musicName)
{
    musics.erase(musicName);
}

Mix_Music *RessourceManager::getMusic(const std::string &musicName)
{
    return musics[musicName].get();
}

/*
 * Chunks
 */

static Mix_Chunk *loadChunkHelper(const char* path)
{
    Mix_Chunk *chunk = nullptr;

    chunk = Mix_LoadWAV(path);
    if(chunk == nullptr)
    {
        std::cerr << "Unable to load chunk from " << path << ". Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return chunk;
}

void RessourceManager::loadChunk(const std::string &path, const std::string &chunkName)
{
    chunks[chunkName] = Mix_Chunk_ptr(loadChunkHelper(path.c_str()));
}

void RessourceManager::loadChunk(Mix_Chunk *chunk, const std::string &chunkName)
{
    chunks[chunkName] = Mix_Chunk_ptr(chunk);
}

void RessourceManager::unloadChunk(const std::string &chunkName)
{
    chunks.erase(chunkName);
}

Mix_Chunk *RessourceManager::getChunk(const std::string &chunkName)
{
    return chunks[chunkName].get();
}

/*
 * Font <=> Texture
 */

void RessourceManager::loadTextureFromFont(SDL_Renderer *renderer, const std::string &path, const std::string &fontName, const int fontSize, const std::string &textureName, const std::string text, const SDL_Color &textColor)
{
    loadFont(path, fontSize, fontName);
    loadTextureFromFont(renderer, getFont(fontName), textureName, text, textColor);
}

void RessourceManager::loadTextureFromFont(SDL_Renderer *renderer, TTF_Font* font, const std::string &textureName, const std::string text, const SDL_Color &textColor)
{
    SDL_Surface *fontSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    loadTexture(SDL_CreateTextureFromSurface(renderer, fontSurface), textureName);
    SDL_FreeSurface(fontSurface);
}