#ifndef RESSOURCE_MANAGER_HPP_INCLUDED
#define RESSOURCE_MANAGER_HPP_INCLUDED

#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// Texture
struct SDL_Texture_Deleter { void operator()(SDL_Texture *texture) { SDL_DestroyTexture(texture); } };
using SDL_Texture_ptr = std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>;

// Fonts
struct TTF_Font_Deleter { void operator()(TTF_Font *font) { TTF_CloseFont(font); } };
using TTF_Font_ptr = std::unique_ptr<TTF_Font, TTF_Font_Deleter>;

// Musics
struct Mix_Music_Deleter { void operator()(Mix_Music *music) { Mix_FreeMusic(music); } };
using Mix_Music_ptr = std::unique_ptr<Mix_Music, Mix_Music_Deleter>;

// Chunks
struct Mix_Chunk_Deleter { void operator()(Mix_Chunk *chunk) { Mix_FreeChunk(chunk); } };
using Mix_Chunk_ptr = std::unique_ptr<Mix_Chunk, Mix_Chunk_Deleter>;

class RessourceManager
{
public:
    RessourceManager();
    ~RessourceManager();

    // Textures
    void loadTexture(SDL_Renderer *renderer, const std::string &path, const std::string &textureName);
    void loadTexture(SDL_Texture *texture, const std::string &textureName);
    void unloadTexture(const std::string &textureName);
    SDL_Texture *getTexture(const std::string &textureName);

    // Fonts
    void loadFont(const std::string &path, const int fontSize, const std::string &fontName);
    void loadFont(TTF_Font *font, const std::string &fontName);
    void unloadFont(const std::string &fontName);
    TTF_Font *getFont(const std::string &fontName);

    // Musics
    void loadMusic(const std::string &path, const std::string &musicName); // Can load FLAC, MP3, Ogg, VOC, and WAV
    void loadMusic(Mix_Music *music, const std::string &musicName);
    void unloadMusic(const std::string &musicName);
    Mix_Music *getMusic(const std::string &musicName);

    // Chunks
    void loadChunk(const std::string &path, const std::string &chunkName); // Can load FLAC, MP3, Ogg, VOC, and WAV
    void loadChunk(Mix_Chunk *chunk, const std::string &chunkName);
    void unloadChunk(const std::string &chunkName);
    Mix_Chunk *getChunk(const std::string &chunkName);

    // Font <=> Texture
    void loadTextureFromFont(SDL_Renderer *renderer, const std::string &path, const std::string &fontName, const int fontSize, const std::string &textureName, const std::string text, const SDL_Color &textColor);
    void loadTextureFromFont(SDL_Renderer *renderer, TTF_Font* font, const std::string &textureName, const std::string text, const SDL_Color &textColor);

private:
    // Textures
    std::unordered_map<std::string, SDL_Texture_ptr> textures;

    // Fonts
    std::unordered_map<std::string, TTF_Font_ptr> fonts;

    // Musics
    std::unordered_map<std::string, Mix_Music_ptr> musics;

    // Chunks
    std::unordered_map<std::string, Mix_Chunk_ptr> chunks;
};

#endif // RESSOURCE_MANAGER_HPP_INCLUDED