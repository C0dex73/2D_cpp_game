#include "vertices.hh"
#include <type_traits>
#include <glad/glad.h>

#include <iomanip>

namespace cdxg
{
    Vertex::Vertex(){
        x = 0.0f;
        y = 0.0f;
    }

    Vertex::Vertex(const Vertex &v){
        x = v.x;
        y = v.y;
    }

    Vertex::Vertex(float _x, float _y){
        x = _x;
        y = _y;
    }

    void Vertex::move(float _x, float _y){
        x += _x;
        y += _y;
    }

    VertexRGB::VertexRGB()
    : Vertex(){
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    VertexRGB::VertexRGB(const VertexRGB &v)
    : Vertex(v.x, v.y)
    {
        r = v.r;
        g = v.g;
        b = v.b;
    }

    VertexRGB::VertexRGB(float _x, float _y, float _r, float _g, float _b)
    : Vertex(_x, _y)
    {
        r = _r;
        g = _g;
        b = _b;
    }

    VertexRGBA::VertexRGBA()
    : VertexRGB()
    {
        a = 0.0f;
    }

    VertexRGBA::VertexRGBA(const VertexRGBA &v)
    : VertexRGB(v.x, v.y, v.r, v.r, v.b)
    {
        a = v.a;
    }

    VertexRGBA::VertexRGBA(float _x, float _y, float _r, float _g, float _b, float _a)
    : VertexRGB(_x, _y, _r, _g, _b)
    {
        a = _a;
    }

    template<> void initializeVertexAttribArrays<Vertex>(){
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
        glEnableVertexAttribArray(0);
    }

    template<> void initializeVertexAttribArrays<VertexRGB>(){
        initializeVertexAttribArrays<Vertex>();
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    template<> void initializeVertexAttribArrays<VertexRGBA>(){
        initializeVertexAttribArrays<Vertex>();
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexRGBA)-sizeof(Vertex), (void*)offsetof(VertexRGBA, r));
    }

    bool operator==(const Vertex &v1, const Vertex &v2)
    {
        return v1.x == v2.x
            && v1.y == v2.y;
    }

    bool operator==(const VertexRGB &v1, const VertexRGB &v2)
    {
        return v1.x == v2.x
            && v1.y == v2.y
            && v1.r == v2.r
            && v1.g == v2.g
            && v1.b == v2.b;
    }

    bool operator==(const VertexRGBA &v1, const VertexRGBA &v2)
    {
        return v1.x == v2.x
            && v1.y == v2.y
            && v1.r == v2.r
            && v1.g == v2.g
            && v1.b == v2.b
            && v1.a == v2.a;
    }

    std::ostream& operator<<(std::ostream &os, VertexRGB &v)
    {
        return os << "VertexRGB : {x=" << (float)v.x << "; y=" << (float)v.y << "; r=" << (float)v.r << "; g=" << (float)v.g << "; b=" << (float)v.b << ";}" << std::endl;
    }

} // namespace cdxg
