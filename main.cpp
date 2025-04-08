#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version to 2.1 (for compatibility with immediate mode)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Create a windowed mode window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Green Line with GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Set background color (black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set line color to green
        glColor3f(0.0f, 1.0f, 0.0f);

        // Draw a line using immediate mode
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.8f, -0.8f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.8f, -0.8f);
        glVertex2f(0.65f, -0.9f);
        glVertex2f(0.36f, -0.6f);
        glVertex2f(0.0f, -0.8f);
        glVertex2f(-0.36f, -0.6f);
        glVertex2f(-0.65f, -0.9f);
        glVertex2f(-0.8f, -0.8f);
        glEnd();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
