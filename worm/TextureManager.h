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
    static void SetSize(short x);

    static void SetColor(short x = 255, short y= 255, short z = 255);
    static SDL_Texture* LoadTexture( const char* path);
    static SDL_Texture* LoadTexture( const char* path, short &W,short &H, short fr, short num);
    static SDL_Texture* LoadTexture( const char*path, SDL_Rect& src);
    static SDL_Texture* LoadTextTexture( const char* path, SDL_Rect& src);



    static void DrawTexture(SDL_Texture* tex,SDL_Rect src, SDL_Rect dest);

};
