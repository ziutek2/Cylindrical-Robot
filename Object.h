#include <vector>
#include "Mesh.h"


class Object
{
public:
	Object(int sides, float height,float down, float shift, float radius, int ObjectType,float width);
	std::vector<Vertex>& getVertices()
	{
		return vertices;
	}
	std::vector<GLuint>& getIndices()
	{
		return indices;
	}
	int Type;
	int Sides;
	float Height;
	float Down;
	float Shift;
	float Radius;
	float Width;

	const float PI = 3.14159265358979323846;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	void UpadateObjectParameters(float DiffRobotHeight,float DiffArmLenght);
	void UpdateObjectVertices();

private:
	void GenerateObject();





};
