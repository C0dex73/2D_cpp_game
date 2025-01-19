#ifndef CDXG_DISPLAYABLE
#define CDXG_DISPLAYABLE

//#warning displayable called

#include <vector>
#include "vertices.hh"
#include "shader.hh"
#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

namespace cdxg
{
    class TestGame;
    
    template<class Vtype = Vertex>
    class Displayable {
        public:
        enum mGlDrawType {
            //IBO drawType is dynamic VBO drawType is dynamic
            DYNAMIC = 0,
            //IBO drawType is dynamic VBO drawType is dynamic
            DYNAMIC_DYNAMIC = 0,
            //IBO drawType is static VBO drawType is static
            STATIC = 1,
            //IBO drawType is static VBO drawType is static
            STATIC_STATIC = 1,
            //IBO drawType is static VBO drawType is dynamic
            DYNAMIC_STATIC = 2,
            //IBO drawType is dynamic VBO drawType is static
            STATIC_DYNAMIC = 3,
            //IBO drawType is stream VBO drawType is stream
            STREAM = 4
        };
        Displayable();
        ~Displayable();
        void draw();
        void move(float x, float y);
        
        private:
        friend class TestGame;

        void load();
        void setVertices(std::vector<Vtype> vertices, bool bRefreshVram = true);
        void setVerticesIndices(std::vector<unsigned int> verticesIndices, bool bRefreshVram = true);
        void setShader(Shader *shader);
        void unload();
        void refreshVram(bool forceRefresh = false, bool bindBuffers = true, int vertexArrayObjectCallbackID = 0);
        std::vector<unsigned int> muivVerticesIndices;
        mGlDrawType meDrawType;
        std::vector<Vtype> mvVertices;
        Shader *mpShader;
        unsigned int muiVao;
        unsigned int muiVbo;
        unsigned int muiIbo;
        bool mbVerticesModified;
        bool mbVerticesIndicesModified;
        bool mbLoaded;
        static const std::tuple<GLenum, GLenum> mateGlDrawType[];
    }; // class Displayable
} // namespace cdxg

//template definitions
#include "templates/displayable.tcc"

#endif // CDXG_DISPLAYABLE