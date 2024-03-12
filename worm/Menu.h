#pragma once

#include "Game.h"
#include <vector>
#include "Block.h"

class Menu
{
public:

    bool isRunning = false;
    std::vector<Block* > tags;
    int x_ = 250 ,y_ = 400;
    Block BG;

    void init();
    void input();
    int update();
    void render();
    void close();


    void AddTag(std::string Text);

    void SetPos(int x,int y);
};
