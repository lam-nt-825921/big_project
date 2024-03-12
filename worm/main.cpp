
#include "Game.h"
#include "Menu.h"




int main( int argc, char* args[] )
{
    Game* game = new Game();
    game->Init();

    Menu* menu = new Menu;
    menu->init();

    menu->SetPos(game->Width/2, game->Height/3);

    menu->AddTag("Start");
    menu->AddTag("Exit");

    while(menu->isRunning)
    {
        menu->input();
        switch(menu->update())
        {
        case 1:
        {
            game->isRunning = true;
            while(game->isRunning)
            {

                game->Input();
                game->Update();
                game->Render();
            }
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
    game->Close();
    menu->close();
    delete menu;




    return 0;
}

