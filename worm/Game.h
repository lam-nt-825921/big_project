#pragma once


#include <SDL.h>
#include <iostream>
#include "TextureManager.h"
#include <cstring>
#include <fstream>
#include <string>
#include "Vector2D.h"
#include "bullet.h"
#include "Object.h"
#include "worm.h"
#include "enemy.h"
#include "Block.h"

class Window
{
public:

    static short Width;
    static short Height;
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Event event;
};


class Game
{
private:

public:

    short Frame;
    short last_spawn;
    short numEnemys;
    int Time;
    int TimeStart;
    std::vector<std::pair<float, short> > spawn;

    static int FPS;
    static worm* wormMap[6][11];
    static short onGround[6];
    static int timer;
    static short money;

    static std::vector<Bullet*> wormBullet;
    static std::vector<worm*> worms;
    static std::vector<enemy*> enemys;

    static bool isRunning;
    static bool Win;

    bool isWriting = false;
    std::string write = "";
    short temp = 0;
    SDL_Rect tmpSrc,tmpRect;

    Game();
    ~Game();
    bool Init();
    void Input();
    void Update();
    void Render();
    void Close();
};

bool Collision(const SDL_Rect &A,const SDL_Rect &B);








