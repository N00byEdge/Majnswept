#include "config.h"

Option::Option ( ): s ( "" ) {

    type = OptionType::TYPE_UNDEF;

}

Option::Option ( long long data ): i ( data ), type ( OptionType::TYPE_INT ), s ( "" ) {

}

Option::Option ( long double data ): f ( data ), type ( OptionType::TYPE_FLOAT ), s ( "" ) {

}

Option::Option ( string data ): s ( data ), type ( OptionType::TYPE_STRING ) {

}

Option::Option ( bool data ): b ( data ), type ( OptionType::TYPE_BOOL ), s ( "" ) {

}

Option::Option ( const Option & other ) {

    type = other.type;

    switch ( type ) {

        case OptionType::TYPE_INT:

            i = other.i;
            s = "";
            break;

        case OptionType::TYPE_FLOAT:

            f = other.f;
            s = "";
            break;

        case OptionType::TYPE_STRING:

            s = other.s;
            break;

        case OptionType::TYPE_BOOL:

            b = other.b;
            s = "";
            break;

        case OptionType::TYPE_UNDEF:

            s = "";
            break;

    }

}

bool isAllowedOptionName ( string name ) {

    for ( auto disChar: disallowedChars ) if ( name.find ( disChar ) != npos ) return false;

    return true;

}

Config::Config ( ): filename ( "Unnamed config file.cfg" ) {



}

Config::Config ( string _filename ): filename ( _filename ) {



}

string Config::getFilename ( ) {

    return filename;

}

void Config::setFilename ( string _filename ) {

    filename = _filename;

}

void Config::saveConfigFile ( ) {

    return saveConfigFile ( filename );

}

void Config::saveConfigFile ( string _filename ) {

    ofstream configFile;
    configFile.open ( _filename );
    if ( configFile.is_open ( ) ) {

        for ( auto & o: options ) {

            switch ( o.second.type ) {

                case OptionType::TYPE_INT:

                    configFile << "i:" << o.first << "=" << o.second.i << "\n";
                    break;

                case OptionType::TYPE_FLOAT:

                    configFile << "f:" << o.first << "=" << o.second.f << "\n";
                    break;

                case OptionType::TYPE_STRING:

                    configFile << "s:" << o.first << "=" << o.second.s << "\n";
                    break;

                case OptionType::TYPE_BOOL:

                    configFile << "b:" << o.first << "=" << o.second.b << "\n";
                    break;

                case OptionType::TYPE_UNDEF:

                    cerr << "Failed to write undefined type option.\n";
                    exit ( 57 );

            }

        }

        configFile << flush;

    } else {

        cerr << "Could not write file " << _filename << ".\nPlease make sure this file is readable.\n";
        exit ( 55 );

    }

}

void Config::loadConfigFile ( ) {

    return loadConfigFile ( filename );

}

void Config::loadConfigFile ( string _filename ) {

    /* Load the config file */
    ifstream configFile;
    configFile.open ( _filename );
    string currentLine;
    size_t namebegin, nameend, databegin, dataend;

    if ( configFile.is_open ( ) ) {

        while ( getline ( configFile, currentLine ) ) {

            if ( currentLine.size ( ) < 1 ) break;
            char typechar = currentLine [ 0 ];

            if        ( typechar == 'i' ) {

                namebegin = 2ull;
                nameend = currentLine.find ( '=' );
                databegin = nameend + 1ull;
                dataend = currentLine.size ( );
                Option intOption ( ( long long ) atol ( currentLine.substr ( databegin, dataend - databegin ).c_str ( ) ) );
                insertOption ( currentLine.substr ( namebegin, nameend - namebegin ), intOption );

            } else if ( typechar == 'f' ) {

                namebegin = 2ull;
                nameend = currentLine.find ( '=' );
                databegin = nameend + 1ull;
                dataend = currentLine.size ( );
                Option floatOption ( ( long double ) atof ( currentLine.substr ( databegin, dataend - databegin ).c_str ( ) ) );
                insertOption ( currentLine.substr ( namebegin, nameend - namebegin ), floatOption );

            } else if ( typechar == 's' ) {

                namebegin = 2ull;
                nameend = currentLine.find ( '=' );
                databegin = nameend + 1ull;
                dataend = currentLine.size ( );
                Option stringOption ( currentLine.substr ( databegin, dataend - databegin ).c_str ( ) );
                insertOption ( currentLine.substr ( namebegin, nameend - namebegin ), stringOption );

            } else if ( typechar == 'b' ) {

                namebegin = 2ull;
                nameend = currentLine.find ( '=' );
                databegin = nameend + 1ull;
                dataend = currentLine.size ( );
                Option boolOption ( ( bool ) atoi ( currentLine.substr ( databegin, dataend - databegin ).c_str ( ) ) );
                insertOption ( currentLine.substr ( namebegin, nameend - namebegin ), boolOption );

            }

        }

        configFile.close ( );

    }

}

Option * Config::getOption ( string name ) {

    auto ptr = options.find ( name );

    return ptr == options.end ( ) ? nullptr : & ptr -> second;

}

void Config::insertOption ( string name, Option option ) {

    if ( !isAllowedOptionName ( name ) || option.type == TYPE_UNDEF ) return;

    options [ name ] = option;

}

void Config::tryInsertOption ( string name, Option option ) {

    if ( !isAllowedOptionName ( name ) || option.type == TYPE_UNDEF ) return;

    auto it = options.find ( name );
    if ( it == options.end ( ) ) options [ name ] = option;

}

void Config::removeOption ( string name ) {

    options.erase ( name );

}

bool Config::hasOption ( string name ) {

    auto it = options.find ( name );
    if ( it == options.end ( ) ) return false;
    else                         return true;

}
