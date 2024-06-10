#include "Cube.h"

Cube::Cube(float height, float width, float down,float shift,bool IsCube)
{
    Cube::IsCube = IsCube;
    if (Cube::IsCube)
        GenerateCube(height, width, down, shift);
    else
        GenerateSquare(width, down, shift);
}

void Cube::GenerateCube(float height, float width, float down, float shift)
{
	vertices.push_back(Vertex{ glm::vec3(-width / 2, down, shift+width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 0
	vertices.push_back(Vertex{ glm::vec3(width / 2, down, shift+ width/ 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 1
	vertices.push_back(Vertex{ glm::vec3(width / 2,  height , shift+width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 2
	vertices.push_back(Vertex{ glm::vec3(-width / 2,  height , shift+ width/ 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 3
	vertices.push_back(Vertex{ glm::vec3( -width / 2, down,shift -width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 4)
	vertices.push_back(Vertex{ glm::vec3(+width / 2,down,shift -width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 5)
	vertices.push_back(Vertex{ glm::vec3(+width / 2,  height ,shift -width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 6)
	vertices.push_back(Vertex{ glm::vec3( -width / 2,  height ,shift -width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });  // 7)


	indices = {
         0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    0, 3, 7,
    0, 7, 4,
    // Right face
    1, 5, 6,
    1, 6, 2,
    // Top face
    3, 2, 6,
    3, 6, 7,
    // Bottom face
    0, 1, 5,
    0, 5, 4
	
    };
	
}
void Cube::GenerateSquare(float width, float down, float shift)
{
    vertices.push_back(Vertex{ glm::vec3(-width / 2, down,  width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
    vertices.push_back(Vertex{ glm::vec3(-width / 2, down, -width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) });
    vertices.push_back(Vertex{ glm::vec3(width / 2, down,-width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
    vertices.push_back(Vertex{ glm::vec3(width / 2,down,  width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) });

    indices = 
    {
     0, 1, 2,
    0, 2, 3
    };
}