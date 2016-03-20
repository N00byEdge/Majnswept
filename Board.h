#pragma once
#include "Util.h"

enum Marker { none, flag, questionmark, revealed };

class Board: public sf::Drawable {

    public:

        Board ( size_t _width, size_t _height, size_t numBombs );
        ~Board ( );

        void clickTile ( const Location & location, sf::Mouse::Button & button );

        virtual void draw ( sf::RenderTarget &, sf::RenderStates ) const;

        void mouseButtonDown ( sf::Event::MouseButtonEvent );

        bool quitgame = false;

    protected:

    private:

        vector < vector < bool > > hasBomb;
        vector < vector < int > > numAdjacent;
        vector < vector < Marker > > markers;
        vector < vector < sf::Sprite > > boardSprites;

        size_t boardHeight;
        size_t boardWidth;
        size_t numBombs;

        //int * drawTable;

        Location lastMousePos;
        bool lastWasPressed = false;
        bool isDragging;

        Location cameraPos = { 0, 0 };
        Location viewportBegin;
        Location viewportEnd;

        size_t numUnrevealedTiles;

        bool shouldQuitOnNextClick = 0;

        void gameOver ( );
        void youWin ( );

        void reveal ( );

        int numAdjacentFlaggedTiles ( const Location & location );

        template < typename T >
        void printBoardSizedMember ( vector < vector < T > > &, ostream & );
        void revealTile ( const Location & location );
        void toggleMarker ( const Location & location );
        void updateTexture ( const Location & location );
        void mouseButtonUp ( sf::Event::MouseButtonEvent );
        void mouseMoved ( sf::Event::MouseButtonEvent );
        void setViewport ( Location viewportBegin, Location viewportEnd );

};
