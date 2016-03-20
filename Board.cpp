#include "Board.h"

std::random_device randomDevice;
std::mt19937 mersenneTwister ( randomDevice ( ) );

sf::Texture tileTexture1;
sf::Texture tileTexture2;
sf::Texture tileTexture3;
sf::Texture tileTexture4;
sf::Texture tileTexture5;
sf::Texture tileTexture6;
sf::Texture tileTexture7;
sf::Texture tileTexture8;
sf::Texture tileTextureBomb;
sf::Texture tileTextureFlag;
sf::Texture tileTextureEmpty;
sf::Texture tileTextureHidden;
sf::Texture tileTextureNoBomb;
sf::Texture tileTextureQuestionMark;

template < typename T >
void Board::printBoardSizedMember ( vector < vector < T > > & m, ostream & os ) {

    for ( size_t y = 0; y < boardHeight; ++ y ) {

        for ( size_t x = 0; x < boardWidth; ++ x ) {

            os << m [ x ] [ y ] << " ";

        }

        os << "\n";

    }

}

Board::Board ( size_t _width, size_t _height, size_t _numBombs ): boardHeight ( _height ), boardWidth ( _width ), numBombs ( _numBombs ) {
	
	if ( boardHeight * boardWidth < numBombs ) exit ( 5 );

    /* Create tables */
    #ifdef DEBUG
    printf ( "Creating tables\n" );
    #endif // DEBUG

    hasBomb.resize ( boardWidth );
    for ( auto & e: hasBomb ) e.resize ( boardHeight, false );

    numAdjacent.resize ( boardWidth );
    for ( auto & e: numAdjacent ) e.resize ( boardHeight, 0 );

    markers.resize ( boardWidth );
    for ( auto & e: markers ) e.resize ( boardHeight, Marker::none );

    boardSprites.resize ( boardWidth );
    for ( auto & e: boardSprites ) e.resize ( boardHeight );

    /* Variables for board generation */
    vector < size_t > xBombs ( boardWidth, 0 );

    /* Distributions for randomizing */
    uniform_int_distribution < size_t > xDist ( 0, boardWidth );
    uniform_int_distribution < size_t > yDist ( 0, boardHeight );


    /* Distributing bombs uniformally between columns */
    #ifdef DEBUG
    printf ( "Distributing bombs uniformally between columns\n" );
    #endif // DEBUG

    for ( size_t i = 0; i < numBombs; ++ i ) {

        size_t randomX = xDist ( randomDevice );

        if ( xBombs [ randomX ] < boardWidth ) ++ xBombs [ randomX ];
        else -- i;

    }

    /* Distributing bombs between lines */
    #ifdef DEBUG
    printf ( "Distributing bombs between lines\n" );
    #endif // DEBUG

    for ( size_t x = 0; x < boardWidth; ++ x ) {

        for ( size_t i = 0; i < xBombs [ x ]; ++ i ) hasBomb [ x ] [ i ] = true;
        shuffle ( hasBomb [ x ].begin ( ), hasBomb [ x ].end ( ), randomDevice );

    }

    #ifdef DEBUG
    printBoardSizedMember ( hasBomb, cerr );
    #endif // DEBUG

    /* Generating numAdjacent */
    #ifdef DEBUG
    printf ( "Generating numAdjacent\n" );
    #endif // DEBUG

    for ( long long y = 0; y < boardHeight; ++ y ) {

        for ( long long x = 0; x < boardWidth; ++ x ) {

            if ( !hasBomb [ x ] [ y ] ) continue;

            for ( long long y2 = max ( y - 1, 0ll ); y2 <= min ( ( size_t ) y + 1, boardHeight - 1 ); ++ y2 ) {

                for ( long long x2 = max ( x - 1, 0ll ); x2 <= min ( ( size_t ) x + 1, boardWidth - 1 ); ++ x2 )
                    ++ numAdjacent [ x2 ] [ y2 ];

            }
			
        }
		
    }

    #ifdef DEBUG
    printBoardSizedMember ( numAdjacent, cerr );
    #endif // DEBUG

    for ( size_t y = 0; y < boardHeight; ++ y ) {

        for ( size_t x = 0; x < boardWidth; ++ x ) {

            #ifdef DEBUG
            //cerr << x << ", " << y << endl;
            #endif // DEBUG

            markers [ x ] [ y ] = Marker::none;

            Location location;
            location.x = x;
            location.y = y;
            updateTexture ( location );

            boardSprites [ x ] [ y ].setPosition ( x * tilesize, y * tilesize );

        }

    }

    numUnrevealedTiles = boardHeight * boardWidth;

}

