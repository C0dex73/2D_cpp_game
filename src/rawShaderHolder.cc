#include "rawShaderHolder.hh"

namespace cdxg::RawShaders
{
    ShaderFormater::ShaderFormater()
    {
        if(mbLoaded) { return; }
        //Format the shaders by adding \0 at the end of it
        *(_binary___assets_source_vs_glsl_end - 1) = ""[0];
        *(_binary___assets_source_fs_glsl_end - 1) = ""[0];

        *(_binary___assets_rgb_vs_glsl_end - 1) = ""[0];
        *(_binary___assets_rgb_fs_glsl_end - 1) = ""[0];
        
        *(_binary___assets_rgba_vs_glsl_end - 1) = ""[0];
        *(_binary___assets_rgba_fs_glsl_end - 1) = ""[0];
    }

    bool ShaderFormater::mbLoaded = false;
} // namespace cdxg::RawShaders