#include<SFML/Graphics.hpp>

#include<SFML/Audio.hpp>

#define MAX_ITEMS 3

using namespace sf;

extern bool menuOn, gameOn;

class Menu
{
public:

    Menu(float height, float width);

    void create(RenderWindow& app);

    void moveUp();


    void moveDown();

    void enter(RenderWindow& app);

private:
    int activeItemIndex;
    Font font;
    Text text[MAX_ITEMS];
    Texture menu_background;

};


