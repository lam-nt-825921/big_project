#pragma once
#include <SDL.h>
#include "Block.h"

class Setting
{
public:
    static short totalEnemys;
    static short numEnermy[6];

    bool scroll = false;
    int lastPos;
    int nowPos;
    bool isRunning = false;
    std::vector<Block* > tags;
    void init(const char* path);
    void LoadCusstom();
    void input();
    void update();
    void render();
    void close();
    void SaveCusstom();

    void AddTag(bool chose,std::string Text,std::string type = "unChosed",const char* path = "image/Board.bmp", short sz =15);

};
