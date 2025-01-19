#ifndef CDXG_SHADER
#define CDXG_SHADER

#include <vector>

namespace cdxg {
    class Shader {
        public:
        Shader();
        Shader(char *vertexShader, char *fragmentShader);
        ~Shader();
        void Use();
        void Load();
        private:
        bool mbLoaded;
        const char *const mpcVertexShader;
        const char *const mpcFragmentShader;
        unsigned int muiShaderProgramId;
    };
    static Shader defaultShader;
} // namespace cdxg

#endif // CDXG_SHADER