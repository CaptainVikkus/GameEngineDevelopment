#include "Game.h"

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

    //! [camera]
    SceneNode* camNode = mSceneManager->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = mSceneManager->createCamera("myCam");
    cam->setProjectionType(PT_ORTHOGRAPHIC);
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    mWindow = getRenderWindow();
    mWindow->addViewport(cam);
    mWindow->resize(windowWidth, windowHeight);
    //! [camera]

    //! [entity1]
    //Entity* ogreEntity = mSceneManager->createEntity("ogrehead.mesh");
    //SceneNode* ogreNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
    //ogreNode->attachObject(ogreEntity);
    //! [entity1]

    //! [entity4]
    Entity* ogreEntity4 = mSceneManager->createEntity("cube.mesh");
    SceneNode* ogreNode4 = mSceneManager->getRootSceneNode()->createChildSceneNode();
    ogreNode4->setPosition(-600, 0, 0);
    ogreNode4->setScale(0.5, 3, 0.5);
    //ogreNode4->roll(Degree(-90));
    ogreNode4->attachObject(ogreEntity4);
    //! [entity4]

    // ---- Ball ---- //
    ball = new Ball(mSceneManager);


    // ---- !Ball ----//
}

void Game::run()
{
    mRoot->startRendering();
}

bool Game::processEvents(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;

}

bool Game::update(const FrameEvent& frameEvent)
{
    ball->update();
    return true;
}

bool Game::render(const FrameEvent& frameEvent)
{
    return true;
}
