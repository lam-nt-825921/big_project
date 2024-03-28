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
    AddTag(false,"BG");


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

short Menu:: update()
{
    if(listTags)
    {
        x_ = 250;
        y_ = 1000;
        for(short i = 0, e = tags.size()-1; i<=e; i++)if(tags[i]->CanChose)
        {
            y_-= tags[i]->dest.h + 10;
        }

        y_/=2;
        short cnt = 0;
        for(short i = 0, e = tags.size()-1; i<=e; i++)
        {
            if(tags[i]->CanChose)
            {
                y_ += tags[i]->dest.h/2;
                tags[i]->SetPos(x_, y_);
                y_ += tags[i]->dest.h/2 + 10;
            }
            tags[i]->update();
            if(tags[i]->CanChose && tags[i]->isChosed) return i;

        }
    }
    else
    {
        for(short i = 0, e = tags.size()-1; i<=e; i++)
        {
            tags[i]->update();
        }
    }
    return -1;
}

void Menu:: render()
{
    for(auto& t : tags)
    {
        t->render();
        t->isChosed = false;
    }
}

void Menu:: close()
{
    for(auto& t : tags)delete t;
    SDL_DestroyWindow(Window::window);
    SDL_DestroyRenderer(Window::renderer);
    SDL_Quit();
}
///----------------------------

void Menu:: AddTag(bool chose,std::string Text,std::string type,const char* path, short sz)
{
    tags.push_back(new Block);
    if(Text != "BG")
    {
        tags.back()-> init(chose,path,Text,sz);//const char* path, std::string T,short sz
        tags.back()->type = type;
    }
    else
    {
        tags.back()-> init(false,"image/menu_BG.bmp");
        tags.back()->type = type;
        tags.back()->SetScale(1);
        tags.back()->SetPos(250 , 400);
    }
}

void Menu:: SetPos(short x,short y)
{
    tags.back()->SetPos(x,y);
}
