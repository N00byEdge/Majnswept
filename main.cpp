#include "Board.h"
#include <chrono>
#include <thread>

int main ( int nArgs, char * arg [] ) {

    loadAssets ( );

    size_t boardWidth = 100, boardHeight = 100, numBombs = boardWidth * boardHeight / 6;

    if ( 2 < nArgs && nArgs < 4 ) {

        cerr << "Usage: Majnswept [width height numBombs]\n";
        return 1;

    }

    if ( 2 < nArgs ) {

        boardWidth =  ( int ) atol ( arg [ 1 ] );
        boardHeight = ( int ) atol ( arg [ 2 ] );
        numBombs =    ( int ) atol ( arg [ 3 ] );

    }

    Board mainBoard ( boardWidth, boardHeight, numBombs );

    sf::RenderWindow mainWindow ( sf::VideoMode ( boardWidth * tilesize, boardHeight * tilesize ), "Majnswept", sf::Style::Close );

    while ( mainWindow.isOpen ( ) ) {

        sf::Event event;

        while ( mainWindow.pollEvent ( event ) ) {

            switch ( event.type ) {

                case sf::Event::Closed:
                    mainWindow.close ( );
                    break;

                case sf::Event::Count: break;
                case sf::Event::GainedFocus: break;
                case sf::Event::JoystickButtonPressed: break;
                case sf::Event::JoystickButtonReleased: break;
                case sf::Event::JoystickConnected: break;
                case sf::Event::JoystickDisconnected: break;
                case sf::Event::JoystickMoved: break;
                case sf::Event::KeyPressed: break;
                case sf::Event::KeyReleased: break;
                case sf::Event::LostFocus: break;
                case sf::Event::MouseButtonPressed:

                    #ifdef DEBUG
                    if      ( event.mouseButton.button == sf::Mouse::Left )     printf ( "Left mouse button down at %d, %d\n", event.mouseButton.x, event.mouseButton.y );
                    else if ( event.mouseButton.button == sf::Mouse::Right )    printf ( "Right mouse button down at %d, %d\n", event.mouseButton.x, event.mouseButton.y );
                    else if ( event.mouseButton.button == sf::Mouse::Middle )   printf ( "Middle mouse button down at %d, %d\n", event.mouseButton.x, event.mouseButton.y );
                    else if ( event.mouseButton.button == sf::Mouse::XButton1 ) printf ( "X1 mouse button down at %d, %d\n", event.mouseButton.x, event.mouseButton.y );
                    else if ( event.mouseButton.button == sf::Mouse::XButton2 ) printf ( "X2 mouse button down at %d, %d\n", event.mouseButton.x, event.mouseButton.y );
                    else if ( event.mouseButton.button == sf::Mouse::XButton2 ) printf ( "Other mouse button down at %d, %d\n", event.mouseButton.x, event.mouseButton.y );
                    #endif //DEBUG

                    mainBoard.mouseButtonDown ( event.mouseButton );

                    break;

                case sf::Event::MouseButtonReleased: break;
                case sf::Event::MouseEntered: break;
                case sf::Event::MouseLeft: break;
                case sf::Event::MouseMoved: break;
                case sf::Event::MouseWheelMoved: break;
                case sf::Event::MouseWheelScrolled: break;
                case sf::Event::Resized: break;
                case sf::Event::SensorChanged: break;
                case sf::Event::TextEntered: break;
                case sf::Event::TouchBegan:

                    #ifdef DEBUG

                    printf ( "Touch at \n" );

                    #endif //DEBUG

                    break;

                case sf::Event::TouchEnded: break;
                case sf::Event::TouchMoved: break;

                default:
                    cerr << "Unhandled event.\n";
                    break;

            }

        }

        mainWindow.clear ( );
        mainWindow.draw ( mainBoard );
        mainWindow.display ( );

        this_thread::sleep_for ( chrono::milliseconds ( 10 ) );

        if ( mainBoard.quitgame ) mainBoard = Board ( boardWidth, boardHeight, numBombs );

    }

}
