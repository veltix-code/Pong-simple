#include <SFML/Graphics.hpp>
#include "input.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace sf;

Clock Gameclock;

enum GameState
{
    GAME,
    PAUSE,
    DIFFICULTE
};

void ajusterVitesseGlobale(float& vitesseGlobale)
{
    float dt = 0.f;
    float timer = 0.f;
    for(int i = 0; i < 1000000; i++); // charge le CPU pour que le timer soit plus précis
    {
        dt = Gameclock.restart().asSeconds();
        timer += dt;
    }
    vitesseGlobale = timer / 1.97582f;
}

void move(Shape& player, float NewX, float NewY)
{
    player.setPosition(Vector2f(player.getPosition().x + NewX, player.getPosition().y + NewY));
}

bool verifierCollisionPlayer(RectangleShape& player, CircleShape& ball)
{
    if(ball.getPosition().x <= 60.f && ball.getPosition().y >= player.getPosition().y && ball.getPosition().y <= player.getPosition().y + player.getSize().y)
    {
        ball.setPosition(Vector2f(player.getPosition().x + player.getSize().x + 1.f,ball.getPosition().y));
        return true;
    }
    return false;
}

bool verifierCollisionEnemi(RectangleShape& enemi, CircleShape& ball)
{
    if(ball.getPosition().x >= 730.f && ball.getPosition().y >= enemi.getPosition().y && ball.getPosition().y <= enemi.getPosition().y + enemi.getSize().y)
    {
        return true;
    }
    return false;
}

float calculerArriveeBalle(CircleShape& ball, int ballDirection)
{
    CircleShape simulationBall(10.f);
    simulationBall.setPosition(ball.getPosition());

    // getPosition().x au lieu de setPosition()
    int safety = 0;
    while(simulationBall.getPosition().x < 740.f && safety < 10000)
    {
        safety++;
        float ballX = simulationBall.getPosition().x + simulationBall.getRadius();
        float ballY = simulationBall.getPosition().y + simulationBall.getRadius();

        if(ballX >= 800.f)
            ballDirection = 180 - ballDirection;
        else if(ballX - simulationBall.getRadius() <= 0.f)
            ballDirection = 180 - ballDirection;

        if(ballY >= 600.f)
            ballDirection = 360 - ballDirection;
        else if(ballY - simulationBall.getRadius() <= 0.f)
            ballDirection = 360 - ballDirection;

        float rad = ballDirection * 3.14159f / 180.f;
        move(simulationBall, std::cos(rad)*1.25, std::sin(rad)*1.5);
    }

    return simulationBall.getPosition().y;
}

void MenuDificulte(RenderWindow& window, Font& font)
{
    Text text_titre(font);
    text_titre.setString("Dificulte");
    text_titre.setCharacterSize(96);
    text_titre.setFillColor(Color::White);
    text_titre.setPosition(Vector2f(215.f, 25.f));
    Text text_niveau(font);
    text_niveau.setString("Eshap  :  easy : vitesse -> Joueur 1.25, Enemi 0.75, Balle 0.5");
    text_niveau.setCharacterSize(48);
    text_niveau.setFillColor(Color(75, 75, 75));
    text_niveau.setPosition(Vector2f(85.f, 225.f));
    Text text_jouer(font);
    text_jouer.setString("Espace  :  medium : vitesse -> Joueur 1, Enemi 1, Balle 1");
    text_jouer.setCharacterSize(48);
    text_jouer.setFillColor(Color(75, 75, 75));
    text_jouer.setPosition(Vector2f(85.f, 350.f));
    Text text_quitter(font);
    text_quitter.setString("D  :  hard : vitesse -> Joueur 0.75, Enemi 1.5, Balle 1.5");
    text_quitter.setCharacterSize(48);
    text_quitter.setFillColor(Color(75, 75, 75));
    text_quitter.setPosition(Vector2f(85.f, 475.f));
    RectangleShape niveau(Vector2f(700.f, 100.f));
    RectangleShape jouer(Vector2f(700.f, 100.f));
    RectangleShape quitter(Vector2f(700.f, 100.f));
    RectangleShape pause(Vector2f(800.f, 600.f));
    niveau.setFillColor(Color(128, 128, 128));
    jouer.setFillColor(Color(128, 128, 128));
    quitter.setFillColor(Color(128, 128, 128));
    pause.setFillColor(Color(0, 0, 0, 150));
    niveau.setPosition(Vector2f(50.f, 200.f));
    jouer.setPosition(Vector2f(50.f, 325.f));
    quitter.setPosition(Vector2f(50.f, 450.f));
    pause.setPosition(Vector2f(0.f, 0.f));
    window.draw(pause);
    window.draw(niveau);
    window.draw(jouer);
    window.draw(quitter);
    window.draw(text_titre);
    window.draw(text_niveau);
    window.draw(text_jouer);
    window.draw(text_quitter);
    return;
}

