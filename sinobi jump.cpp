#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Menu.h"
#include "Game.h"

using namespace std;
using namespace sf;

// Function prototype for callmenu
void callmenu();





// Create the main window
RenderWindow app(VideoMode(1070, 900), "Shinobi jump");

//Create Menu object
Menu menu(app.getSize().x, app.getSize().y);

// Create Texture object 
Texture texture, txt, text, padtexture;

// Creating a music object
Music sound, jumpSound;
SoundBuffer menu_sound_buff;
Sound menu_sound;



int main()
{






    // Load in images to the texture
    texture.loadFromFile(imgs[8]);
    txt.loadFromFile("Background/0.gif");
    padtexture.loadFromFile("pad.png");



    // Declare a sprite object and pass the texture
    Sprite sprite(texture);
    Sprite  pad1(padtexture), pad2(padtexture), pad3(padtexture), pad4(padtexture),
        pad5(padtexture), pad6(padtexture), pad7(padtexture), pad8(padtexture);
    const int padnum = 8;
    Sprite pad[padnum] = { pad1, pad2,  pad3,  pad4, pad5, pad6, pad7, pad8 };
    Sprite background(txt);




    // Scale the size of sprites to display them properly inside the window
    sprite.scale(2, 2);
    background.scale(1.6, 2.3);

    //Randomly set position to each pads and scale the size of each pads
    generatePads(pad);

    // Score Object
    Font arial;
    //Create output string stream object for the score to display
    ostringstream sScore;
    //Create Text object for the score to display
    Text gamescore;
    //Prepare the score to be displayed on the canvas
    setScore(arial, sScore, gamescore);



    pad[0].setPosition(450, 500);
    sprite.setPosition(pad[0].getPosition().x, pad[0].getPosition().y);

    // Game over logo
    Text Texts;
    Texts.setFont(arial);
    Texts.setString("Game Over\nPress enter to\n continue");
    Texts.setFillColor(Color::Red);
    Texts.setCharacterSize(80);
    Texts.setPosition(380, 300);











    // Loading the sound files
    menu_sound.setBuffer(menu_sound_buff);

    sound.openFromFile("sound/naruto-trap.ogg");

    jumpSound.openFromFile("sound/katon.ogg");


    //return failure if the audio could not be loaded 
    if (!sound.openFromFile("sound/naruto-trap.ogg"))
        return EXIT_FAILURE;

    if (!jumpSound.openFromFile("sound/katon.ogg"))
        return EXIT_FAILURE;

    if (!menu_sound_buff.loadFromFile("sound/Strong and Strike.ogg"))
        return EXIT_FAILURE;


    callmenu();


    // setting parameters for the sound
    sound.setVolume(50);
    jumpSound.setVolume(120);



    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == event.Closed)
                app.close();

        }

        if (spriteframe == 35)
            spriteframe = 1;

        spriteframe++;

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            sound.pause();
            callmenu();
        }

        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            jump = true;

        }


        jumpUp(sprite, pad, texture);


        if (Keyboard::isKeyPressed(Keyboard::A) && sprite.getPosition().x >= 0)
        {
            if (jump)
                texture.loadFromFile("Jump/" + imgs[index]);




            sprite.move(-8, 0);
        }

        if (Keyboard::isKeyPressed(Keyboard::D) && sprite.getPosition().x <= 1070 - 100)
        {
            if (jump)
                texture.loadFromFile("Jump/" + imgs[index]);


            sprite.move(8, 0);
        }

        // Game over logic
        if (sprite.getPosition().y > 750)
        {
            if (event.type == event.Closed)
            {
                app.close();
            }
            while (!(Keyboard::isKeyPressed(Keyboard::Enter)))
            {


                app.clear();
                Texture gback;
                gback.loadFromFile("menu.jpg");
                Sprite ggback(gback);
                ggback.scale(0.3, 0.4);
                app.draw(ggback);
                app.draw(Texts);
                app.draw(gamescore);
                app.display();
            }
            sprite.setPosition(450, 500);
            pad[0].setPosition(450, 500);
            score = 0;
        }




        // Check if the sprites are in contact
        checkContact(sprite, pad);

        // Increase the score with each frame
        displayScore(sScore, gamescore);


        //limit the character from moving beyond the screen upwards
        if (sprite.getPosition().y <= 0)
        {
            jump_vel = 0;
        }

        //Loop the background to create animation effect
        loopBackground(txt);

        app.setFramerateLimit(100);


        // Clear screen
        app.clear();










        // Draw the sprite
        app.draw(background);

        drawPad(app, pad);

        app.draw(sprite);

        app.draw(gamescore);





        // Update the window
        app.display();




    }



    return EXIT_SUCCESS;
}





void callmenu()
{
    menuOn = true;
    menu_sound.play();

    while (menuOn)
    {

        // Process events
        Event event;
        while (app.pollEvent(event))
        {

            if (Keyboard::isKeyPressed(Keyboard::Up))
                menu.moveUp();

            if (Keyboard::isKeyPressed(Keyboard::Down))
                menu.moveDown();

            if (Keyboard::isKeyPressed(Keyboard::Enter))
                menu.enter(app);

            // Close window : exit
            if (event.type == event.Closed)
            {
                menuOn = false;
                app.close();
            }

        }

        menu.create(app);

    }
    menu_sound.stop();
    sound.play();
    sound.setLoop(true);


}