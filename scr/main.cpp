#include <SFML/Graphics.hpp>
#include "input.hpp"
#include "pong.hpp"
using namespace sf;

void drawMenu(RenderWindow& window, Font& font);

int main()
{
    int scene = 0;//0=menu, 1=game, 2=score
    bool textFileExists = false,inGame = false;
    Clock clock;
    RenderWindow window(sf::VideoMode({800u, 600u}), "Pong");
    Font font;
    if (font.openFromFile("arial.ttf")){textFileExists = true;}
    Text text(font);
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        InitInput(window, dt);
        
        if(scene == 1)
        {
            if(getInput("Escape"))
            {
                inGame = false;
                scene = 0;
            }
        }
        if(scene == 0)
        {
            if(getInput("Escape"))
            {
                window.close();
            }
            if(getInput("Space"))
            {
                scene = 1;
            }
        }
        
        window.clear();
        if(scene == 0)
        {
            drawMenu(window, font);
        }
        else if(scene == 1 && inGame == false)
        {
            if(jouer(window, font))
            {
                inGame = false;
            }
            inGame = true;
        }
        /*
        if(textFileExists)
        {
            text.setString("Scene: " + std::to_string(scene));
            text.setCharacterSize(24);
            text.setFillColor(Color::White);
            text.setPosition(Vector2f(10.f, 10.f));
            window.draw(text);
        }
        */
        window.display();
    }
    return 0;
}

void drawMenu(RenderWindow& window, Font& font)
{
    Text text_titre(font);
    text_titre.setString("PING - PONG");
    text_titre.setCharacterSize(96);
    text_titre.setFillColor(Color::White);
    text_titre.setPosition(Vector2f(100.f, 75.f));
    Text text_jouer(font);
    text_jouer.setString("Jouer : Espace");
    text_jouer.setCharacterSize(48);
    text_jouer.setFillColor(Color(75, 75, 75));
    text_jouer.setPosition(Vector2f(235.f, 325.f));
    Text text_quitter(font);
    text_quitter.setString("Quitter : Echap");
    text_quitter.setCharacterSize(48);
    text_quitter.setFillColor(Color(75, 75, 75));
    text_quitter.setPosition(Vector2f(235.f, 475.f));
    RectangleShape jouer(Vector2f(400.f, 100.f));
    RectangleShape quitter(Vector2f(400.f, 100.f));
    jouer.setFillColor(Color(128, 128, 128));
    quitter.setFillColor(Color(128, 128, 128));
    jouer.setPosition(Vector2f(200.f, 300.f));
    quitter.setPosition(Vector2f(200.f, 450.f));
    window.draw(jouer);
    window.draw(quitter);
    window.draw(text_titre);
    window.draw(text_jouer);
    window.draw(text_quitter);
    return;
}