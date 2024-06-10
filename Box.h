#include <vector>
#include "Mesh.h"

class Box
{
	
	public:
		Box(const glm::vec3& position, float width, float height, float depth);
		
		std::vector<Vertex>& getVertices()
		{
			return vertices;
		}
		std::vector<GLuint>& getIndices()
		{
			return indices;
		}
		void Update(glm::vec3& gripperPosition, float thresholdDistance, bool grab);

	private:
		glm::vec3 position;
		float width;
		float height;
		float depth;
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		void GenerateVertices();
		bool IsGripperClose(glm::vec3& gripperPosition, float thresholdDistance);
		void FollowGripper(glm::vec3& gripperPosition);
		void Gravity();


};