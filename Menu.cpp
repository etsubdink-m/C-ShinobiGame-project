#include "Menu.h"

using namespace sf;

bool menuOn = true;

Menu::Menu(float width, float height)
{
    font.loadFromFile("TextFile/Japanese Robot.ttf");

    for(int pos = 0; pos<MAX_ITEMS; pos++)
    {
        text[pos].setFont(font);
        text[pos].setPosition((width/2)-50,(height/3)+(pos*100));
    }

    text[0].setFillColor(Color::Red);
    text[0].setString("PLAY");

    text[1].setFillColor(Color::White);
    text[1].setString("HELP");

    text[2].setFillColor(Color::White);
    text[2].setString("EXIT");

    activeItemIndex = 0;


}

void Menu::create(RenderWindow& app)
{
    menu_background.loadFromFile("menu.jpg");

    Sprite menu_bg(menu_background);

    menu_bg.scale(0.3,0.4);

    app.draw(menu_bg);

    for(int pos = 0; pos<MAX_ITEMS; pos++)
    {
        app.draw(text[pos]);
    }

    app.display();
}

void Menu::moveUp()
{
    if(activeItemIndex >=0)
    {
        text[activeItemIndex].setFillColor(Color::White);
        activeItemIndex--;
        if(activeItemIndex<0)
            activeItemIndex = 0;
        text[activeItemIndex].setFillColor(Color::Red);
    }

}

void Menu::moveDown()
{
    if(activeItemIndex >=0)
    {
        text[activeItemIndex].setFillColor(Color::White);
        activeItemIndex++;
        if(activeItemIndex>2)
            activeItemIndex = 0;
        text[activeItemIndex].setFillColor(Color::Red);
    }
}

void Menu::enter(RenderWindow& app)
{
    switch(activeItemIndex)
    {
    case 0:
        menuOn = false;
        break;
    case 1:
        break;
    case 2:
        menuOn = false;
        app.close();

    }

}
