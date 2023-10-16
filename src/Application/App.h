#pragma once
#define GLEW_STATIC
#include <chrono>
#include <GL/glew.h>
#include "Window.h"
#include "BasicScene.h"
#include "MenuScene.h"
#include "Scene2d.h"
#include "Logger.h"
#include "Renderer.h"

class App {
private:
    /** If OpenGL is already initalized. Used to prevent redundant initialization  */
    static bool sOpenGLInitialized_;
    /** Time of last update call */
    std::chrono::steady_clock::time_point mLastTime_;
    /** The window for this application*/
    Window mWindow_;
    /** The current Scenes of the application. List to allow controlled scene deleting */
    std::list<Scene*> mScenes_;
    /** Renderer used to*/
    Renderer* mpRenderer_ = nullptr;

public:
    /** Default Constructor */
    App();
    
    /** Destructor */
    ~App();
    
    /** Start and do the run loop */
    void run();
    
    /** Update the application components */
    void update();
    
    /** Render the application components */
    void render();

    /** If the application is currently running */
    bool isRunning() const;
    
    /**
     * Quits the application. Quit should be handled by the App and not the window to ensure
     * proper closure of the application
     */
    void quit();

    /**
     *  Set the current Scene of the application
     * \param newScene The new Scene
     */
    void setScene(Scene* newScene);
    
    /** 
     * Set Anti-Aliasing sample size. If the size is 0 then anti aliasing is disabled
     * \param sampleSize Anti aliasing sample size
     */
    void setAntiAliasing(unsigned int sampleSize);

    /** Get Application Window */
    Window& getWindow();

private:
    /** Initialize OpenGL if not already initialized */
    static void initializeOpenGL();
};