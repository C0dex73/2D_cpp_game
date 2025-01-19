#include "shader.hh"
#include "rawShaderHolder.hh"
#include <glad/glad.h>
#include <iostream>

namespace cdxg
{
    Shader::Shader()
    :mbLoaded(false)
    ,muiShaderProgramId(0)
    ,mpcVertexShader(_binary___assets_source_vs_glsl_start)
    ,mpcFragmentShader(_binary___assets_source_fs_glsl_start)
    {}

    Shader::Shader(char *vertexShader, char *fragmentShader)
    :mbLoaded(false)
    ,muiShaderProgramId(0)
    ,mpcVertexShader(vertexShader)
    ,mpcFragmentShader(fragmentShader)
    {}

    Shader::~Shader()
    {
        if(!mbLoaded){ return; }
        glDeleteProgram(muiShaderProgramId);
    }

    void Shader::Use()
    {
        if(!mbLoaded){
            std::cout << "WARNING::SHADER::PROGRAM::USED_BEFORE_LOADED\n\tCounter-action : Loading shader" << std::endl;
            Load();
        }
        glUseProgram(muiShaderProgramId);
    }

    void Shader::Load()
    {
        if(mbLoaded) { return; }

        //create an opengl shader program
        muiShaderProgramId = glCreateProgram();

        //compile vertex shader
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &mpcVertexShader, NULL);
        glCompileShader(vertexShaderId);

        int sucess;
        char infoLog[512];
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &sucess);
        if(!sucess)
        {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //compile fragment shader
        unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &mpcFragmentShader, NULL);
        glCompileShader(fragmentShaderId);

        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &sucess);
        if(!sucess)
        {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //link both shaders and shader program
        glAttachShader(muiShaderProgramId, vertexShaderId);
        glAttachShader(muiShaderProgramId, fragmentShaderId);
        glLinkProgram(muiShaderProgramId);

        //delete shaders
        glDetachShader(muiShaderProgramId, vertexShaderId);
        glDetachShader(muiShaderProgramId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        mbLoaded = true;
    }
} // namespace cdxg