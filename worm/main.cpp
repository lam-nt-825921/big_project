
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
            const int FPS =60;
            const int frameDelay=1000/FPS;
            Uint32 frameStart;
            int frameTime;
            while(game->isRunning)
            {
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

