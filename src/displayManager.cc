#include "displayManager.hh"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include "shader.hh"
#include <glad/glad.h>

namespace cdxg {
    void DisplayManager::CreateWindow(int width, int height, std::string title){
        // initialize glfw
        if( !glfwInit() )
        {
            fprintf( stderr, "Failed to initialize GLFW.\r\n" );
            return;
        } // if failed glfw init
        
        // opengl context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6 core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, 0); // We don't want resizable window

        // creates the window
        mpsWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if( !mpsWindow ) {
            fprintf(stderr, "Failed to open GLFW window.\r\n");
            glfwTerminate();
            return;
        } // if no window

        //opengl init
        gladLoadGL();

        //make the new window focused
        glfwFocusWindow(mpsWindow);        

        //init glad
        glfwMakeContextCurrent(mpsWindow);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            fprintf(stderr, "Failed to initialize GLAD.\r\n");
            glfwTerminate();
            return;
        } // if glad cant init

        //tells opengl window size
        glViewport(0, 0, width, height);        
    } // void InitializeDisplayAPI()

    void DisplayManager::CloseWindow(){
    glfwTerminate();
    } // void CloseWindow()
} // namespace cdxg