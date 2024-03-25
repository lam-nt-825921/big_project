#pragma once
#include <SDL.h>
#include <iostream>
#include "TextureManager.h"
#include <cstring>
#include <fstream>
#include <string>

class Block
{
private:
    std::string UnchosedSkin = "image/Board.bmp";
    std::string ChosedSkin = "image/BoardChosed.bmp";
public:

    SDL_Rect src,dest,tsrc,tdest;
    bool CanChose = false;
    std::string type = "";
    std::string Text = "";
    SDL_Texture* text = nullptr;
    SDL_Texture* skin = nullptr;
    bool touch = false;
    bool isChosed = false;
    short scale = 1;
    short xPos = 0,yPos = 0;



    Block();
    ~Block();

    void init(bool Cch,const char* path);
    void init(bool Cch, const char* path, std::string T,short sz = 15);
    void update();
    void render();

    void SetSkin(const char* path);
    void SetText(std::string path,short sz =15);
    void SetPos(short x, short y);
    void SetScale(short sc);

    SDL_Rect Get();
};
