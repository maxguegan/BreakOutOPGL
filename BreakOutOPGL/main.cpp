#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Ressource.h"
#include "Game.h"
unsigned int width = 800;
unsigned int height = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
void processInput(GLFWwindow* window,Game &game);

int main() {

	Game game(width, height);

    //initialisation de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    //création de la fenètre
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //initialisation de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    game.Init();
    game.gameState = ACTIVE;
    glEnable(GL_BLEND);
    unsigned int error = glGetError();
    while (error) {
        std::cout << error << std::endl;
        error = glGetError();
    }
    while (!glfwWindowShouldClose(window))
    {
        float curFrame = (float)glfwGetTime();
        deltaTime = curFrame - lastFrame;
        lastFrame = curFrame;
        glClearColor(0.25f, 0.25f, 0.5f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window, game);
        game.Update(deltaTime);

        game.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
        error = glGetError();
        while (error) {
            std::cout << error << std::endl;
            error = glGetError();
        }
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Game& game) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        game.keys[GLFW_KEY_A] = true;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
        game.keys[GLFW_KEY_A] = false;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        game.keys[GLFW_KEY_D] = true;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
        game.keys[GLFW_KEY_D] = false;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        game.keys[GLFW_KEY_SPACE] = true;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
        game.keys[GLFW_KEY_SPACE] = false;

    game.ProcessInput(deltaTime);
}