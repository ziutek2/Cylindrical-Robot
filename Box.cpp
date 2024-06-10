#include "Box.h"

Box::Box(const glm::vec3& position, float width, float height, float depth)
{
    Box::position = position;
    Box::width = width;
    Box::height = height;
    Box::depth = depth;

    Box::GenerateVertices();
}

    

void Box::GenerateVertices() 
{
    vertices.clear();
    indices.clear();

    vertices.push_back(Vertex{position + glm::vec3(-width / 2, -height, depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 0
    vertices.push_back(Vertex{position +glm::vec3(width / 2, -height, depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 1
    vertices.push_back(Vertex{position+ glm::vec3(width / 2,  height , depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 2
    vertices.push_back(Vertex{position+ glm::vec3(-width / 2,  height , depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 3
    vertices.push_back(Vertex{position+ glm::vec3(-width / 2, -height,-depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 4)
    vertices.push_back(Vertex{position+ glm::vec3(+width / 2,-height,-depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 5)
    vertices.push_back(Vertex{position+ glm::vec3(+width / 2,  height ,-depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 6)
    vertices.push_back(Vertex{position+ glm::vec3(-width / 2,  height ,-depth / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });  // 7)


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
bool Box::IsGripperClose(glm::vec3& gripperPosition, float thresholdDistance) 
{
    float distance = glm::distance(position, gripperPosition);
    return distance < thresholdDistance;

}
void Box::FollowGripper(glm::vec3& gripperPosition)
{
    position = gripperPosition;
    GenerateVertices();
}
void Box::Update(glm::vec3& gripperPosition, float thresholdDistance, bool Grab)
{
    if (Grab)
    {
        if (IsGripperClose(gripperPosition, thresholdDistance))
        {
            FollowGripper(gripperPosition);
        }
    }
    else
    {
        Gravity();
    }

}
void Box::Gravity()
{
   while(position.y > -0.5f)
    {
        position.y -= 0.001f;
        GenerateVertices();
    }

}


// Aktualizacja wierzcho³ków zgodnie z now¹ pozycj¹