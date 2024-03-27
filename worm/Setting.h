#pragma once
#include <SDL.h>
#include "Block.h"

class Setting
{
public:
    //static short totalEnemys;
    //static short numEnermy[6];
    /** custom setting **/
    bool isCusstom = false;
    bool save = false;

    static short moneyStart;
    static bool hasClearWorm;

    void LoadCusstom();
    void SaveCusstom();

    ///------------
    /** scroll **/
    bool scroll = false;
    int lastPos;
    int nowPos;
    ///------------

    ///
    bool isRunning = false;
    std::vector<Block* > tags;
    void init(const char* path);
    void input();
    void update();
    void render();
    void close();


    void AddTag(bool chose,std::string Text,std::string type = "unChosed",const char* path = "image/Board.bmp", short sz =15,short x = 255,short y=255,short z =255);

};
