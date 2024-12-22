#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

const int largura = 800;
const int altura = 600;

class Bola {
    sf::CircleShape bola;
    sf::Vector2f v;
public:
    Bola(int r) : bola(r), v(0.4, 0.4) {
        bola.setFillColor(sf::Color::White);
        bola.setPosition(largura/2, altura/2);
    }

    void move() {
        bola.move(v);
        double y = bola.getPosition().y;
        if(y <= 0 || y >= altura) v.y = -v.y;
    }

    void invertX() { v.x = -v.x; }

    sf::CircleShape shape() const { return bola; }
    void reset() {
        bola.setPosition(largura/2, altura/2);
        v.x = -v.x;
    }

    double getX() const { return bola.getPosition().x; }
    double getY() const { return bola.getPosition().y; }
};

class Raquete {
    sf::RectangleShape rect;
    double v;
    const int w, h;
public:
    Raquete(bool direita) : w(20), h(100), v(1.0) {
        rect = sf::RectangleShape(sf::Vector2f(w, h));
        if(direita)
            rect.setPosition(10, altura/2 - h/2);
        else
            rect.setPosition(largura - 10 - w, altura/2 - h/2);
    }

    sf::Vector2f dims() const {
        return sf::Vector2f(w, h);
    }

    void move(double dy) {
        double y = rect.getPosition().y;
        if(y + dy >= 0 && y + dy + h <= altura)
            rect.move(0, dy);
    }

    void moveUp() { move(-v); }
    void moveDown() { move(v); }

    bool colide(const Bola& b) const {
        return b.shape().getGlobalBounds().intersects(rect.getGlobalBounds());
    }

    sf::RectangleShape shape() const { return rect; }
};

class Jogo {
    sf::RenderWindow janela;
    Raquete esq, dir;
    Bola bola;
public:
    Jogo() : janela(sf::VideoMode(largura, altura), "PONG GAME"),
             esq(false), dir(true), bola(10) { run(); }

    void run();
};

void Jogo::run() {
    sf::Event evento;
    while(janela.isOpen()) {
        while(janela.pollEvent(evento)) {
            if(evento.type == sf::Event::Closed)
                janela.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            esq.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            esq.moveDown();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dir.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dir.moveDown();
        bola.move();
        if(esq.colide(bola) || dir.colide(bola))
            bola.invertX();

        if(bola.getX() <= 0 || bola.getX() >= largura)
            bola.reset();

        janela.clear(sf::Color::Black);
        janela.draw(bola.shape());
        janela.draw(esq.shape());
        janela.draw(dir.shape());
        janela.display();
    }
}

int main() {
    Jogo j;
    return 0;
}