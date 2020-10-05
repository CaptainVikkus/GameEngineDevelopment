//! [fullsource]

#include "Game.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        app.run();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]