void afficherPause(RenderWindow& window, Font& font)
{
    Text text_titre(font);
    text_titre.setString("PAUSE");
    text_titre.setCharacterSize(96);
    text_titre.setFillColor(Color::White);
    text_titre.setPosition(Vector2f(225.f, 25.f));
    Text text_niveau(font);
    text_niveau.setString("Dificulte : D");
    text_niveau.setCharacterSize(48);
    text_niveau.setFillColor(Color(75, 75, 75));
    text_niveau.setPosition(Vector2f(265.f, 225.f));
    Text text_jouer(font);
    text_jouer.setString("Jouer : Espace");
    text_jouer.setCharacterSize(48);
    text_jouer.setFillColor(Color(75, 75, 75));
    text_jouer.setPosition(Vector2f(235.f, 350.f));
    Text text_quitter(font);
    text_quitter.setString("Quitter : Echap");
    text_quitter.setCharacterSize(48);
    text_quitter.setFillColor(Color(75, 75, 75));
    text_quitter.setPosition(Vector2f(235.f, 475.f));
    RectangleShape niveau(Vector2f(400.f, 100.f));
    RectangleShape jouer(Vector2f(400.f, 100.f));
    RectangleShape quitter(Vector2f(400.f, 100.f));
    RectangleShape pause(Vector2f(800.f, 600.f));
    niveau.setFillColor(Color(128, 128, 128));
    jouer.setFillColor(Color(128, 128, 128));
    quitter.setFillColor(Color(128, 128, 128));
    pause.setFillColor(Color(0, 0, 0, 150));
    niveau.setPosition(Vector2f(200.f, 200.f));
    jouer.setPosition(Vector2f(200.f, 325.f));
    quitter.setPosition(Vector2f(200.f, 450.f));
    pause.setPosition(Vector2f(0.f, 0.f));
    window.draw(pause);
    window.draw(niveau);
    window.draw(jouer);
    window.draw(quitter);
    window.draw(text_titre);
    window.draw(text_niveau);
    window.draw(text_jouer);
    window.draw(text_quitter);
    return;
}

