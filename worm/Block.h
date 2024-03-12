#pragma once
#include "Game.h"

class Block
{
public:

    SDL_Rect src,dest,tsrc,tdest;
    std::string type = "";
    std::string Text = "";
    SDL_Texture* text;
    SDL_Texture* skin;
    bool touch = false;
    bool isChosed = false;
    int scale = 2;

    Block();
    ~Block();

    void init(const char* path);
    void init(const char* path, std::string T);
    void update();
    void render();

    void SetSkin(const char* path);
    void SetText(std::string path);
    void SetPos(int x, int y);
    void SetScale(int sc);

    SDL_Rect Get();
};
