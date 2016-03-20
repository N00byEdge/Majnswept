#pragma once
#include "Util.h"

enum Marker { none, flag, questionmark, revealed };

class Board: public sf::Drawable {

    public:

        Board ( size_t _height, size_t _width, size_t numBombs );
        ~Board ( );

        void gameOver ( );
        void youWin ( );

        int numAdjacentUncoveredTiles ( Location location );

        void clickTile ( Location & location, sf::Mouse::Button & button );
        void revealTile ( Location & location );
        void toggleMarker ( Location & location );

        void updateTexture ( Location & location );

        virtual void draw ( sf::RenderTarget &, sf::RenderStates ) const;

        void mouseButtonDown ( sf::Event::MouseButtonEvent );
        void mouseButtonUp ( sf::Event::MouseButtonEvent );
        void mouseMoved ( sf::Event::MouseButtonEvent );

        void setViewport ( Location viewportBegin, Location viewportEnd );

        template < typename T >
        void printBoardSizedMember ( vector < vector < T > > &, ostream & );

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

};
