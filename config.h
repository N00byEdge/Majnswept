#pragma once

#include "Util.h"

#include <fstream>
#include <string>
#include <map>

using namespace std;

enum OptionType { TYPE_INT, TYPE_FLOAT, TYPE_STRING, TYPE_BOOL, TYPE_UNDEF };

const string disallowedChars = " \n\r=";

struct Option {

    Option ( );
    Option ( long long );
    Option ( long double );
    Option ( string );
    Option ( bool );

    Option ( const Option & );

    OptionType type;

    string s;

    union {

        long long i;
        long double f;
        bool b;

    };

};

class Config {

    public:

        Config ( );
        Config ( string filename );

        string getFilename ( );
        void setFilename ( string filename );

        void saveConfigFile ( );
        void saveConfigFile ( string filename );

        void loadConfigFile ( );
        void loadConfigFile ( string filename );

        Option * getOption ( string name );

        void insertOption ( string name, Option option );
        void tryInsertOption ( string name, Option option );
        void removeOption ( string name );

        bool hasOption ( string name );

    protected:

    private:

        string filename;
        map < string, Option > options;

};
