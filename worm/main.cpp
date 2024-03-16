
#include "Game.h"
#include "Menu.h"



int Window:: Width = 500;
int Window::Height = 800;
SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;
SDL_Event Window::event;




int main( int argc, char* args[] )
{
    Game* game = new Game();

    Menu* menu = new Menu;
    menu->init();

    menu->SetPos(Window::Width/2, Window::Height/3);

    menu->AddTag("Start");
    menu->AddTag("Exit");


    while(menu->isRunning)
    {
        menu->input();
        switch(menu->update())
        {
        case 1:
        {
            game->Init();

            int frameDelay;
            Uint32 frameStart;
            int frameTime;
            while(game->isRunning)
            {
                frameDelay=1000/Game::FPS;
                frameStart=SDL_GetTicks();
                game->Input();
                game->Update();
                game->Render();
                frameTime=SDL_GetTicks()-frameStart;
                if(frameTime<frameDelay)
                {
                    SDL_Delay(frameDelay-frameTime);
                }
            }
            Block *endGame = new Block;

            if(game->Win) endGame->init("image/Board.bmp","you win",30);
            else endGame->init("image/Board.bmp","you lose",30);
            endGame->SetPos(250,400);
            while(endGame->isChosed == false)
            {
                SDL_PollEvent(&Window::event);
                endGame->update();
                endGame->render();
                SDL_RenderPresent(Window::renderer);
            }
            delete endGame;
            game->Close();

        }
            break;
        case 2:
            menu->isRunning = false;
            break;
        default:
            break;
        }
        menu->render();
    }
    menu->close();
    delete menu;




    return 0;
}

