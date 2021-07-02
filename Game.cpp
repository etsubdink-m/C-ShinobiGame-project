#include"Game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<iomanip>

using namespace sf;
using namespace std;

string imgs[30] = {"0.png","1.png","2.png","3.png","4.png",
                    "5.png","6.png","7.png","8.png","8_I.png"};

bool jump = false;

float jump_vel = -25;

int spriteframe = 1;

int index = 0;

const int padnum = 8;

int bgFramebalancer = 1;

int bgIndex = 1;

float score = 0;

void generatePads(Sprite pad[])
{
    for (int i = 0; i < padnum; i++)
    {
        pad[i].scale(1.5, 1.5);
    }

    // using random seed for time function
    srand(time(NULL));

    for (int i = 0; i < padnum; i++)
    {
        pad[i].setPosition(rand() % 970, (rand() % 790) + 200);
    }
    for (int i = 0; i < padnum; i++)
    {
        for (int j = 1; j < padnum; j++)
        {
            if (pad[i].getGlobalBounds().intersects(pad[j].getGlobalBounds()))
                pad[j].setPosition(rand() % 970, (rand() % 790) + 200);
        }
    }

}


void jumpUp(Sprite &sprite, Sprite pad[], Texture &texture)
{
    if(jump)
    {
        jump_vel += 1;

        sprite.move(0, jump_vel);

        if (spriteframe % 6 == 0)
        {
            texture.loadFromFile("Jump/" + imgs[index]);
            index++;

            if (index == 6)
                index = 0;
        }

        for (int i = 0; i < padnum; i++)
        {
            pad[i].move(0, 3);

            if (pad[i].getPosition().y >= 1000)
            {
                pad[i].setPosition(rand() % 970, -1);
            }
        }


        if (sprite.getPosition().y > 750)
        {
            texture.loadFromFile(imgs[8]);
            jump_vel = -25;
            jump = false;
        }

    }

}

void checkContact(Sprite &sprite,Sprite pad[])
{
    for (int i = 0; i < padnum; i++)
    {
        IntRect r1(sprite.getPosition().x, sprite.getPosition().y, 35, 92);
        IntRect r2(pad[i].getPosition().x, pad[i].getPosition().y, 102, 14);
        IntRect result;
        bool contact;
        contact = r1.intersects(r2, result);

        if (contact)
        {
            jump = true;
            if (sprite.getPosition().y > 300)
                jump_vel = -25;
        }

    }

}

void drawPad(RenderWindow &app,Sprite pad[])
{
    for (int i = 0; i < padnum; i++)
    {
        app.draw(pad[i]);
    }
}

void loopBackground(Texture &txt)
{
    if (bgFramebalancer%8==0)
    {
        txt.loadFromFile("Background/" + to_string(bgIndex) + ".gif");
        bgIndex++;
        if (bgIndex > 29)
            bgIndex = 0;
    }
    bgFramebalancer++;

}
void setScore(Font &arial , ostringstream & sScore , Text & gamescore)
{
    arial.loadFromFile("TextFile/arial.ttf");
    sScore << "Score: " << score;
    gamescore.setCharacterSize(30);
    gamescore.setPosition({ 920, 10 });
    gamescore.setFont(arial);
    gamescore.setFillColor(Color::Black);
    gamescore.setString(sScore.str());
}

void displayScore(ostringstream & sScore , Text & gamescore)
{
    score += 0.01;
    sScore.str("");
    sScore << setprecision(0) << fixed << "Time: " << score;
    gamescore.setString(sScore.str());
}
