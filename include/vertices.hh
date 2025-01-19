#ifndef CDXG_VERTICES
#define CDXG_VERTICES

//#warning vertices called

#include <type_traits>
#include <stdexcept>


namespace cdxg
{
    struct Vertex {
        Vertex();
        Vertex(const Vertex &v);
        Vertex(float _x, float _y);
        void move(float _x, float _y);
        float x;
        float y;
        friend bool operator==(const Vertex &v1, const Vertex &v2);
    };

    struct VertexRGB : public Vertex {
        VertexRGB();
        VertexRGB(const VertexRGB &v);
        VertexRGB(float _x, float _y, float _r, float _g, float _b);
        float r;
        float g;
        float b;
        friend std::ostream& operator<<(std::ostream &os, VertexRGB &v);
        friend bool operator==(const VertexRGB &v1, const VertexRGB &v2);
    };
    struct VertexRGBA : public VertexRGB {
        VertexRGBA();
        VertexRGBA(const VertexRGBA &v);
        VertexRGBA(float _x, float _y, float _r, float _g, float _b, float _a);
        float a;
        friend bool operator==(const VertexRGBA &v1, const VertexRGBA &v2);
    };

    template<typename T> void initializeVertexAttribArrays(){
        throw std::invalid_argument("Tried to enableVertexAttribArray of an unhandled class");
    }

    bool operator==(const Vertex &v1, const Vertex &v2);
    bool operator==(const VertexRGB &v1, const VertexRGB &v2);
    bool operator==(const VertexRGBA &v1, const VertexRGBA &v2);

    std::ostream& operator<<(std::ostream &os, VertexRGB &v);

} // namespace cdxg


#endif