#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include "Game.h"


class TextureManager
{
private:

public:
    static TTF_Font *font;
    static SDL_Color color;
    static bool init();
    static void SetSize(int x);
    static SDL_Texture* LoadTexture( const char* path);
    static SDL_Texture* LoadTexture( const char*path, SDL_Rect& src);
    static SDL_Texture* LoadTextTexture( const char* path, SDL_Rect& src);
    static void DrawTexture(SDL_Texture* tex,SDL_Rect src, SDL_Rect dest);

};
