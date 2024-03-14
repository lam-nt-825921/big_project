#include "Menu.h"


void Menu::init()
{

    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout<<"init\n";
        Window::window = SDL_CreateWindow("Menu game con sau",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Window::Width,Window::Height,false);
        if(Window::window != nullptr)
        {
            std::cout<<"window\n";
            Window::renderer = SDL_CreateRenderer(Window::window,-1,0);
            if(Window::renderer != nullptr)
            {
                std::cout<<"renderer\n";
                SDL_SetRenderDrawColor(Window::renderer, 0, 20, 40, 255);
                if(TextureManager:: init())
                {
                    std::cout<<"texture manager\n";
                    isRunning = true;
                }
            }
        }
    }
    TextureManager::init();
    AddTag("");

    isRunning = true;
}

void Menu:: input()
{

    SDL_PollEvent(&Window::event);

    switch(Window::event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }

}

int Menu:: update()
{

    for(int i = 0, e = tags.size()-1; i<=e; i++)
    {
        if(i>0) tags[i]->SetPos(x_, y_ + i*(tags[i]->dest.h + 10));
        tags[i]->update();
        if(i>0&&tags[i]->isChosed) return i;

    }
    return -1;
}

void Menu:: render()
{
    SDL_RenderClear( Window::renderer);



    for(auto& t : tags)
    {
        t->render();
        t->isChosed = false;
    }


    SDL_RenderPresent(Window::renderer);
}

void Menu:: close()
{
    for(auto& t : tags)delete t;
    SDL_DestroyWindow(Window::window);
    SDL_DestroyRenderer(Window::renderer);
    SDL_Quit();
}
///----------------------------

void Menu:: AddTag(std::string Text)
{
    tags.push_back(new Block);
    if( tags.size()> 1 )tags.back()-> init("image/Board.bmp",Text);
    else
    {
        tags.back()->type = "BG";
        tags.back()->SetScale(1);
        tags.back()->SetPos(x_ , y_);
        tags.back()-> init("image/menu_BG.bmp");
    }
}

void Menu:: SetPos(int x,int y)
{
    x_=x;
    y_=y;
}
