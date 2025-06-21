#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

//vertex shader source code (stored in RAM as a string)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"}\0";

//Fragment shader source code (stored in RAM as a string)
const char* fragmentShaderSource = "version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor =  vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	//Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Rectangle", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Load openGL functions with GLAD. There are several functions which are not present in library of modern openGL
	//So instead of loading each function manually one by one, we use GLAD to load function pointers of all the functions at once
	// and use them anywhere we want. This saves time and effort.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Rectangle vertices(2 triangles) (stored in RAM, and meant to transfer to GPU's VRAM(VBO)
	float vertices[] = {
		0.5f, 0.5f, 0.0f,	//index no. 0, top right
		0.5f, -0.5f, 0.0f,	//index no. 1, bottom right
		-0.5f, -0.5f, 0.0f,	//index no. 2, bottom left
		-0.5f, 0.5f, 0.0f	//index no. 3, top left
	};

	//Indices to form two triangles (stored in RAM, and meant to transfer to GPU's VRAM(EBO)
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned VAO, VBO, EBO;

	//Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Generate and bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//GL_ARRAY_BUFFER stores vertex attributes(positions, colors, etc)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//This function transfers vertex data from RAM to GPU's VRAM(VBO)

	//Generate and bind EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	//GL_ELEMENT_ARRAY_BUFFER stores indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//This function transfers data from RAM to GPU's VRAM(EBO)

	//set vertex attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//This function tells the openGL to how to interpret the vertex data. It tells the openGL- "Hey, the vertex data in the buffer is made up of 3 float per vertex (like x, y & z), stored one after another with no gaps, and it starts at the beginning of the buffer."
	glEnableVertexAttribArray(0); 

	//Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);	//This function gives an integer id to our vertexShader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);	//This function transfers the vertex shader source code from the RAM to the GPU's VRAM
	glCompileShader(vertexShader);

	//Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	//This function gives an id to to the fragmentShader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);	//This function transfers the fragment shader source code from the RAM to the GPU's VRAM
	glCompileShader(fragmentShader);

	//Shader program
	unsigned int shaderProgram = glCreateProgram();	//This function generates an id for shaderProgram object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Delete shaders(no longer needed)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		//Input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		//Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw the rectangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}