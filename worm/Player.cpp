#include "Player.h"

Player::Player()
{

}
Player::~Player()
{
    SDL_DestroyTexture(skin);
}
void Player::SetAni(const char* path,short _fr, short mpf, short num )
{

    frames = _fr;
    msPF = mpf;
    numA = num;
    SetTex(path);
    R = width;
    I = {Window::Width/2,Window::Height/2};
    ang = 0;
}

void Player:: update()
{
    int mouseX, mouseY;


    if( Window::event.type == SDL_MOUSEMOTION)
    {
        mouseX = Window::event.motion.x;
        mouseY = Window::event.motion.y;
        Button = {mouseX, mouseY , R , R};
    }
    else mouseX = Button.x, mouseY = Button.y;


    Vector2D B = {mouseX, mouseY};
//    B.x =mouseX + 50.0*cos(bAng);
//    B.y =mouseY + 50.0*sin(bAng);
    Move::MoveInit(I,R,B);
    ang = Move::GetAng();


    speed = B.Val(B-I)-0.2;
    speed = std::max(speed, 0.0);
    std::cout<<I.x<<' '<<I.y<<'\n';

    velocity = {std::cos(ang)*speed , std::sin(ang)*speed };

    double X = I.x-B.x, Y =I.y - B.y;
    if(X*X + Y*Y <= 10*10 )
    {
        bAng += 3.14/10;
        if(bAng > 2.0*3.14) bAng = 0;
        velocity = {0,0};
        Act = 0;
    }
    else Act = 0;
    I.x += velocity.x;
    I.y += velocity.y;
    dest.x = I.x - width/2;
    dest.y = I.y - height/2;
    timer_change = Game::timer;

    if((1000.0/Game::FPS)*(timer_change - last_change) >= msPF*60.0/Game::FPS)
    {
        last_change = timer_change;
        phase = (phase + 1)%frames;
        src.x = phase * width;
        src.y = Act * height;
    }
}

void Player:: SetTex(const char* path)
{
    skin = TextureManager::LoadTexture(path,width,height,frames,numA);
    dest = {0,0,width,height};
    src = {0,0,width,height};
    I = {0,0};
}

void Player:: Draw()
{
    timer_change = Game::timer;

    if((1000.0/Game::FPS)*(timer_change - last_change) >= msPF*60.0/Game::FPS)
    {
        last_change = timer_change;
        phase = (phase + 1)%frames;
        src.x = phase * width;
        src.y = Act * height;
    }

    SDL_RenderCopyExF(Window::renderer,skin,&src,&dest,-90+ang*180/3.14,NULL,SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(Window::renderer,255,0,0,255);
    SDL_RenderDrawPointF(Window::renderer,std::cos(ang)*R + I.x, std::sin(ang)*R + I.y);

    SDL_SetRenderDrawColor(Window::renderer,5,5,5,255);

}

bool Player:: Collision(SDL_FRect A)
{
    SDL_FRect B = dest;
    return !(A.x > B.x + B.w||
             A.y > B.y + B.h||
             B.x > A.x + A.w||
             B.y > A.y + A.h);
}

void Snake::init()
{
    length++;
    head = new Player;
    head->SetAni("image/snake.bmp",6,120,1);
    space = int(20.0 / head->speed);
}
void Snake::update()
{

   // for(int i = 0; i<5; i++)
    {
        if(Window::event.type == SDL_KEYDOWN && Window::event.key.keysym.sym == SDLK_w)length++;
        if(Window::event.type == SDL_KEYDOWN && Window::event.key.keysym.sym == SDLK_s)length--;
        if(Window::event.type == SDL_KEYDOWN && Window::event.key.keysym.sym == SDLK_d)head->speed++;
        if(Window::event.type == SDL_KEYDOWN && Window::event.key.keysym.sym == SDLK_a)head->speed--;
        if(Window::event.type == SDL_KEYDOWN && Window::event.key.keysym.sym == SDLK_e)space++;
        if(Window::event.type == SDL_KEYDOWN && Window::event.key.keysym.sym == SDLK_q)space--;

        head->update();
        body.push_front({head->src,head->dest,head->ang});

        while(body.size() > length*space)body.pop_back();
    }

}
void Snake::render()
{
    for(int i = length-1;i>=0 ; i--)
    {
        int tmp = i*space;
        if(tmp > body.size()-1)tmp = body.size()-1;
        SDL_RenderCopyExF(Window::renderer,head->skin,&body[tmp].src,&body[tmp].dest,90+body[tmp].ang*180/3.14,NULL,SDL_FLIP_NONE);
    }
}
void Snake::clean()
{
    body.clear();
}
