#include "Game.h"
#include <iostream>

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

    // ---- HUD ---- //
    mTrayManager = new TrayManager("HUD", mWindow);
    mSceneManager->addRenderQueueListener(mOverlaySystem);

    livesLabel = mTrayManager->createLabel(TL_TOP, "Lives", "Lives: " + std::to_string(lives), 200);
    scoreLabel = mTrayManager->createLabel(TL_TOPRIGHT, "Score", "Score: " + std::to_string(score), 150);
    fpsLabel = mTrayManager->createLabel(TL_BOTTOMRIGHT, "fps", String("fps"), 150);
    tickLabel = mTrayManager->createLabel(TL_BOTTOMRIGHT, "tick", String("tick"), 150);
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
    if (ball->getPosition().y + 100 > windowHeight || ball->getPosition().y - 100 < -windowHeight)
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
    //bat->update(); //empty function

    // ---- Labels ---- //
    livesLabel->setCaption("Lives: " + std::to_string(lives));
    scoreLabel->setCaption("Score: " + std::to_string(score));
    fpsLabel->setCaption(std::to_string((int)(1 / frameEvent.timeSinceLastFrame)));
    tickLabel->setCaption(std::to_string(frameEvent.timeSinceLastFrame));

    mTrayManager->adjustTrays();

    return true;
}

bool Game::render(const FrameEvent& frameEvent)
{
    return true;
}
