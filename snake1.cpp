#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <deque>

class SnakeGame {
public:
    SnakeGame() : window(sf::VideoMode(600, 600), "Snake Game") {
    
        snake.push_back(sf::Vector2i(10, 10));  

        
        direction = sf::Vector2i(1, 0); 

 
        food.setSize(sf::Vector2f(10, 10));
        food.setFillColor(sf::Color::Red);
        food.setPosition(rand() % 60 * 10, rand() % 60 * 10); 

  
        clock.restart();
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    std::deque<sf::Vector2i> snake; 
    sf::Vector2i direction;        
    sf::RectangleShape food;         
    sf::Clock clock;                
    float speed = 0.1f;            

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && direction != sf::Vector2i(0, 1))
                    direction = sf::Vector2i(0, -1);
                if (event.key.code == sf::Keyboard::Down && direction != sf::Vector2i(0, -1))
                    direction = sf::Vector2i(0, 1);
                if (event.key.code == sf::Keyboard::Left && direction != sf::Vector2i(1, 0))
                    direction = sf::Vector2i(-1, 0);
                if (event.key.code == sf::Keyboard::Right && direction != sf::Vector2i(-1, 0))
                    direction = sf::Vector2i(1, 0);
            }
        }
    }

    void update() {
        if (clock.getElapsedTime().asSeconds() > speed) {
          
            sf::Vector2i newHead = snake.front() + direction;
            snake.push_front(newHead);
            if (newHead.x == food.getPosition().x / 10 && newHead.y == food.getPosition().y / 10) {
            
                food.setPosition(rand() % 60 * 10, rand() % 60 * 10);
            } else {
                snake.pop_back();
            }


            if (newHead.x < 0 || newHead.x >= 60 || newHead.y < 0 || newHead.y >= 60) {
                resetGame();
            }
            for (size_t i = 1; i < snake.size(); ++i) {
                if (snake[i] == newHead) {
                    resetGame(); 
                }
            }
            clock.restart();
        }
    }

    void render() {
        window.clear();

       
        for (auto& segment : snake) {
            sf::RectangleShape rectangle(sf::Vector2f(10, 10));
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setPosition(segment.x * 10, segment.y * 10);
            window.draw(rectangle);
        }

  
        window.draw(food);

        window.display();
    }

    void resetGame() {
    
        snake.clear();
        snake.push_back(sf::Vector2i(10, 10));
        direction = sf::Vector2i(1, 0); 
        food.setPosition(rand() % 60 * 10, rand() % 60 * 10); 
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}