#pragma once
#include <SDL.h>
#include <iostream>
#include "TextureManager.h"
#include <cstring>
#include <fstream>
#include <string>

class Block
{
public:

    SDL_Rect src,dest,tsrc,tdest;
    std::string type = "";
    std::string Text = "";
    SDL_Texture* text = nullptr;
    SDL_Texture* skin = nullptr;
    bool touch = false;
    bool isChosed = false;
    int scale = 1;

    Block();
    ~Block();

    void init(const char* path);
    void init(const char* path, std::string T,int sz = 15);
    void update();
    void render();

    void SetSkin(const char* path);
    void SetText(std::string path,int sz =15);
    void SetPos(int x, int y);
    void SetScale(int sc);

    SDL_Rect Get();
};
