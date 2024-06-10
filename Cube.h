#include <vector>
#include "Mesh.h"

class Cube {

public:
    bool IsCube;
    Cube(float height, float width,float down,float shift,bool IsCube);
    std::vector<Vertex>& getVertices()
    {
        return vertices;
    }
    std::vector<GLuint>& getIndices()
    {
        return indices;
    }
    
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    void GenerateCube(float height, float width,float down,float shift);
    void GenerateSquare(float width, float down, float shift);


};