bool jouer(sf::RenderWindow& window, sf::Font& font)
{
    float vitesseGlobale = 1.f;//vitesseglobal 1 -> 1.97582
    ajusterVitesseGlobale(vitesseGlobale);
    GameState state = GAME;
    srand(time(NULL));
    int angleMax = 15;
    bool inGame = true;
    float timer = 0.f;
    float Save_Ball = 0.f;

    RectangleShape player(Vector2f(10.f, 100.f));
    player.setFillColor(Color::Blue);
    player.setPosition(Vector2f(50.f, 250.f));
    float vitessePlayer = 1.f;

    RectangleShape enemi(Vector2f(10.f, 100.f));
    enemi.setFillColor(Color::Red);
    enemi.setPosition(Vector2f(740.f, 250.f));
    float vitesseEnemi = 1.f;

    int ballDirection = 45;//0=right, 90=down, 180=left, 270=up
    float DX = 0.f, DY = 0.f;
    float vitesseBalle = 0.5f;
    CircleShape ball(10.f);
    ball.setFillColor(Color::Red);
    ball.setPosition(Vector2f(400.f, 300.f));

    while(inGame)
    {
        float dt = Gameclock.restart().asSeconds();
        timer += dt;
        InitInput(window, 0.f);
        if(state == DIFFICULTE)
        {
            if(getInput("Space"))
            {
                vitessePlayer = 1.f;
                vitesseEnemi = 1.f;
                vitesseBalle = 1.0f;
                state = PAUSE;
            }
            if(getInput("D"))
            {
                vitessePlayer = 0.75f;
                vitesseEnemi = 1.5f;
                vitesseBalle = 1.5f;
                state = PAUSE;
            }
            if(getInput("Escape"))
            {
                vitessePlayer = 1.25f;
                vitesseEnemi = 0.75f;
                vitesseBalle = 0.5f;
                state = PAUSE;
            }
        }
        else if(state == PAUSE)
        {
            if(getInput("Space"))
            {
                state = GAME;
            }
            if(getInput("D"))
            {
                state = DIFFICULTE;
            }
            if(getInput("Escape"))
            {
                inGame = false;
            }
        }
        if(getInput("Escape")&& state == GAME)
        {
            state = PAUSE;
        }
        if(state == GAME)
        {
            float ballX = ball.getPosition().x + ball.getRadius();
            float ballY = ball.getPosition().y + ball.getRadius();
            if(ballX >= window.getSize().x)
            {
                ballDirection = 180-ballDirection;
                state = PAUSE;
                ball.setPosition(Vector2f(400.f, 300.f));
            }
            else if(ballX - ball.getRadius() <= 0.f)
            {
                ballDirection = 180-ballDirection;
                state = PAUSE;
                ball.setPosition(Vector2f(400.f, 300.f));
            }
            if(ballY >= window.getSize().y)
            {
                ballDirection = 360-ballDirection;
            }
            else if(ballY - ball.getRadius() <= 0.f)
            {
                ballDirection = 360-ballDirection;
            }
            if(verifierCollisionPlayer(player, ball))
            {
                int angle = (rand() % (angleMax*2+1)) - angleMax;
                ballDirection = 180-ballDirection+angle;
            }
            if(verifierCollisionEnemi(enemi, ball))
            {
                int angle = (rand() % (angleMax*2+1)) - angleMax;
                ballDirection = 180-ballDirection+angle;
            }
            DX = cos(ballDirection/180.f*3.14159f);
            DY = sin(ballDirection/180.f*3.14159f);
            move(ball, DX*vitesseBalle*vitesseGlobale, DY*vitesseBalle*vitesseGlobale);
            if(getInput("Up") && player.getPosition().y > 0.f)
            {
                move(player, 0.f,-0.5f*vitessePlayer*vitesseGlobale);
            }
            if(getInput("Down") && player.getPosition().y + player.getSize().y < window.getSize().y)
            {
                move(player, 0.f,0.5f*vitessePlayer*vitesseGlobale);
            }
            float arrivee = calculerArriveeBalle(ball, ballDirection);
            if(enemi.getPosition().y + enemi.getSize().y/2 < arrivee && enemi.getPosition().y + enemi.getSize().y < window.getSize().y)
            {
                move(enemi, 0.f, 0.5f*vitesseEnemi*vitesseGlobale);
            }
            else if(enemi.getPosition().y + enemi.getSize().y/2 > arrivee && enemi.getPosition().y > 0.f)
            {
                move(enemi, 0.f, -0.5f*vitesseEnemi*vitesseGlobale);
            }
            if(timer >= 1.f)
            {
                if((int)Save_Ball == (int)ball.getPosition().x)
                {
                    ball.setPosition(Vector2f(400.f, 300.f));
                }
                timer = 0.f;
                Save_Ball = ball.getPosition().x;
            }
        }
        window.clear();
        window.draw(ball);
        window.draw(player);
        window.draw(enemi);
        if(state == DIFFICULTE){MenuDificulte(window, font);}else if(state == PAUSE){afficherPause(window, font);}
        window.display();
    }
    return true;
}