// Project02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//GAME INSPIRED BY DOODLE JUMP
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

int main()
{
   RenderWindow window(VideoMode(640, 800),
        "BLUEBERRY JUMP",
        Style::Close | Style::Titlebar //titlbar +close button
    );

    Texture bluberryLeft;
    bluberryLeft.loadFromFile("Images/men_left.png");
    bluberryLeft.setSmooth(true);

    Texture bluberryRight;
    bluberryRight.loadFromFile("Images/men_right.png");
    bluberryRight.setSmooth(true);

    // Character setup
    Sprite character;
    character.setTexture(bluberryRight);
    character.setOrigin(44, 99);
    character.setPosition(320, 600);

    float characterRun = .0;
    float characterGravity = .0;

    bool isPressLeft = false;
    bool isPressRight = false;

    // Platforms setup
    RectangleShape plat(sf::Vector2f(100, 30));
    plat.setFillColor(sf::Color(253, 166, 165)); //red with half green and blue gives pink :)
    plat.setPosition(270, 700);

    std::vector<sf::RectangleShape> platforms;
    platforms.push_back(plat);
    //location for platform
    for (auto i = 1; i < 6; ++i) {
        plat.setPosition(rand() % 540, 700 - (i * 150));
        platforms.push_back(plat); //a new element to the vector each time a new integer is read
    }

    


    // Score
    sf::Font font;
    font.loadFromFile("Fonts/Anonymous Pro.ttf");

    sf::Text textScore;
    textScore.setFont(font);
    textScore.setString("Score: 0");
    textScore.setPosition(10, 10);
    textScore.setCharacterSize(36);
   
    int score = 0;

    // Game over
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setString("GAME OVER");
    gameOver.setPosition(175, 350);
    gameOver.setCharacterSize(64);
   

    // Timer
    Clock clock; //measures time

    bool isRun = true;


    // Start events
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left) {
                    character.setTexture(bluberryLeft);
                    isPressLeft = true;
                }

                if (event.key.code == Keyboard::Right) {
                    character.setTexture(bluberryRight);
                    isPressRight = true;
                }

                if (event.key.code == Keyboard::Return) {
                    score = 0;
                    // Platforms setup
                    plat.setPosition(270, 700);

                    platforms.clear();
                    platforms.push_back(plat);

                    for (auto i = 1; i < 6; ++i) {
                        plat.setPosition(rand() % 540, 700 - (i * 150));
                        platforms.push_back(plat);
                    }

                    

                    // Character
                    character.setPosition(320, 600);

                    characterRun = .0f;
                    characterGravity = .0f;
                    textScore.setString("Score: 0");

                    isRun = true;
                }
            }

            if (event.type == Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left) {
                    isPressLeft = false;
                }

                if (event.key.code == Keyboard::Right) {
                    isPressRight = false;
                }
            }


        }

        if (isRun) {
            // Logic
            if (clock.getElapsedTime().asMilliseconds() > 7) //character speed
            {
                character.move(characterRun, 0);

                if (character.getPosition().y >200 || characterGravity > 0) //speed at which we wanna go higher
                {
                    character.move(0, characterGravity); //we dont want charecter to move away
                }
                else {
                    for (auto& platform : platforms) {
                        platform.move(0, -characterGravity); ///0 because we dont want platform to move away
                    }
                    
                    score += 1;
                    textScore.setString("Score: " + std::to_string(score));
                }


                // controlling x coordinate speed
                if (isPressLeft) characterRun -= 0.1f;
                if (isPressRight) characterRun += 0.1f;

                if (characterRun > 0.0001f) { characterRun -= 0.01f; }
                else if (characterRun < -0.0001f) { characterRun += 0.01f; }
                else { characterRun = 0.0f; }

                characterGravity += 0.1f;

                sf::Vector2f charLeftPos = character.getPosition();
                charLeftPos.x -= 44;
                sf::Vector2f charRightPos = character.getPosition();
                charRightPos.x += 44;

                // Platform jump
                for (auto& platform : platforms) {
                    if (platform.getGlobalBounds().contains(charLeftPos)) {
                        if (characterGravity > 0) characterGravity = -9;
                        break;
                    }
                    else if (platform.getGlobalBounds().contains(charRightPos)) {
                        if (characterGravity > 0) characterGravity = -9;
                        break;
                    }
                }

       
                

                // Update platforms
                for (auto& platform : platforms) {
                    if (platform.getPosition().y > 800) {
                        platform.setPosition(rand() % 540, platform.getPosition().y);
                        platform.move(0, -1100);
                    }
                }

               
                // Left
                if (character.getPosition().x < -50) { character.move(690, 0); }
                else if (character.getPosition().x > 690) { character.move(-690, 0); }

                // Down
                if (character.getPosition().y > 850) { isRun = false; }

                clock.restart();
            }
        }

        // Drawing
        window.clear(sf::Color(104, 184, 193));

        for (auto& platform : platforms) {
            window.draw(platform);
        }

        
        window.draw(character);
        window.draw(textScore);
        if (!isRun) window.draw(gameOver);

        window.display();
    }

    return 0;
}