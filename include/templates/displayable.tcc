#ifndef CDXG_DISPLAYABLE
#error displayable.tcc must only be included by displayable.hh
#endif

#ifndef CDXG_DISPLAYABLE_TCC
#define CDXG_DISPLAYABLE_TCC

template<class Vtype>
inline void testVertexType()
{
    if(std::is_base_of<cdxg::Vertex, Vtype>().value) { return; }
    throw std::invalid_argument("Tried to initialize cdxg::Displayable<Vtype> class\nwith Vtype not a vertex or vertex derived Class.\n");
}

namespace cdxg
{
    template<class Vtype>
    Displayable<Vtype>::Displayable()
    {
        testVertexType<Vtype>();

        muivVerticesIndices = std::vector<unsigned int>({0, 0, 0});
        meDrawType = mGlDrawType::DYNAMIC;
        mvVertices = std::vector<Vtype>({Vtype()});
        mpShader = &defaultShader;
        mpShader->Load();
        muiVao = 0;
        muiVbo = 0;
        muiIbo = 0;
        mbVerticesIndicesModified = false;
        mbVerticesModified = false;
        mbLoaded = false;
    };

    template<class Vtype>
    Displayable<Vtype>::~Displayable()
    {};

    template<class Vtype>
    void Displayable<Vtype>::draw()
    {
        mpShader->Use();

        glBindVertexArray(muiVao);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    };

    template<class Vtype>
    void Displayable<Vtype>::move(float x, float y)
    {
        for(int i = 0; i < mvVertices.size(); ++i){
            mvVertices[i].move(x, y);
        }
        mbVerticesModified = true;
        refreshVram();
    };

    template<class Vtype>
    void Displayable<Vtype>::load()
    {
        glGenVertexArrays(1, &muiVao);
        glBindVertexArray(muiVao);
        glGenBuffers(1, &muiVbo);
        glBindBuffer(GL_ARRAY_BUFFER, muiVbo);
        glGenBuffers(1, &muiIbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, muiIbo);

        refreshVram(true, false, -1);

        initializeVertexAttribArrays<Vtype>();

        glBindVertexArray(0);
        mbLoaded = true;
    };

    template<class Vtype>
    void Displayable<Vtype>::setVertices(std::vector<Vtype> vertices, bool bRefreshVram)
    {
        if(mvVertices == vertices) { return; }
        mvVertices = vertices;
        mbVerticesModified = true;
        if(bRefreshVram) { refreshVram(); }
    };

    template<class Vtype>
    void Displayable<Vtype>::setVerticesIndices(std::vector<unsigned int> verticesIndices, bool bRefreshVram)
    {
        if(muivVerticesIndices == verticesIndices) { return; }
        muivVerticesIndices = verticesIndices;
        mbVerticesIndicesModified = true;
        if(bRefreshVram) { refreshVram(); }
    };

    template<class Vtype>
    void Displayable<Vtype>::setShader(Shader *shader)
    {
        mpShader = shader;
        mpShader->Load();
    };

    template<class Vtype>
    void Displayable<Vtype>::unload()
    {
        if(!mbLoaded) { return; }
        glDeleteVertexArrays(1, &muiVao);
        glDeleteBuffers(1, &muiVbo);
        glDeleteBuffers(1, &muiIbo);
    };

    template<class Vtype>
    void Displayable<Vtype>::refreshVram(bool forceRefresh, bool bindBuffers, int vertexArrayObjectCallbackID)
    {
        if(!forceRefresh && !mbVerticesIndicesModified && !mbVerticesModified) { return; }
        if(bindBuffers) { glBindVertexArray(muiVao); }
        if(forceRefresh || mbVerticesModified) {
            if(bindBuffers) { glBindBuffer(GL_ARRAY_BUFFER, muiVbo); }
            glBufferData(GL_ARRAY_BUFFER, mvVertices.size()*sizeof(mvVertices[0]), &mvVertices[0], std::get<0>(mateGlDrawType[meDrawType]));
        }
        if(forceRefresh || mbVerticesIndicesModified){
            if(bindBuffers) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, muiIbo); }
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, muivVerticesIndices.size()*sizeof(muivVerticesIndices[0]), &muivVerticesIndices[0], std::get<1>(mateGlDrawType[meDrawType]));
        }
        if(vertexArrayObjectCallbackID >= 0 && bindBuffers){
            glBindVertexArray(vertexArrayObjectCallbackID);
        }
    };

    template<class Vtype>
    const std::tuple<GLenum, GLenum> Displayable<Vtype>::mateGlDrawType[] =
    {
        std::tuple<GLenum, GLenum>(GL_DYNAMIC_DRAW, GL_DYNAMIC_DRAW), //DYNAMIC (DYNAMIC_DYNAMIC)
        std::tuple<GLenum, GLenum>(GL_STATIC_DRAW, GL_STATIC_DRAW), //STATIC (STATIC_STATIC)
        std::tuple<GLenum, GLenum>(GL_DYNAMIC_DRAW, GL_STATIC_DRAW), //DYNAMIC_STATIC
        std::tuple<GLenum, GLenum>(GL_STATIC_DRAW, GL_DYNAMIC_DRAW), //STATIC_DYNAMIC
        std::tuple<GLenum, GLenum>(GL_STREAM_DRAW, GL_STREAM_DRAW), //STREAM
    };
} // namespace cdxg


#endif