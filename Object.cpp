#include "Object.h"
#include "cmath"
Object::Object(int sides, float height, float down, float shift, float radius, int ObjectType,float width)
{
    Object::Type = ObjectType;
    Object::Height = height;
    Object::Down = down;
    Object::Shift = shift;
    Object::Radius = radius;
    Object:Width = width;
    Object::Sides = sides;
	GenerateObject();

}

void Object::GenerateObject()
{
    if (Object::Type == 1)
    {
        vertices.push_back(Vertex{ glm::vec3(-Width / 2, Down,  Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
        vertices.push_back(Vertex{ glm::vec3(-Width / 2, Down, -Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) });
        vertices.push_back(Vertex{ glm::vec3(Width / 2, Down,-Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
        vertices.push_back(Vertex{ glm::vec3(Width / 2,Down,  Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) });

        indices =
        {
         0, 1, 2,
        0, 2, 3
        };
    }
    else if (Object::Type == 2 || Object::Type == 5)
    {
        vertices.push_back(Vertex{ glm::vec3(-Width / 2, Down, Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 0
        vertices.push_back(Vertex{ glm::vec3(Width / 2, Down, Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 1
        vertices.push_back(Vertex{ glm::vec3(Width / 2,  Height , Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 2
        vertices.push_back(Vertex{ glm::vec3(-Width / 2,  Height , Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 3
        vertices.push_back(Vertex{ glm::vec3(-Width / 2, Down,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 4)
        vertices.push_back(Vertex{ glm::vec3(+Width / 2,Down,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 5)
        vertices.push_back(Vertex{ glm::vec3(+Width / 2,  Height ,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 6)
        vertices.push_back(Vertex{ glm::vec3(-Width / 2,  Height ,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });  // 7)

        
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
    else if (Object::Type == 3)
    {
        const float angleStep = 2.0f * PI / Sides;

        // Generate vertices
        for (int i = 0; i <= Sides; ++i)
        {
            const float angle = i * angleStep;
            const float x = Radius * cos(angle);
            const float z = Radius * sin(angle);

            // Bottom circle
            vertices.push_back(Vertex{ glm::vec3(x, Down, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(static_cast<float>(i) / Sides, 0.0f) });

            // Top circle
            vertices.push_back(Vertex{ glm::vec3(x, Height, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(static_cast<float>(i) / Sides, 1.0f) });
        }

        // Generate indices
        for (int i = 0; i < Sides; ++i)
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

            for (int i = 0; i < Sides; ++i)
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
            indices.push_back((Sides - 1) * 2);
            indices.push_back(2);

            // Top circle
            indices.push_back(1);
            indices.push_back((Sides - 1) * 2 + 1);
            indices.push_back(3);


        }
    }
    else if (Object::Type == 4)
    {
        const float angleStep = 2.0f * PI / Sides;

        // Generowanie wierzcho³ków
        for (int i = 0; i <= Sides; ++i) {

            const float angle = i * angleStep;
            const float x = Radius * cos(angle);
            const float y = Radius * sin(angle);

            // Kr¹g dolny
            vertices.push_back(Vertex{ glm::vec3(x, Height + y, Down), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(static_cast<float>(i) / Sides, 0.0f) });

            // Kr¹g górny
            vertices.push_back(Vertex{ glm::vec3(x, Height + y, Shift), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(static_cast<float>(i) / Sides, 1.0f) });
        }

        // Generowanie indeksów
        for (int i = 0; i < Sides; ++i) {
            const int bottomLeft = i * 2;
            const int topLeft = bottomLeft + 1;
            const int bottomRight = bottomLeft + 2;
            const int topRight = topLeft + 2;

            // Trójk¹ty boczne
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
            indices.push_back(topLeft);

            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);
        }

        for (int i = 0; i < Sides; ++i) {
            // Kr¹g dolny
            indices.push_back(0);                         // Œrodek krêgu dolnego
            indices.push_back(i * 2);                     // Poprzedni wierzcho³ek krêgu dolnego
            indices.push_back((i + 1) * 2);               // Aktualny wierzcho³ek krêgu dolnego

            // Kr¹g górny
            indices.push_back(1);                         // Œrodek krêgu górnego
            indices.push_back((i + 1) * 2 + 1);           // Aktualny wierzcho³ek krêgu górnego
            indices.push_back(i * 2 + 1);                 // Poprzedni wierzcho³ek krêgu górnego
        }

        // Po³¹czenie ostatnich i pierwszych wierzcho³ków, aby zamkn¹æ krêgi
        // Kr¹g dolny
        indices.push_back(0);
        indices.push_back((Sides - 1) * 2);
        indices.push_back(2);

        // Kr¹g górny
        indices.push_back(1);
        indices.push_back((Sides - 1) * 2 + 1);
        indices.push_back(3);

    }





}
void Object::UpadateObjectParameters(float DiffRobotHeight, float DiffArmLenght)
{
   
    if (Object::Type == 2)
        {
            {
                Height = DiffRobotHeight + Width;
                Shift = 0;
                Down = DiffRobotHeight;
            }
        }
        if (Object::Type == 3)
        {
            Height = DiffRobotHeight;
            Shift = 0;
        }
        if (Object::Type == 4)
        {
            Height = DiffRobotHeight + Down;
            Shift = DiffArmLenght;
        }
        if (Object::Type == 5)
        {
            Height = DiffRobotHeight + 0.25 * Width;
            Shift = DiffArmLenght + Width / 2;
            Down = DiffRobotHeight + 0.75 * Width;

        }


        Object::UpdateObjectVertices();
    
}


   void Object::UpdateObjectVertices()
    {

        std::vector<Vertex> newVertices;
        if (Object::Type == 3)
        {
            const float angleStep = 2.0f * PI / Sides;
            for (int i = 0; i <= Sides; ++i) {
                const float angle = i * angleStep;
                const float x = Radius * cos(angle);
                const float z = Radius * sin(angle);

                // Bottom circle
                newVertices.push_back(Vertex{ glm::vec3(x, Down, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(static_cast<float>(i) / Sides, 0.0f) });

                // Top circle

                newVertices.push_back(Vertex{ glm::vec3(x, Height, z), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(static_cast<float>(i) / Sides, 1.0f) });
            }
            vertices = newVertices;
        }
        if (Object::Type == 1)
        {
            newVertices.push_back(Vertex{ glm::vec3(-Width / 2, Down,  Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
            newVertices.push_back(Vertex{ glm::vec3(-Width / 2, Down, -Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) });
            newVertices.push_back(Vertex{ glm::vec3(Width / 2, Down,-Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
            newVertices.push_back(Vertex{ glm::vec3(Width / 2,Down,  Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) });

            vertices = newVertices;
        }
        if (Object::Type == 2 || Object::Type==5)
        {
            newVertices.push_back(Vertex{ glm::vec3(-Width / 2, Down, Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 0
            newVertices.push_back(Vertex{ glm::vec3(Width / 2, Down, Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 1
            newVertices.push_back(Vertex{ glm::vec3(Width / 2,  Height , Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 2
            newVertices.push_back(Vertex{ glm::vec3(-Width / 2,  Height , Shift + Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 3
            newVertices.push_back(Vertex{ glm::vec3(-Width / 2, Down,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 4)
            newVertices.push_back(Vertex{ glm::vec3(+Width / 2,Down,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 5)
            newVertices.push_back(Vertex{ glm::vec3(+Width / 2,  Height ,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }); // 6)
            newVertices.push_back(Vertex{ glm::vec3(-Width / 2,  Height ,Shift - Width / 2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });  // 7)
                
            vertices = newVertices;
        }
        if (Object::Type == 4)
        {
            const float angleStep = 2.0f * PI / Sides;

            // Generowanie wierzcho³ków
            for (int i = 0; i <= Sides; ++i) {

                const float angle = i * angleStep;
                const float x = Radius * cos(angle);
                const float y = Radius * sin(angle);

                // Kr¹g dolny
                newVertices.push_back(Vertex{ glm::vec3(x, Height + y, Down), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(static_cast<float>(i) / Sides, 0.0f) });

                // Kr¹g górny
                newVertices.push_back(Vertex{ glm::vec3(x, Height + y, Shift), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(static_cast<float>(i) / Sides, 1.0f) });
            }
            vertices = newVertices;

        }

    }




