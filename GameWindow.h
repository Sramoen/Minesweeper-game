#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "Board.h"
const float TILE_SIZE = 30.f;
class Tile {
public:
    sf::RectangleShape shape;
    bool revealed;
    bool hasMine;
    int textureIndex;

    Tile() : revealed(false), hasMine(false), textureIndex(-1) {
        shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color::Black);
        shape.setFillColor(sf::Color(148,148,148));
    }

    Tile(float x, float y, int textureIndex) : Tile() {
        shape.setPosition(x, y);
        this->textureIndex = textureIndex;
    }
    // Reveal (change color)
    void reveal() {
        revealed = true;
        shape.setFillColor(sf::Color(192, 192, 192)); 
    }

    // unreveal during reseting
    void unreveal(){
        revealed = false;
        shape.setFillColor(sf::Color(148, 148, 148));

    }
};


class GameWindow {
private:
    Board *board;
    std::vector<sf::Texture> textures;
    Tile** grid;
    bool choose_difficulty;

public:
    GameWindow(); // Constructor
    ~GameWindow(); // Destructor
    void run_difficulty();
    void run_game();
    void initialize_grid(int difficulty);
};