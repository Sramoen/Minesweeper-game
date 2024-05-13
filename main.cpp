#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

const int ROWS = 10;
const int COLS = 10;
const float TILE_SIZE = 30.f;

class Tile {
public:
    sf::RectangleShape shape;
    bool revealed;
    bool hasMine;
    int textureIndex; // Index of the texture

    Tile() : revealed(false), hasMine(false), textureIndex(-1) {
        shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color::Black);
        shape.setFillColor(sf::Color(148,148,148)); // Light gray color
    }

    Tile(float x, float y, int textureIndex) : Tile() {
        shape.setPosition(x, y);
        this->textureIndex = textureIndex;
    }

    void reveal() {
        revealed = true;
        shape.setFillColor(sf::Color(192, 192, 192)); // Change color to white when revealed
    }

    void unreveal(){
        revealed = false;
        shape.setFillColor(sf::Color(148, 148, 148)); // Change color to white when revealed

    }
};

int main() {
    Board board(10,10);
    sf::RenderWindow window(sf::VideoMode(COLS * TILE_SIZE, ROWS * TILE_SIZE), "Minesweeper");

    std::vector<sf::Texture> textures;
    for (int i = 0; i <= 8; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("D:/AAA_kodovani/Roupec_C_Letni/gui/images/" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load image_" << i << std::endl;
            return 1; // Exit with an error if image loading fails
        }
        textures.push_back(texture);
    }

    Tile grid[ROWS][COLS];

    // Initialize grid
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = Tile(j * TILE_SIZE, i * TILE_SIZE, -1);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)&&!board.get_game_state()) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Handle left mouse button click
                // Render game over image and handle left mouse button click
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int row = mousePos.y / TILE_SIZE;
                    int col = mousePos.x / TILE_SIZE;
                    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                        // Reveal the clicked tile
                        board.make_move(row,col);
                    }

                }
            }
        }
        if(!board.get_game_state()){        
        // Render grid
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                
                window.draw(grid[i][j].shape);


                if(board.get_value(i,j)=='0'){
                    grid[i][j].reveal();
                    window.draw(grid[i][j].shape);
                }


                else if((board.get_value(i,j)=='*') && board.get_game_state()==true){
                    sf::Sprite sprite(textures[0]);
                    sprite.setScale(TILE_SIZE / sprite.getTexture()->getSize().x, TILE_SIZE / sprite.getTexture()->getSize().y);
                    sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    window.draw(sprite);                    
                }
                
                else{
                    int digitInt = board.get_value(i,j) - '0';
                    sf::Sprite sprite(textures[digitInt]);
                    sprite.setScale(TILE_SIZE / sprite.getTexture()->getSize().x, TILE_SIZE / sprite.getTexture()->getSize().y);
                    sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    window.draw(sprite);                    
                }
                
            }
        }
        }

    else{
            sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("D:/AAA_kodovani/Roupec_C_Letni/gui/images/play_again.png")) {
        // Error loading the image
    } else {
        // Create a sprite for the game over image
        sf::Sprite gameOverSprite(gameOverTexture);

        // Set the position of the game over image to the center of the window
        gameOverSprite.setPosition((window.getSize().x - gameOverSprite.getLocalBounds().width) / 2,
                                    (window.getSize().y - gameOverSprite.getLocalBounds().height) / 2);

        // Draw the game over image
        window.draw(gameOverSprite);

        // Handle left mouse button click only when the game is over
        sf::Event event2;

        while (window.pollEvent(event2))
         {
            if (event2.type == sf::Event::Closed) {
                window.close();
            }
            else if (event2.type == sf::Event::MouseButtonPressed) {
                if (event2.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::FloatRect gameOverBounds = gameOverSprite.getGlobalBounds();
                    if (gameOverBounds.contains(mousePos.x, mousePos.y)) {
                        // Restart the game (e.g., by resetting the board)
                        // For example:
                        board.restart();
                    // Unreveal grid  
                    for (int i = 0; i < ROWS; ++i) {
                        for (int j = 0; j < COLS; ++j) {
                            grid[i][j].unreveal();
                        }
                    }
                        break; // Exit the event handling loop after restarting the game
                    }
                    }
                
            }
        }
    }
    }


        window.display();
    }



    return 0;
}