Board::~Board ( ) {

}

void Board::draw ( sf::RenderTarget & target, sf::RenderStates states ) const {

    for ( size_t y = 0; y < boardHeight; ++ y ) {

        for ( size_t x = 0; x < boardWidth; ++ x ) {

            #ifdef DEBUGG
            cerr << x << ", " << y << ", "
                 << boardSprites [ x ] [ y ].getPosition ( ).x << ", "
                 << boardSprites [ x ] [ y ].getPosition ( ).y << ", "
                 << boardSprites [ x ] [ y ].getScale ( ).x << ", "
                 << boardSprites [ x ] [ y ].getScale ( ).y << ", "
                 << boardSprites [ x ] [ y ].getGlobalBounds ( ).left << ", "
                 << boardSprites [ x ] [ y ].getGlobalBounds ( ).top << ", "
                 << boardSprites [ x ] [ y ].getGlobalBounds ( ).width << ", "
                 << boardSprites [ x ] [ y ].getGlobalBounds ( ).height << ", "
                 << endl;
            #endif //DEBUG
            target.draw ( boardSprites [ x ] [ y ] );

        }

    }

}

void Board::updateTexture ( const Location & location ) {

    switch ( markers [ location.x ] [ location.y ] ) {

        case Marker::revealed:

            switch ( numAdjacent [ location.x ] [ location.y ] ) {

                case 0:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTextureEmpty );
                    break;

                case 1:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture1 );
                    break;

                case 2:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture2 );
                    break;

                case 3:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture3 );
                    break;

                case 4:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture4 );
                    break;

                case 5:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture5 );
                    break;

                case 6:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture6 );
                    break;

                case 7:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture7 );
                    break;

                case 8:
                    boardSprites [ location.x ] [ location.y ].setTexture ( tileTexture8 );
                    break;

            }

            break;

        case Marker::questionmark:

            boardSprites [ location.x ] [ location.y ].setTexture ( tileTextureQuestionMark );
            break;

        case Marker::flag:

            boardSprites [ location.x ] [ location.y ].setTexture ( tileTextureFlag );
            break;

        case Marker::none:

            boardSprites [ location.x ] [ location.y ].setTexture ( tileTextureHidden );


    }

}

void Board::reveal ( ) {

    for ( size_t y = 0; y < boardHeight; ++ y ) {

        for ( size_t x = 0; x < boardWidth; ++ x ) {

            if ( markers [ x ] [ y ] == Marker::flag ) {

                if ( hasBomb [ x ] [ y ] ) boardSprites [ x ] [ y ].setTexture ( tileTextureBomb );
                else                       boardSprites [ x ] [ y ].setTexture ( tileTextureNoBomb );

            } else if ( markers [ x ] [ y ] == Marker::none && hasBomb [ x ] [ y ] ) boardSprites [ x ] [ y ].setTexture ( tileTextureBomb );

        }

    }

}

void Board::gameOver ( ) {

    reveal ( );
    shouldQuitOnNextClick = true;

}

void Board::youWin ( ) {

    reveal ( );
    shouldQuitOnNextClick = true;

}

void Board::toggleMarker ( const Location & location ) {

    switch ( markers [ location.x ] [ location.y ] ) {

        case Marker::questionmark:

            markers [ location.x ] [ location.y ] = Marker::none;
            updateTexture ( location );
            break;

        case Marker::flag:

            markers [ location.x ] [ location.y ] = Marker::questionmark;
            updateTexture ( location );
            break;

        case Marker::none:

            markers [ location.x ] [ location.y ] = Marker::flag;
            updateTexture ( location );
            break;

        case Marker::revealed:

            revealTile ( location );

    }

}

