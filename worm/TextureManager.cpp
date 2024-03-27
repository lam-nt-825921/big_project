#include "TextureManager.h"

TTF_Font* TextureManager:: font = nullptr;
SDL_Color TextureManager:: color = {255,255,255};

void TextureManager:: SetSize(short x)
{
    TTF_CloseFont(font);
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
    if(path == NULL)return nullptr;
    SDL_Surface* tmpSurface = SDL_LoadBMP(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

SDL_Texture* TextureManager:: LoadTexture( const char* path, short &W,short &H, short fr, short num)
{
    if(path == NULL)return nullptr;
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
    if(path == NULL)return nullptr;

    SDL_Surface* tmpSurface = SDL_LoadBMP(path);
    src = {0,0,tmpSurface->w,tmpSurface->h};
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

void TextureManager::SetColor(short x , short y, short z )
{
    color = {x,y,z};
}

SDL_Texture* TextureManager:: LoadTextTexture( const char* path,SDL_Rect& src)
{
    if(path == NULL)return nullptr;
    SDL_Surface* tmpSurface = TTF_RenderText_Solid(font,path,color);
    src = {0,0,tmpSurface->w,tmpSurface->h};
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    SetColor(255,255,255);
    return tex;

}


void TextureManager:: DrawTexture(SDL_Texture* tex,SDL_Rect src, SDL_Rect dest)
{
    if(tex ==nullptr)return;
    SDL_RenderCopy(Window::renderer,tex,&src,&dest);
}

