#include "Block.h"
#include "Menu.h"


Block::Block()
{
    skin = nullptr;
    text = nullptr;
}

Block:: ~Block()
{
    SDL_DestroyTexture(skin);
    SDL_DestroyTexture(text);
}

void Block:: init(const char* path)
{
    SetSkin(path);
}

void Block::init(const char* path, std::string T,int sz)
{
    SetSkin(path);
    SetText(T,sz);
}

void Block:: update()
{
    if(type == "BG")return;
    switch(Window::event.type)
    {

    case SDL_MOUSEMOTION:
        {
            SDL_Rect pos = {Window::event.motion.x,Window::event.motion.y,1,1};

            if(!touch && Collision(dest,pos))
            {
                touch = true;
                SetSkin("image/BoardChosed.bmp");
            }
            if(touch && !Collision(dest,pos))
            {
                touch = false;
                SetSkin("image/Board.bmp");
            }
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(touch)
        {
            isChosed = true;
        }
        break;
    default:
        break;
    }
}

void Block:: render()
{
    TextureManager::DrawTexture(skin,src,dest);

    if(Text!="")
    {
        TextureManager::DrawTexture(text,tsrc,tdest);
    }
}
///------------------------------------------------------------------------------------

void Block:: SetSkin(const char* path)
{
    skin = TextureManager::LoadTexture(path,src);
    dest.w = src.w*scale;
    dest.h = src.h*scale;
    if(text && dest.w <tdest.w + 20)dest.w = tdest.w + 20;
}

void Block:: SetText(std::string path,int sz)
{
    Text = path;
    TextureManager::SetSize(sz);
    text = TextureManager::LoadTextTexture(Text.c_str(),tsrc);

    tdest = tsrc;
    tdest.x = dest.x + dest.w/2 - tsrc.w/2;
    tdest.y = dest.y + dest.h/2 - tsrc.h/2;
    if(dest.w <tdest.w + 20)dest.w = tdest.w + 20;
    if(dest.h <tdest.h + 20)dest.h = tdest.h + 20;

}

void Block:: SetPos(int x, int y)
{
    dest.x = x - dest.w/2;
    dest.y = y - dest.h/2;
    if(type == "BG")dest.x = 0, dest.y =0;
    if(Text!="")
    {
        tdest.x = dest.x + dest.w/2 - tsrc.w/2;
        tdest.y = dest.y + dest.h/2 - tsrc.h/2;
    }
}

void Block:: SetScale(int sc)
{
    scale = sc;
}
///-------------------------------------------------------------------------------------

SDL_Rect Block:: Get()
{
    return dest;
}
