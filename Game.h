#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;

extern bool jump;
extern float jump_vel;
extern int spriteframe;
extern int index;
extern bool jump;
extern const int padnum;
extern string imgs[30];
extern int bgFramebalancer;
extern int bgIndex;
extern float score;




void generatePads(Sprite[]);
void jumpUp(Sprite &, Sprite[], Texture &);
void checkContact(Sprite &, Sprite[]);
void drawPad(RenderWindow &app, Sprite pad[]);
void loopBackground(Texture &);
void setScore(Font & , ostringstream & , Text &);
void displayScore(ostringstream & , Text & );

#endif // GAME_H_INCLUDED
