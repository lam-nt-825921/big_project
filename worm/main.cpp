
#include "Game.h"
#include "Menu.h"
#include "Setting.h"



short Window:: Width = 500;
short Window::Height = 800;
SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;
SDL_Event Window::event;




int main( int argc, char* args[] )
{
    Game* game = new Game();
    Setting* setting = new Setting;


    Menu* menu = new Menu;
    menu->init();
    menu->listTags = true;

    menu->AddTag(true,"Start","Menu");
    menu->AddTag(true,"Setting","Menu");
    menu->AddTag(true,"Exit","Menu");

    while(menu->isRunning)
    {
        menu->input();

        switch(menu->update())
        {
        case 1:
        {
            if(game->ChoseLevel())
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
                if(game->Win)
                {
                    TextureManager::SetColor(255,107,0);
                    endGame->init(false,"image/LightBoard.bmp","you win",30);
                }
                else
                {
                    TextureManager::SetColor(0,140,0);
                    endGame->init(false,"image/DarkBoard.bmp","you lose",30);
                }
                endGame->SetPos(250,400);
                endGame->update();
                while(true)
                {
                    endGame->render();
                    SDL_RenderPresent(Window::renderer);
                    SDL_PollEvent(&Window::event);
                    if(Window::event.type == SDL_MOUSEBUTTONDOWN)break;
                    if(Window::event.type == SDL_KEYDOWN)break;
                }
                delete endGame;
                game->Close();
            }

        }
            break;
        case 2:
        {
            setting->init("text/MenuSetting.txt");
            setting->LoadCusstom();
            while(setting->isRunning)
            {
                setting->input();
                setting->update();
                setting->render();
            }
            setting->close();
        }
            break;
        case 3:
            menu->isRunning = false;
            break;
        default:
            break;
        }
        SDL_RenderClear( Window::renderer);
        menu->render();
        SDL_RenderPresent(Window::renderer);

    }
    menu->close();
    delete menu;




    return 0;
}

