#include <SFML/Graphics.hpp>
#include <optional>
    
int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1400, 900)), "Carta");

    // Carta (rectángulo)
    sf::RectangleShape carta(sf::Vector2f(100.f, 150.f));
    carta.setFillColor(sf::Color::White);
    carta.setOutlineColor(sf::Color::Black);
    carta.setOutlineThickness(4.f);
    carta.setPosition(sf::Vector2f(750.f, 600.f));

    //borde de la mesa
    sf::RectangleShape borde(sf::Vector2f(1400.f, 900.f));
    borde.setFillColor(sf::Color(128, 64, 0)); // Color del borde

    //mesa
    sf::RectangleShape mesa(sf::Vector2f(1300.f, 800.f));
    mesa.setFillColor(sf::Color(0, 80, 0)); // Color del borde
    mesa.setPosition(sf::Vector2f(50.f, 50.f));
    

    // Diamante (hecho con un círculo deformado)
    sf::CircleShape diamante(20.f, 4); // 4 puntos = rombo
    diamante.setFillColor(sf::Color::Red);

    diamante.setPosition(sf::Vector2f(780.f, 655.f));

	// Letra A en la carta
    sf::Font font;
    // Intenta cargar una fuente del sistema. Ajusta la ruta si es necesario.
    if (!font.openFromFile("C:\\Windows\\Fonts\\times.ttf")) {
        // Si no se pudo cargar, el texto podría no mostrarse; seguir para evitar fallo en compilación
    }
    sf::Text A(font, "A", 25);
    A.setFillColor(sf::Color::Red); // Color
    A.setPosition(sf::Vector2f(755.f, 600.f));

    
    sf::Text A2(font, "A", 25);
    A2.setFillColor(sf::Color::Red); // Color
    A2.setPosition(sf::Vector2f(843.f, 750.f));
	// Voltear la A para que quede al revés (sf::rotate expects sf::Angle in SFML 3)
	A2.rotate(sf::degrees(180.f));
    
	

    // Otro diamante arriba
    sf::CircleShape diamante2 = diamante;
    diamante2.setScale(sf::Vector2f(0.5f, 0.5f));
    diamante2.setPosition(sf::Vector2f(755.f, 630.f));

    // Otro diamante abajo
    sf::CircleShape diamante3 = diamante2;
    diamante3.setPosition(sf::Vector2f(825.f, 700.f));

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.draw(borde);
        window.draw(mesa);
        window.draw(carta);
        window.draw(diamante);
        window.draw(diamante2);
        window.draw(diamante3);
        window.draw(A);
        window.draw(A2);
        window.display();
    }

    return 0;
}
