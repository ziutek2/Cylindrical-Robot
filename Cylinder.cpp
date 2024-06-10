
#include "Cylinder.h"
#include <cmath>

Cylinder::Cylinder(int sides, float height, float radius, float down, bool vertical, float ArmHeight) {
    Cylinder::vertical = vertical;
    if (Cylinder::vertical)
        generateVerticalCylinder(sides, height, radius, down);
    else
        generateHorizontalCylinder(sides, height, radius, down,ArmHeight);

}
void Cylinder::generateVerticalCylinder(int sides, float height, float radius,float down) {
    const float angleStep = 2.0f * PI / sides;

    // Generate vertices
    for (int i = 0; i <= sides; ++i) {
        const float angle = i * angleStep;
        const float x = radius * cos(angle);
        const float z = radius * sin(angle);

        // Bottom circle
        vertices.push_back(Vertex{ glm::vec3(x, down, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(static_cast<float>(i) / sides, 0.0f) });

        // Top circle
        vertices.push_back(Vertex{ glm::vec3(x, height, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(static_cast<float>(i) / sides, 1.0f) });
    }

    // Generate indices
    for (int i = 0; i < sides; ++i) 
    {
        const int bottomLeft = i * 2;
        const int topLeft = bottomLeft + 1;
        const int bottomRight = bottomLeft + 2;
        const int topRight = topLeft + 2;

        // Side triangles
        indices.push_back(bottomLeft);
        indices.push_back(topLeft);
        indices.push_back(bottomRight);

        indices.push_back(topLeft);
        indices.push_back(topRight);
        indices.push_back(bottomRight);

        for (int i = 0; i < sides; ++i) 
        {
            // Bottom circle
            indices.push_back(0);                        // Center of bottom circle
            indices.push_back(i * 2);                    // Previous vertex of bottom circle
            indices.push_back((i + 1) * 2);              // Current vertex of bottom circle

            // Top circle
            indices.push_back(1);                        // Center of top circle
            indices.push_back((i + 1) * 2 + 1);          // Current vertex of top circle
            indices.push_back(i * 2 + 1);                // Previous vertex of top circle
        }

        // Connect the last and first vertices to close the circles
        // Bottom circle
        indices.push_back(0);
        indices.push_back((sides - 1) * 2);
        indices.push_back(2);

        // Top circle
        indices.push_back(1);
        indices.push_back((sides - 1) * 2 + 1);
        indices.push_back(3);


    }
   
}
void Cylinder::generateHorizontalCylinder(int sides, float lenght, float radius, float down, float height) 
{
    const float angleStep = 2.0f * PI / sides;

    // Generowanie wierzcho�k�w
    for (int i = 0; i <= sides; ++i) {

        const float angle = i * angleStep;
        const float x = radius * cos(angle);
        const float y = radius * sin(angle);

        // Kr�g dolny
        vertices.push_back(Vertex{ glm::vec3(x, height+y, down), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(static_cast<float>(i) / sides, 0.0f) });

        // Kr�g g�rny
        vertices.push_back(Vertex{ glm::vec3(x, height+y, lenght), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(static_cast<float>(i) / sides, 1.0f) });
    }

    // Generowanie indeks�w
    for (int i = 0; i < sides; ++i) {
        const int bottomLeft = i * 2;
        const int topLeft = bottomLeft + 1;
        const int bottomRight = bottomLeft + 2;
        const int topRight = topLeft + 2;

        // Tr�jk�ty boczne
        indices.push_back(bottomLeft);
        indices.push_back(bottomRight);
        indices.push_back(topLeft);

        indices.push_back(topLeft);
        indices.push_back(bottomRight);
        indices.push_back(topRight);
    }

    for (int i = 0; i < sides; ++i) {
        // Kr�g dolny
        indices.push_back(0);                         // �rodek kr�gu dolnego
        indices.push_back(i * 2);                     // Poprzedni wierzcho�ek kr�gu dolnego
        indices.push_back((i + 1) * 2);               // Aktualny wierzcho�ek kr�gu dolnego

        // Kr�g g�rny
        indices.push_back(1);                         // �rodek kr�gu g�rnego
        indices.push_back((i + 1) * 2 + 1);           // Aktualny wierzcho�ek kr�gu g�rnego
        indices.push_back(i * 2 + 1);                 // Poprzedni wierzcho�ek kr�gu g�rnego
    }

    // Po��czenie ostatnich i pierwszych wierzcho�k�w, aby zamkn�� kr�gi
    // Kr�g dolny
    indices.push_back(0);
    indices.push_back((sides - 1) * 2);
    indices.push_back(2);

    // Kr�g g�rny
    indices.push_back(1);
    indices.push_back((sides - 1) * 2 + 1);
    indices.push_back(3);
}
void Cylinder::UpdateVertices(int sides, float height, float radius, float down)
{
    const float angleStep = 2.0f * PI / sides;
   std::vector<Vertex> newVertices;

   for (int i = 0; i <= sides; ++i) {
       const float angle = i * angleStep;
       const float x = radius * cos(angle);
       const float z = radius * sin(angle);

       // Bottom circle
       newVertices.push_back(Vertex{ glm::vec3(x, down, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(static_cast<float>(i) / sides, 0.0f) });

       // Top circle
       newVertices.push_back(Vertex{ glm::vec3(x, height, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(static_cast<float>(i) / sides, 1.0f) });
   }
   vertices = newVertices;

}