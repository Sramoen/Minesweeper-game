#include "GameWindow.h"

GameWindow::GameWindow(){
    // Load images
    for (int i = 0; i <= 14; i++) {
        sf::Texture texture;
        if (!texture.loadFromFile("D:/AAA_kodovani/Roupec_C_Letni/gui/images/" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load image_" << i << std::endl;
            exit(1); // Exit with an error if image loading fails
        }
        textures.push_back(texture);
    }
    board = nullptr;
    grid=nullptr;
}

GameWindow::~GameWindow() {
    // Free dynamically allocated memory
    if (grid != nullptr) {
        for (int i = 0; i < board->get_shape(); i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
}

void GameWindow::run_difficulty() {
    bool choose_dificulty = false;
//Create settings window
    sf::RenderWindow window1(sf::VideoMode(10 * TILE_SIZE, 10 * TILE_SIZE), "Minesweeper");
    while (window1.isOpen()) {

             sf::Sprite sprite1(textures[9]), sprite2(textures[10]), sprite3(textures[11]), sprite4(textures[12]);

            // Set the scale factor for all sprites
            window1.clear(sf::Color::Blue);
            float scaleFactor = 0.5f;
            sprite1.setScale(scaleFactor, scaleFactor);
            sprite2.setScale(scaleFactor, scaleFactor);
            sprite3.setScale(scaleFactor, scaleFactor);
            sprite4.setScale(scaleFactor, scaleFactor);
            // Position the sprites
            sprite1.setPosition(35, 0);
            sprite2.setPosition(110, 100);
            sprite3.setPosition(100, 150);
            sprite4.setPosition(110, 200);

            window1.draw(sprite1);
            window1.draw(sprite2);
            window1.draw(sprite3);
            window1.draw(sprite4);
            sf::Event event0;
             while (window1.pollEvent(event0)) {
            if (event0.type == sf::Event::Closed) {
                window1.close();
            } else if (event0.type == sf::Event::MouseButtonPressed) {
                // Check if mouse click is within one of the sprites
                sf::Vector2i mousePos = sf::Mouse::getPosition(window1);
                if (sprite2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        initialize_grid(1);
                        board = new Board(5, 5);
                        choose_dificulty = true;
                        window1.close();
                } else if (sprite3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        initialize_grid(2);
                        board = new Board(10, 10);
                        choose_dificulty = true;
                        window1.close();
                } else if (sprite4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        initialize_grid(3);
                        board = new Board(15, 30);
                        choose_dificulty = true;
                        window1.close();
                }
            }
            
        }
                window1.display();

        }
    }

void GameWindow::initialize_grid(int difficulty) {
   int ROWS;
    if (difficulty == 1) {
        ROWS = 5;
    } else if (difficulty == 2) {
        ROWS = 10;
    } else {
        ROWS = 15;
    }

    // Dynamically allocate memory for the grid
    grid = new Tile*[ROWS];
    for (int i = 0; i < ROWS; i++) {
        grid[i] = new Tile[ROWS];
    }

    // Initialize grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            grid[i][j] = Tile(j * TILE_SIZE, i * TILE_SIZE, -1);
        }
    }
}

void GameWindow::run_game(){
     // Load grid
        sf::RenderWindow window(sf::VideoMode(board->get_shape() * TILE_SIZE, board->get_shape() * TILE_SIZE), "Minesweeper");
        while(window.isOpen()){

        // Checking if tile was clicked
        sf::Event event;
        while (window.pollEvent(event)&&!board->get_game_state()) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int row = mousePos.y / TILE_SIZE;
                    int col = mousePos.x / TILE_SIZE;
                    if (row >= 0 && row < board->get_shape() && col >= 0 && col < board->get_shape()) {
                        // Make a move
                        board->make_move(row,col);
                    }

                }
            }
        }

        // If game is not over - draw board
        if(!board->get_game_state()){        
        // Render grid
        for (int i = 0; i < board->get_shape(); ++i) {
            for (int j = 0; j < board->get_shape(); ++j) {
                


                if(board->get_value(i,j)=='0'){
                    grid[i][j].reveal();
                    window.draw(grid[i][j].shape);
                }

                else if((board->get_value(i,j)=='-')||(board->get_value(i,j)=='*')){
                    window.draw(grid[i][j].shape);

                }
                
                else{
                    int digitInt = board->get_value(i,j) - '0';
                    sf::Sprite sprite(textures[digitInt]);
                    sprite.setScale(TILE_SIZE / sprite.getTexture()->getSize().x, TILE_SIZE / sprite.getTexture()->getSize().y);
                    sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    window.draw(sprite);       
                }

                
            }
        }
        }

    // If game is over draw mines and game over sign
    else{
    sf::Texture gameOverTexture;
    if(board->get_game_state()==2){
        gameOverTexture = textures[13];
    }
    else{
        gameOverTexture = textures[14];
    }

    sf::Sprite gameOverSprite(gameOverTexture);

    gameOverSprite.setPosition((window.getSize().x - gameOverSprite.getLocalBounds().width) / 2,
                                (window.getSize().y - gameOverSprite.getLocalBounds().height) / 2);


    // Draw the game over image
    for (int i = 0; i < board->get_shape(); ++i) {
        for (int j = 0; j < board->get_shape(); ++j){ 
                if ((board->get_value(i,j)=='*') ){
                    sf::Sprite sprite(textures[0]);
                    sprite.setScale(TILE_SIZE / sprite.getTexture()->getSize().x, TILE_SIZE / sprite.getTexture()->getSize().y);
                    sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    window.draw(sprite);
                }                    
                }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    window.draw(gameOverSprite);


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
                    board->restart();
                // Unreveal grid  
                for (int i = 0; i < board->get_shape(); ++i) {
                    for (int j = 0; j < board->get_shape(); ++j) {
                        grid[i][j].unreveal();
                    }
                }
                    break; // Exit the event handling loop after restarting the game
                    }
                    }
                
            }
        }
    }
           window.display();
    }
}