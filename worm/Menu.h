#pragma once

#include <vector>
#include "Block.h"


class Menu
{
public:



    bool isRunning = false;
    std::vector<Block* > tags;
    short x_ = 250 ,y_ = 400;

    bool listTags = false;

    void init();
    void input();
    short update();
    void render();
    void close();


    void AddTag(bool chose,std::string Text,std::string type = "unChosed",const char* path = "image/Board.bmp", short sz =15);

    void SetPos(short x,short y);
};
