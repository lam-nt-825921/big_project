#include "Setting.h"
#include "Game.h"
#include "TextureManager.h"

short Setting::moneyStart = 0;
bool Setting::hasClearWorm = true;

void Setting:: AddTag(bool chose,std::string Text,std::string type,const char* path, short sz, short x, short y, short z)
{
    if(Text != "")
    {
        tags.push_back(new Block);
        TextureManager::SetColor(x,y,z);
        tags.back()-> init(chose,path,Text,sz);//const char* path, std::string T,short sz
        tags.back()->type = type;
    }

}

void Setting:: init(const char* path)
{
    isRunning = true;

    AddTag(true, "Null","back home","image/BackHomeBoard.bmp");
    tags.back()->SetPos(30,30);

    {/// load setting
        std::ifstream getBlock(path); // Open file for reading
        if(getBlock.is_open() == false)
        {
            std::cout<<"loi mo file\n";
            return;
        }
        int numBlock = 0;
        short xPos, yPos, sz;
        bool chose;
        std::string Text, Type, Path;

        getBlock>>numBlock;

        for(short i=0 ;i < numBlock; i++)
        {
            getBlock.ignore();
            getline(getBlock,Text);
            getline(getBlock,Type);
            getBlock >> chose >> Path >>xPos >>yPos >> sz;
           // std::cout<<chose<<" "<<Text<<" "<<Type<<" "<<Path<<'\n';
            if(Path == "Null")
            {
                AddTag(chose,Text,Type,NULL,sz);
            }
            else
            {
                AddTag(chose,Text,Type,Path.c_str(),sz);
            }
            tags.back()->SetPos(xPos,yPos);
        }
        getBlock.close(); // Close the file
    }
}

void Setting::LoadCusstom()
{
    std::ifstream getCusstom("text/cusstomSetting.txt");
    getCusstom>>moneyStart;
    getCusstom>>hasClearWorm;
    getCusstom.close();
    save = false;
    isCusstom = true;
}

void Setting::input()
{
    SDL_PollEvent(&Window::event);

    int Min = 799;
    int Max = 1;

    for(auto&t : tags)if(scroll && t->type[0] == 'O')
    {
        if(t->touch)
        {
            scroll = false;
        }
        if(Min > t->yPos) Min = t->yPos;
        if(Max < t->yPos + t->dest.h) Max = t->yPos + t->dest.h;
    }

    for(short i = 0, e = tags.size()-1; i<=e; i++)
    {
        if(scroll && tags[i]->type[0] == 'O' && Min + nowPos-lastPos < 700 && Max + nowPos-lastPos > 200)
        {
            tags[i]->upPos(nowPos-lastPos);
        }
        tags[i]->update();
    }
    lastPos = nowPos;


    if(Window::event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(Window::event.button.button == SDL_BUTTON_LEFT)
        {
            scroll = true;
            nowPos = lastPos = Window::event.button.y;
        }
    }
    if(scroll && Window::event.type == SDL_MOUSEMOTION)
    {
        nowPos = Window::event.motion.y;
    }
    if(Window::event.type == SDL_MOUSEBUTTONUP)
    {
        if(Window::event.button.button == SDL_BUTTON_LEFT)
        {
            scroll = false;
        }
    }
}

void Setting::update()
{


    for(auto&t : tags)
    {
        if(t->type == "money start")
        {
            t->SetText(std::to_string(moneyStart));
        }
        else if(t->type == "start with clear")
        {
            if(hasClearWorm)t->SetText("yes");
            else t->SetText("no");
        }
        if(t->isChosed)
        {
            if(t->type == "back home")///go back home
            {
                isRunning = false;
                Game::isRunning = false;
                if(save == false && isCusstom == true)SaveCusstom();
            }
            else if(t->type == "next money")
            {
                moneyStart = (moneyStart + 150)%1050;
            }
            else if(t->type == "prev money")
            {
                moneyStart = (moneyStart - 150 +1050*2)%1050;
            }
            else if(t->type == "change has clear" )
            {
                hasClearWorm = !hasClearWorm;
            }
            else if(t->type == "save cusstom")
            {
                SaveCusstom();
            }
            else if(t->type == "Open level 0")
            {
                Game::Level = "text/level0.txt";
                std::cout<<"Game start in level 0\n";
                isRunning = false;
                Game::isRunning = true;
            }
            else if(t->type == "Open level 1")
            {
                Game::Level = "text/level1.txt";
                std::cout<<"Game start in level 1\n";
                isRunning = false;
                Game::isRunning = true;
            }
            else if(t->type == "Open level 2")
            {
                Game::Level = "text/level2.txt";
                std::cout<<"Game start in level 2\n";
                isRunning = false;
                Game::isRunning = true;
            }
            else if(t->type == "Open Cusstom Level")
            {
                Game::Level = "text/cusstom.txt";
                std::cout<<"Game start with custom level\n";
                isRunning = false;
                Game::isCusstom = true;
                Game::isRunning = true;
            }
        }
    }


}

void Setting::render()
{
    SDL_RenderClear(Window::renderer);
    for(auto& t : tags)
    {
        t->render();
        t->isChosed = false;
    }
    SDL_RenderPresent(Window::renderer);
}

void Setting::SaveCusstom()
{
    std::ofstream renCusstom("text/cusstomSetting.txt");
    renCusstom <<moneyStart<<'\n';
    renCusstom <<hasClearWorm<<'\n';
    renCusstom.close();
    save == true;
}

void Setting::close()
{
    for(auto& t: tags)delete t;
    tags.clear();
}
