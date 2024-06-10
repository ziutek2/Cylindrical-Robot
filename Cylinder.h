#include <vector>
#include "Mesh.h"

class Cylinder {
public:
    Cylinder(int sides, float height, float radius, float down,bool vertical,float ArmHeight);
    bool vertical;
     std::vector<Vertex>& getVertices()
     { return vertices; }
     std::vector<GLuint>& getIndices() 
     { return indices; }
    const float PI = 3.14159265358979323846;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    void UpdateVertices(int sides, float height, float radius, float down);
  


private:
    
    void generateVerticalCylinder(int sides, float height, float radius,float down);
    void generateHorizontalCylinder(int  sides, float lenght, float radius, float down,float height );
};