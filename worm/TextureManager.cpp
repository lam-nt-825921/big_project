#include "TextureManager.h"

TTF_Font* TextureManager:: font = nullptr;
SDL_Color TextureManager:: color = {50,50,50};

void TextureManager:: init()
{
    TTF_Init();
    font = TTF_OpenFont("font/font.ttf",28);
}

SDL_Texture* TextureManager:: LoadTexture(SDL_Renderer* ren, const char* path)
{

    SDL_Surface* tmpSurface = SDL_LoadBMP(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

SDL_Texture* TextureManager:: LoadTexture(SDL_Renderer* ren, const char* path,SDL_Rect& src)
{
    SDL_Surface* tmpSurface = SDL_LoadBMP(path);
    src = {0,0,tmpSurface->w,tmpSurface->h};
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

SDL_Texture* TextureManager:: LoadTextTexture(SDL_Renderer* ren, const char* path,SDL_Rect& src)
{

    SDL_Surface* tmpSurface = TTF_RenderText_Solid(font,path,color);
    src = {0,0,tmpSurface->w,tmpSurface->h};
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

void TextureManager:: DrawTexture(SDL_Renderer* ren,SDL_Texture* tex,SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren,tex,&src,&dest);
}
