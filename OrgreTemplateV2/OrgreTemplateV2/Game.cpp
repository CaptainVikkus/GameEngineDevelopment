#include "Game.h"
//#include <iostream>

Game::Game()
    : ApplicationContext("OgreTemplate-V2")
{
}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    mRoot = getRoot();
    mSceneManager = mRoot->createSceneManager();
    // get a pointer to the already created window
    mWindow = getRenderWindow();
    mWindow->resize(windowWidth, windowHeight);

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mSceneManager);

    //! [turnlights]
    mSceneManager->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = mSceneManager->createLight("MainLight");
    SceneNode* lightNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(-80, 80, 50);
    //! [lightpos]

    // --- Camera ---- //
    SceneNode* camNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
    Camera* cam = mSceneManager->createCamera("myCam");
    cam->setProjectionType(PT_ORTHOGRAPHIC);
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);
    mWindow->addViewport(cam); // and tell it to render into the main window
    //! [camera]

    // ---- Ball ---- //
    ball = new Ball(mSceneManager);
    // ---- Paddle ---- //
    bat = new Bat(mSceneManager);

    //mSceneManager->addRenderQueueListener(mOverlaySystem);
    // ---- Overlays ---- //
    OverlayManager& overlayManager = OverlayManager::getSingleton();

    // Create a panel
    OverlayContainer* panel = static_cast<OverlayContainer*>(
        overlayManager.createOverlayElement("Panel", "PanelName"));
    //panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(10, 10);
    panel->setDimensions(100, 100);
    panel->setMaterialName("BaseWhite"); // Optional background material

    // Create a text area
    //TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
    //    overlayManager.createOverlayElement("TextArea", "TextAreaName"));
    //textArea->setMetricsMode(Ogre::GMM_PIXELS);
    //textArea->setPosition(0, 0);
    //textArea->setDimensions(100, 100);
    //textArea->setCaption("Hello, World!");
    //textArea->setCharHeight(16);
    ////textArea->setFontName("TrebuchetMSBold");
    //textArea->setColourBottom(ColourValue(0.3, 0.5, 0.3));
    //textArea->setColourTop(ColourValue(0.5, 0.7, 0.5));

    // Create an overlay, and add the panel
    Overlay* overlay = overlayManager.create("OverlayName");
    overlay->add2D(panel);

    // Add the text area to the panel
    //panel->addChild(textArea);

    // Show the overlay
    overlay->show();
}

void Game::run()
{
    mRoot->startRendering();
}

bool Game::processEvents(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    // Quit
    case (SDLK_ESCAPE):
        getRoot()->queueEndRendering();
        break;
    // Move Bat
    case (SDLK_DOWN):
        //std::cout << bat->getPosition() << " against " << windowHeight * -1 << std::endl;
        if (!(bat->getPosition().y - 250 <= windowHeight * -1))
        {// Not hitting the bottom
            bat->moveDown();
        }
        break;
    case (SDLK_UP):
        //std::cout << bat->getPosition() << " against " << windowHeight << std::endl;
        if (!(bat->getPosition().y + 250 >= windowHeight))
        {// Not hitting the top
            bat->moveUp();
        }
        break;
    }
    return true;

}

bool Game::update(const FrameEvent& frameEvent)
{
    // ---- Scoring ---- //
    if (ball->getPosition().x + 20 > windowWidth) // scored goal
    {
        ball->hitGoal();
        score++;
    }
    else if (ball->getPosition().x - 20 < -windowWidth) // lost goal
    {
        ball->hitGoal();
        lives--;
    }
    // ---- Wall Collision ---- //
    if (ball->getPosition().y > windowHeight || ball->getPosition().y < -windowHeight)
    {
        ball->reboundSides();
    }
    // ---- Paddle Collision ---- //
    if (ball->getPosition().x - 20 < bat->getPosition().x + 20 && ball->getPosition().x + 20 > bat->getPosition().x - 20)
    {
        if (ball->getPosition().y - 20 < bat->getPosition().y + 150 && ball->getPosition().y + 20 > bat->getPosition().y - 150)
        {
            ball->reboundBat();
        }
    }
    // ---- Move Entities ---- //
    ball->update();
    bat->update();

    return true;
}

bool Game::render(const FrameEvent& frameEvent)
{
    return true;
}
