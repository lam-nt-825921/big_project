#pragma once

#include <SDL_ttf.h>
#include <SDL.h>


class TextureManager
{
private:

public:
    static TTF_Font *font;
    static SDL_Color color;
    static void init();
    static SDL_Texture* LoadTexture(SDL_Renderer* ren, const char* path);
    static SDL_Texture* LoadTexture(SDL_Renderer* ren, const char*path, SDL_Rect& src);
    static SDL_Texture* LoadTextTexture(SDL_Renderer* ren, const char* path, SDL_Rect& src);
    static void DrawTexture(SDL_Renderer* ren,SDL_Texture* tex,SDL_Rect src, SDL_Rect dest);

};