void Board::revealTile ( const Location & location ) {

    #ifdef DEBUG
    printf ( "Revealing tile %zu, %zu\n", location.x, location.y );
    #endif // DEBUG

    if ( hasBomb [ location.x ] [ location.y ] ) gameOver ( );
    else {

        if ( markers [ location.x ] [ location.y ] == Marker::revealed ) {

            if ( numAdjacentFlaggedTiles ( location ) == numAdjacent [ location.x ] [ location.y ] ) {

                for ( long long y2 = max ( ( ( long long ) location.y ) - 1, 0ll ); y2 <= min ( ( long long ) location.y + 1, ( ( long long ) boardHeight ) - 1 ); ++ y2 ) {

                    for ( long long x2 = max ( ( ( long long ) location.x ) - 1, 0ll ); x2 <= min ( ( long long ) location.x  + 1, ( ( long long ) boardWidth ) - 1 ); ++ x2 ) {

                        if ( markers [ x2 ] [ y2 ] == Marker::none ) {

                            Location nextlocation;
                            nextlocation.x = x2;
                            nextlocation.y = y2;

                            revealTile ( nextlocation );

                        }

                    }

                }

            }

        } else {

        	markers [ location.x ] [ location.y ] = Marker::revealed;
        	updateTexture ( location );
        	-- numUnrevealedTiles;

        	if ( !numAdjacent [ location.x ] [ location.y ] ) {

            	Location nextLocation;

            	for ( long long y2 = max ( ( ( long long ) location.y ) - 1, 0ll ); y2 <= min ( ( long long ) location.y + 1, ( ( long long ) boardHeight ) - 1 ); ++ y2 ) {

                	for ( long long x2 = max ( ( ( long long ) location.x ) - 1, 0ll ); x2 <= min ( ( long long ) location.x  + 1, ( ( long long ) boardWidth ) - 1 ); ++ x2 ) {

                    	if ( markers [ x2 ] [ y2 ] != Marker::revealed ) {

                        	nextLocation.x = x2;
                        	nextLocation.y = y2;

                        	revealTile ( nextLocation );

                    	}

                	}

            	}

        	}
			
		}

    }

	#ifdef DEBUG
	cerr << numUnrevealedTiles << ", " << numBombs << "\n";
	#endif //DEBUG

    if ( numUnrevealedTiles == numBombs ) youWin ( );

}

void Board::clickTile ( const Location & location, sf::Mouse::Button & button ) {

    #ifdef DEBUG
    printf ( "Click at location %zu, %zu\n", location.x, location.y );
    #endif // DEBUG

    if ( button == sf::Mouse::Button::Left ) {

        switch ( markers [ location.x ] [ location.y ] ) {

            case Marker::none:

                revealTile ( location );
                break;

            case Marker::questionmark:

                revealTile ( location );
                break;

            case Marker::revealed:

                revealTile( location );
                break;

            case Marker::flag:

                break;

        }

    } else if ( button == sf::Mouse::Button::Right ) {

        toggleMarker ( location );

    }

}

void loadAssets ( ) {

    #ifdef DEBUG
    printf ("Loading assets\n");
    #endif // DEBUG

    string tilesizestring = to_string ( tilesize );

    string texturefile;

    texturefile = "./assets/img/" + tilesizestring + "_1.png";
    if ( !tileTexture1.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_2.png";
    if ( !tileTexture2.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_3.png";
    if ( !tileTexture3.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_4.png";
    if ( !tileTexture4.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_5.png";
    if ( !tileTexture5.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_6.png";
    if ( !tileTexture6.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_7.png";
    if ( !tileTexture7.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_8.png";
    if ( !tileTexture8.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_bomb.png";
    if ( !tileTextureBomb.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_flag.png";
    if ( !tileTextureFlag.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_empty.png";
    if ( !tileTextureEmpty.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_hidden.png";
    if ( !tileTextureHidden.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_nobomb.png";
    if ( !tileTextureNoBomb.loadFromFile ( texturefile ) ) exit ( 5 );

    texturefile = "./assets/img/" + tilesizestring + "_questionmark.png";
    if ( !tileTextureQuestionMark.loadFromFile ( texturefile ) ) exit ( 5 );

    #ifdef DEBUG
    printf ("Finished loading assets\n");
    #endif // DEBUG

}

void Board::mouseButtonDown ( sf::Event::MouseButtonEvent mbevent ) {

    if ( shouldQuitOnNextClick ) quitgame = true;

    Location t;
    t.x = mbevent.x / tilesize;
    t.y = mbevent.y / tilesize;

    clickTile ( t, mbevent.button );

}

void Board::mouseButtonUp ( sf::Event::MouseButtonEvent ) {



}

void Board::mouseMoved ( sf::Event::MouseButtonEvent ) {



}

int Board::numAdjacentFlaggedTiles ( const Location & location ) {

    int adj = 0;

    for ( long long y2 = max ( ( ( long long ) location.y ) - 1, 0ll ); y2 <= min ( ( long long ) location.y + 1, ( ( long long ) boardHeight ) - 1 ); ++ y2 ) {

        for ( long long x2 = max ( ( ( long long ) location.x ) - 1, 0ll ); x2 <= min ( ( long long ) location.x  + 1, ( ( long long ) boardWidth ) - 1 ); ++ x2 ) {

            if ( markers [ x2 ] [ y2 ] == Marker::flag || markers [ x2 ] [ y2 ] == Marker::questionmark ) ++ adj;

        }

    }

    return adj;

}
