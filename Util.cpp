#include "Util.h"

void loadAssets ( size_t tilesize ) {

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
