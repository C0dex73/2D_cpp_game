#ifndef CDXG_RAW_SHADER_HOLDER
#define CDXG_RAW_SHADER_HOLDER

#pragma region SHADER_POINTERS
// Get shaders from linked and compiled .glsl files
// To get all the symbols names,
// run make shaders then run objdump -x bin/rawShaders.o
#pragma region SOURCE
extern char _binary___assets_source_vs_glsl_start[];
extern char _binary___assets_source_vs_glsl_end[];

extern char _binary___assets_source_fs_glsl_start[];
extern char _binary___assets_source_fs_glsl_end[];
#pragma endregion
#pragma region RGB
extern char _binary___assets_rgb_vs_glsl_start[];
extern char _binary___assets_rgb_vs_glsl_end[];

extern char _binary___assets_rgb_fs_glsl_start[];
extern char _binary___assets_rgb_fs_glsl_end[];
#pragma endregion
#pragma region RGBA
extern char _binary___assets_rgba_vs_glsl_start[];
extern char _binary___assets_rgba_vs_glsl_end[];

extern char _binary___assets_rgba_fs_glsl_start[];
extern char _binary___assets_rgba_fs_glsl_end[];
#pragma endregion
#pragma endregion

namespace cdxg::RawShaders
{
    class ShaderFormater {
        public:
        ShaderFormater();
        private:
        static bool mbLoaded;
    };
    static ShaderFormater shaderFormater;
} // namespace cdxg::RawShaders


#endif //CDXG_RAW_SHADER_HOLDER