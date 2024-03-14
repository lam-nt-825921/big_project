#pragma once


#include <SDL.h>
#include <iostream>
#include "TextureManager.h"
#include <cstring>
#include <fstream>
#include <string>
#include "Vector2D.h"

class Window
{
public:

    static int Width;
    static int Height;
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Event event;
};


class Game
{
private:

public:


    static bool isRunning;

    bool isWriting = false;
    std::string write = "";
    int temp = 0;
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







