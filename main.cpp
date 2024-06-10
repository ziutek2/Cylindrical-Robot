
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"



#include"Mesh.h"
#include"Object.h"
#include"Box.h"
const unsigned int width = 1024;
const unsigned int height = 768;
const float FloorZ = -1.0f;
const float FloorWidth = 10.0f;
const int CylinderSides = 36;
const float BaseCylinderRadius = 0.5f;
const float ArmRadius = 0.25f;
const float MidCylinderRadius = 0.25f;
const float BoxWidth = 0.5f;
const float BoxHeight = 0.5f;
const float BoxDepth = 0.5f;
const float Range = 1.0f;



int main()
{  
	float BaseCylinderDown = FloorZ;
	float BaseCylinderHeight = 0.3f;
	float BaseCylinderUp = BaseCylinderDown + BaseCylinderHeight;
	float MidCylinderDown = BaseCylinderUp;
	float MidCylinderHeight = 1.0f;
	float MidCylinderUp = MidCylinderDown + MidCylinderHeight;
	float CubeDown = MidCylinderUp;
	float CubeHeight = 0.5f;
	float CubeUp = CubeDown + CubeHeight;
	float CubeWidth = 0.5f;
	float ArmDown = CubeWidth/2;
	float ArmLenght = 2.0f;
	float ArmHeight = MidCylinderUp + CubeWidth / 2;
	float ArmUp = ArmDown + ArmLenght;
	float EffectorUp = CubeDown + CubeWidth;
	float EffectorDown = CubeDown + CubeWidth / 2;
	float EffectorWidth = CubeWidth;
	bool grab = false;
	
	glm::vec3 BoxPosition = { 2.0f,FloorZ+BoxHeight,2.0f };
	glm::vec3 EffectorPosition;


	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Cylindrical Robot", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	
	Texture FLoorTextures[]
	{
		Texture("metal.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)
	};
	Texture CylinderTextures[]
	{
		Texture("white.png","diffuse",0,GL_RGBA,GL_UNSIGNED_BYTE)
	};
	Texture BoxTextures[]
	{
		Texture("MetalBox.jpg","diffuse",0,GL_RGB,GL_UNSIGNED_BYTE)
	};

	
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Store mesh data in vectors for the mesh
	Object BaseCylinder(CylinderSides, BaseCylinderUp, BaseCylinderDown, 0, BaseCylinderRadius, 3, 0);
	Object MidCylinder(CylinderSides, MidCylinderUp, MidCylinderDown, 0, MidCylinderRadius, 3, 0);
	Object Arm(CylinderSides, ArmHeight, ArmDown, ArmUp, ArmRadius, 4,0);
	Object Cube(6, CubeUp, CubeDown, 0, 0, 2, CubeWidth);
	Object Effector(6,EffectorUp,EffectorDown,ArmUp,0,5, EffectorWidth);
	Object Floor(6,FloorZ, FloorZ, 0, 0, 1, FloorWidth);

	Box Box1(BoxPosition, BoxWidth, BoxHeight, BoxDepth);
	
//	Object Box(6,2.0f,FloorZ,)
	std::vector<Object*> ChangedObjects = {&MidCylinder, &Arm, &Cube, &Effector};


	std::vector <Texture> FloorTex(FLoorTextures, FLoorTextures + sizeof(FLoorTextures) / sizeof(Texture));
	std::vector <Texture> CylinderTex(CylinderTextures, CylinderTextures + sizeof(CylinderTextures) / sizeof(Texture));
	std::vector <Texture> BoxTex(BoxTextures, BoxTextures + sizeof(BoxTextures) / sizeof(Texture));
	// Create floor mesh

	Mesh MidCylinderMesh(MidCylinder.getVertices(), MidCylinder.getIndices(), CylinderTex);
	Mesh BaseCylinderMesh(BaseCylinder.getVertices(), BaseCylinder.getIndices(), CylinderTex);
	Mesh CubeMesh(Cube.getVertices(), Cube.getIndices(), CylinderTex);
	Mesh ArmMesh(Arm.getVertices(), Arm.getIndices(), CylinderTex);
	Mesh EffectorMesh(Effector.getVertices(), Effector.getIndices(), CylinderTex);
	Mesh FloorMesh(Floor.getVertices(), Floor.getIndices(), FloorTex);
	Mesh BoxMesh(Box1.getVertices(), Box1.getIndices(),BoxTex);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	


	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);






	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 3.0f, -10.0f), glm::vec3(0.0f));
	float angle = 0.0f;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	
		
		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		// Draws different meshes
	//	floor.Draw(shaderProgram, camera);
		
		
		
		ImGui::Begin("GUI");
		ImGui::SliderFloat("Linear Change Z axis", &MidCylinderHeight, 0.0f, 2.0f);
		ImGui::SliderFloat("Linera Change X axis", &ArmLenght, 0.5f, 3.5f);
		ImGui::SliderFloat("Rotation Angle (degrees)", &angle, 0.0f, 360.0f); // Dodanie kontrolki do zmiany k¹ta rotacji
		ImGui::Checkbox("Grab Object", &grab);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	


		for (int i = 0; i < ChangedObjects.size(); i++)
		{
			
			ChangedObjects[i]->UpadateObjectParameters(MidCylinderHeight,ArmLenght);
		}
		
		EffectorPosition = glm::rotate(Effector.vertices[1].position,glm::radians(angle),glm::vec3(0.0f,1.0f,0.0f));
		Box1.Update(EffectorPosition, Range,grab);
		BoxMesh.UpdateObject(Box1.getVertices());
		MidCylinderMesh.UpdateObject(MidCylinder.getVertices());
		ArmMesh.UpdateObject(Arm.getVertices());
		CubeMesh.UpdateObject(Cube.getVertices());
		EffectorMesh.UpdateObject(Effector.getVertices());
	


		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		
		
		MidCylinderMesh.Draw(shaderProgram, camera);
		ArmMesh.Draw(shaderProgram, camera);
		CubeMesh.Draw(shaderProgram, camera);
		EffectorMesh.Draw(shaderProgram, camera);
		



		// Drawing objects without rotation
		
		glm::mat4 identityMatrix = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(identityMatrix));
		FloorMesh.Draw(shaderProgram, camera);
		BaseCylinderMesh.Draw(shaderProgram, camera);
		BoxMesh.Draw(shaderProgram, camera);


		// Swap the back buffer with the front buffera
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	FLoorTextures->Delete();
	CylinderTextures->Delete();
	BoxTextures->Delete();
	

	// Delete all the objects we've created
	shaderProgram.Delete();
	//lightShader.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	
	return 0;
}
