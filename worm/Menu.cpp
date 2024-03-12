#include "Menu.h"

void Menu::init()
{
    AddTag("");


    isRunning = true;
}

void Menu:: input()
{

    if(SDL_PollEvent(& Game::event)!=0)
    {
        switch(Game::event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
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
    SDL_RenderClear(Game:: renderer);



    for(auto& t : tags)
    {
        t->render();
        t->isChosed = false;
    }


    SDL_RenderPresent(Game:: renderer);
}

void Menu:: close()
{
    for(auto& t : tags)delete t;
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
