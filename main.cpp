#include "Config.h"
#include "Board.h"
#include <chrono>
#include <thread>

int main ( int nArgs, char * arg [] ) {

    size_t boardWidth, boardHeight, numBombs, tilesize;

    Config cfg ( "Majnswept.cfg" );

    Option optionBoardWidth ( 20ll );
    cfg.insertOption ( "boardWidth", optionBoardWidth );
    Option optionBoardHeight ( 20ll );
    cfg.insertOption ( "boardHeight", optionBoardHeight );
    Option optionMaxFPS ( 60.0L );
    cfg.insertOption ( "maxFPS", optionMaxFPS );
    Option optionNumBombs ( 70ll );
    cfg.insertOption ( "numBombs", optionNumBombs );
    Option optionSleepRecalculatePeriod ( 128ll );
    cfg.insertOption ( "sleepRecalculatePeriod", optionSleepRecalculatePeriod );
    Option optionTilesize ( 16ll );
    cfg.insertOption ( "tilesize", optionTilesize );

    cfg.loadConfigFile ( );

    optionBoardWidth = *cfg.getOption ( "boardWidth" );
    optionBoardHeight = *cfg.getOption ( "boardHeight" );
    optionMaxFPS = *cfg.getOption ( "maxFPS" );
    optionNumBombs = *cfg.getOption ( "numBombs" );
    optionSleepRecalculatePeriod = *cfg.getOption ( "sleepRecalculatePeriod" );
    optionTilesize = *cfg.getOption ( "tilesize" );

    boardWidth = optionBoardWidth.i;
    boardHeight = optionBoardHeight.i;
    maxFPS = optionMaxFPS.f;
    numBombs = optionNumBombs.i;
    sleepRecalculatePeriod = optionSleepRecalculatePeriod.i;
    tilesize = optionTilesize.i;

    cfg.saveConfigFile ( );

    loadAssets ( tilesize );

    if ( 2 < nArgs && nArgs < 4 ) {

        cerr << "Usage: Majnswept [width height numBombs]\n";
        return 1;

    }

    if ( 2 < nArgs ) {

        boardWidth =  atol ( arg [ 1 ] );
        boardHeight = atol ( arg [ 2 ] );
        numBombs =    atol ( arg [ 3 ] );

    }

    int nDraws = 0;
    sf::Time sleepTime;
    sf::Clock renderClock;

    Board mainBoard ( boardWidth, boardHeight, numBombs, tilesize );
    sf::RenderWindow mainWindow ( sf::VideoMode ( boardWidth * tilesize, boardHeight * tilesize ), "Majnswept: ", sf::Style::Close );


    while ( mainWindow.isOpen ( ) ) {

        string windowTitle = "Majnswept: " + mainBoard.getBoardStatus ( );
        //mainWindow.setTitle ( windowTitle );

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
        if ( nDraws % sleepRecalculatePeriod == 0 ) {

            renderClock.restart ( );
            mainWindow.draw ( mainBoard );
            sleepTime = sf::microseconds ( 1000000/maxFPS - renderClock.getElapsedTime ( ).asMicroseconds ( ) );
            
        } else mainWindow.draw ( mainBoard );

        mainWindow.display ( );

        sf::sleep ( sleepTime );

        if ( mainBoard.shouldQuitGame ( ) ) mainBoard = Board ( boardWidth, boardHeight, numBombs, tilesize );

    }

}
