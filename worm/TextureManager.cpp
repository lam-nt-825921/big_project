#include "TextureManager.h"

TTF_Font* TextureManager:: font = nullptr;
SDL_Color TextureManager:: color = {255,255,255};

void TextureManager:: SetSize(int x)
{
    font = TTF_OpenFont("font/font.ttf",x);
}

bool TextureManager:: init()
{
    if(TTF_Init() < 0) return false;
    font = TTF_OpenFont("font/font.ttf",18);
    if(font == nullptr) return false;
    return true;
}

SDL_Texture* TextureManager:: LoadTexture( const char* path)
{

    SDL_Surface* tmpSurface = SDL_LoadBMP(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

SDL_Texture* TextureManager:: LoadTexture( const char* path, int &W,int &H, int fr, int num)
{
    SDL_Surface* tmpSurface = SDL_LoadBMP(path);

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    W = tmpSurface->w;
    H = tmpSurface->h;
    W = W/fr;
    H = H/num;
    SDL_FreeSurface(tmpSurface);
    return tex;
}

SDL_Texture* TextureManager:: LoadTexture( const char* path,SDL_Rect& src)
{
    SDL_Surface* tmpSurface = SDL_LoadBMP(path);
    src = {0,0,tmpSurface->w,tmpSurface->h};
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

SDL_Texture* TextureManager:: LoadTextTexture( const char* path,SDL_Rect& src)
{

    SDL_Surface* tmpSurface = TTF_RenderText_Solid(font,path,color);
    src = {0,0,tmpSurface->w,tmpSurface->h};
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;

}


void TextureManager:: DrawTexture(SDL_Texture* tex,SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Window::renderer,tex,&src,&dest);
}

