#include <SFML/Graphics.hpp>
#include <string>

bool Haut = false, Bas = false, Gauche = false, Droite = false, Space = false, Escape = false, modMenu = false,lancerTimer = false,D = false;
float timer = 0.f;

void InitInput(sf::RenderWindow& window,float deltaTime)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (auto* e = event->getIf<sf::Event::KeyPressed>())
        {
            if (e->code == sf::Keyboard::Key::Escape) Escape = true;
            if (e->code == sf::Keyboard::Key::Space)  Space  = true;
            if (e->code == sf::Keyboard::Key::D) D = true;
        }
    }
    timer += deltaTime;
    Haut = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    Bas = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    Gauche = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    Droite = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
}


bool getInput(std::string input)
{
    if (input == "Escape") { bool v = Escape; Escape = false; return v; }
    if (input == "Space")  { bool v = Space;  Space  = false; return v; }
    if (input == "D")      { bool v = D; D = false; return v; }
    if (input == "Up")     return Haut;
    if (input == "Down")   return Bas;
    if (input == "Left")   return Gauche;
    if (input == "Right")  return Droite;
    return false;
}

void modifierModMenu(bool modif)
{
    modMenu = modif;
}
