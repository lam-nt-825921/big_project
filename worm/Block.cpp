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

void Block:: init(bool Cch,const char* path)
{
    CanChose = Cch;
    if(path != NULL)
    {
        UnchosedSkin = const_cast<char*>(path);
        ChosedSkin = "";
        for(int i = 0, n = strlen(path)-4; i<n; i++)ChosedSkin+=path[i];
        ChosedSkin += "Chosed.bmp";
    }


    SetSkin(path);
}

void Block::init(bool Cch, const char* path, std::string T,short sz)
{

    CanChose = Cch;
    if(path != NULL)
    {
        UnchosedSkin = const_cast<char*>(path);
        ChosedSkin = "";
        for(int i = 0, n = strlen(path)-4; i<n; i++)ChosedSkin+=path[i];
        ChosedSkin += "Chosed.bmp";
    }

    SetSkin(path);
    SetText(T,sz);

}

void Block:: update()
{

    if(CanChose == false)return;
    switch(Window::event.type)
    {

    case SDL_MOUSEMOTION:
        {

            SDL_Rect pos = {Window::event.motion.x,Window::event.motion.y,1,1};
            if(!touch && Collision(dest,pos))
            {
                touch = true;
                SetSkin(ChosedSkin.c_str());
            }
            if(touch && !Collision(dest,pos))
            {
                touch = false;
                SetSkin(UnchosedSkin.c_str());
            }

        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        {
            SDL_Rect pos = {Window::event.button.x,Window::event.button.y,1,1};
            if(!touch && Collision(dest,pos))
            {
                touch = true;
                SetSkin(ChosedSkin.c_str());
            }
            if(touch && !Collision(dest,pos))
            {
                touch = false;
                SetSkin(UnchosedSkin.c_str());
            }
            if(touch)
            {
                isChosed = true;
            }

        }
        break;
    default:
        break;
    }
}

void Block:: render()
{
    if(skin!=nullptr)TextureManager::DrawTexture(skin,src,dest);

    if(text!=nullptr)TextureManager::DrawTexture(text,tsrc,tdest);
}
///------------------------------------------------------------------------------------

void Block:: SetSkin(const char* path)
{
    SDL_DestroyTexture(skin);
    skin = TextureManager::LoadTexture(path,src);
    if(skin == nullptr)return;
    dest.x = xPos - dest.w/2;
    dest.y = yPos - dest.h/2;
    dest.w = src.w*scale;
    dest.h = src.h*scale;
    if(text == nullptr)return;
    if(dest.w <tdest.w + 20)dest.w = tdest.w + 20;
}

void Block:: SetText(std::string path,short sz)
{
    Text = path;
    TextureManager::SetSize(sz);
    SDL_DestroyTexture(text);
    text = TextureManager::LoadTextTexture(Text.c_str(),tsrc);

    if(text == nullptr)return;
    tdest = tsrc;
    tdest.x = xPos - tsrc.w/2;
    tdest.y = yPos - tsrc.h/2;

    if(skin == nullptr)return;
    if(dest.w <tdest.w + 20)dest.w = tdest.w + 20;
    if(dest.h <tdest.h + 20)dest.h = tdest.h + 20;

}

void Block:: SetPos(short x, short y)
{

    xPos = x;
    yPos = y;
    if(skin != nullptr)
    {
        dest.x = x - dest.w/2;
        dest.y = y - dest.h/2;
    }
    if(text != nullptr)
    {
        tdest.x = xPos - tsrc.w/2;
        tdest.y = yPos - tsrc.h/2;
    }
}

void Block:: SetScale(short sc)
{
    scale = sc;
}
///-------------------------------------------------------------------------------------

SDL_Rect Block:: Get()
{
    return dest;
}
