#include "testGame.hh"
#include "displayManager.hh"
#include <iostream>
#include "gameTime.hh"
#include "shader.hh"
#include "rawShaderHolder.hh"
#include "vertices.hh"
#include "displayable.hh"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace cdxg{

    TestGame::TestGame(int initialWidth, int initialHeight, std::string initialTitle)
        :GameTemplate(initialWidth, initialHeight, initialTitle)
        ,vertices({
            VertexRGB(-0.2, -0.2, 1.0, 0.0, 0.0),
            VertexRGB(0.2, 0.2, 0.0, 1.0, 0.0),
            VertexRGB(-0.2, 0.2, 0.0, 0.0, 1.0),
            VertexRGB(0.2, -0.2, 1.0, 1.0, 1.0)
        })
        ,indices({0, 1, 2, 0, 1, 3})
        ,mHighlightShader(Shader(_binary___assets_rgb_vs_glsl_start, _binary___assets_rgb_fs_glsl_start))
        {}

    TestGame::~TestGame(){}

    void TestGame::Initialize(){
        // initialize Uinput
        glfwSetInputMode(DisplayManager::mpsWindow, GLFW_STICKY_KEYS, 0);
        //initialize GameTime
        GameTime::msDeltaTimeSec = 0.0f;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Initialize()

    void TestGame::addRectangle(){
        //creates rectangle
        rectangles.push_back(Displayable<VertexRGB>());
        int iLastRecIndex = rectangles.size()-1;
        rectangles[iLastRecIndex].setVerticesIndices(indices, false);
        rectangles[iLastRecIndex].setVertices(vertices, false);
        rectangles[iLastRecIndex].load();

        if(state != -1) { return; }
        //if this is the first rectangle, select it as current rectangle and apply highlight shader to it
        state = 0;
        rectangles[0].setShader(&mHighlightShader);
    }

    void TestGame::removeRectangle(){
        //remove rectangle from list
        rectangles.erase(rectangles.begin() + state);

        //if the deleted rectangle was at the end of the list, decrement the index by one
        if(state >= rectangles.size()) { --state; }

        //if the deleted rectangle was the last one, return to idle state (-1)
        if(state == -1) { return; }

        //apply the shader to the new selected rectangle
        rectangles[state].setShader(&mHighlightShader);
    }

    void TestGame::processInput(){

        //* '+' key from keypad => add rect
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_ADD) == GLFW_PRESS && oldAddButtonState == GLFW_RELEASE){
            addRectangle();
        }

        //* esc key => close window
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(DisplayManager::mpsWindow, true);
        }


        //the instructions after this point are useless/could cause errors if no rectangle exists
        if(state == -1) { return; }

        //* directional keys => move rect
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_LEFT) == GLFW_PRESS){
            rectangles[state].move(-0.005, 0.0);
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_RIGHT) == GLFW_PRESS){
            rectangles[state].move(0.005, 0.0);
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_UP) == GLFW_PRESS){
            rectangles[state].move(0.0, 0.005);
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_DOWN) == GLFW_PRESS){
            rectangles[state].move(0.0, -0.005);
        }
        
        //* '-' key from keypad => remove a rect
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && oldSubButtonState == GLFW_RELEASE){
            removeRectangle();
        }

        //* space key => switch between rects
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_SPACE) == GLFW_PRESS && oldSpaceButtonState == GLFW_RELEASE){
            //remove highlight shader from current rectangle
            rectangles[state].setShader(&defaultShader);
            
            //change current rectangle
            if(state == rectangles.size()-1) { state = -1; }
            ++state;

            //add highlight shader to current rectangle
            rectangles[state].setShader(&mHighlightShader);
        }

        oldAddButtonState = glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_ADD);
        oldSubButtonState = glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_SUBTRACT);
        oldSpaceButtonState = glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_SPACE);
    }

    void TestGame::Update(){
        //update GameTime
        GameTime::msDeltaTimeSec = glfwGetTime() - GameTime::msTotalTimeSec;
        GameTime::msTotalTimeSec = glfwGetTime();

        processInput();
    } // void Update()

    void TestGame::Render(){
        //blank screen w/ bg color
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i = 0; i < rectangles.size(); ++i){
            rectangles[i].draw();
        }
        
        // display the current frame and init the next one
        glfwSwapBuffers(DisplayManager::mpsWindow);
    } // void Render()

} // namespace cdxg