#pragma once
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreOverlay.h"
#include "OgreTrays.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "Ball.h"
#include "Bat.h"
#include <string>

using namespace Ogre;
using namespace OgreBites;

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    Ball* ball;
    Bat* bat;
    Label* livesLabel;
    Label* scoreLabel;
    Label* fpsLabel;
    Label* tickLabel;
    // mFont;
    // mIcon;
    // mMusic;
    // mText;

    RenderWindow* mWindow;
    Root* mRoot;
    SceneManager* mSceneManager;
    TrayManager* mTrayManager;

    int lives = 5;
    int score = 0;
    int windowHeight = 600;
    int windowWidth = 800;
    
public:
    Game();
    virtual ~Game() {}

    void setup();
    void run();

private:
    //Overloaded Application Even Functions
    bool keyPressed(const KeyboardEvent& evt) 
        { return processEvents(evt); }
    bool frameStarted(const FrameEvent& frameEvent) 
        { ApplicationContext::frameStarted(frameEvent); return update(frameEvent); }
    bool frameEnded(const FrameEvent& frameEvent) 
        { ApplicationContext::frameEnded(frameEvent); return render(frameEvent); }

    //My Application Event Functions
    bool processEvents(const KeyboardEvent& evt);
    bool update(const FrameEvent& frameEvent);
    bool render(const FrameEvent& frameEvent);

};
