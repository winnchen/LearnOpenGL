#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <unistd.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../Shader.hpp"
#include "../Camera.hpp"
#include "model.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Camera camera(glm::vec3(0.0f, 0.0f,  3.0f));

float lastX =  SCR_WIDTH / 2.0;
float lastY =  SCR_HEIGHT / 2.0;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


int main()
{
    char * dir = getcwd(NULL, 0);    
    printf("Current dir: %s\n", dir);
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    std::stringstream outlineVertexShader, outlineFragmentShader;
    outlineVertexShader << dir << "/outline_vertex_shader.vs";
    outlineFragmentShader << dir << "/outline_fragment_shader.fs";
    Shader outlineShader(outlineVertexShader.str().c_str(), outlineFragmentShader.str().c_str());


    std::stringstream objVertexShader, objFragmentShader;
    objVertexShader << dir << "/obj_vertex_shader.vs";
    objFragmentShader << dir << "/obj_fragment_shader.fs";
    Shader objShader(objVertexShader.str().c_str(), objFragmentShader.str().c_str());

    std::stringstream objModelPath;
    objModelPath << dir << "/../resources/nanosuit/nanosuit.obj";
    Model objModel(objModelPath.str().c_str());

    
    glm::vec3 lightColor =  glm::vec3(1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        glm::mat4 model = glm::mat4();
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,  0.1f, 100.0f);  //透视

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        objShader.use();
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        objShader.setMat4("model", model);
        objShader.setMat4("view", view);
        objShader.setMat4("projection", projection);

        
        float radius = 6.0f;
        glm::vec3 lightPos = glm::vec3(sin(glfwGetTime()) * radius, 0.0f, cos(glfwGetTime()) * radius);
            
        objShader.setVec3("viewPos", camera.Position);
        objShader.setVec3("light.position", lightPos);
        objShader.setVec3("light.direction", glm::normalize(-lightPos));
        objShader.setFloat("light.cutoff", glm::cos(glm::radians(0.5f)));
        objShader.setFloat("light.outerCutoff", glm::cos(glm::radians(1.5f)));
        objShader.setVec3("light.ambient", lightColor * glm::vec3(1.0f));
        objShader.setVec3("light.diffuse", lightColor * glm::vec3(0.5f));
        objShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objShader.setFloat("light.constant", 1.0f);
        objShader.setFloat("light.linear", 0.09f);
        objShader.setFloat("light.quadratic", 0.032f);
        objModel.draw(objShader);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        outlineShader.use();

        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        outlineShader.setMat4("model", model);
        outlineShader.setMat4("view", view);
        outlineShader.setMat4("projection", projection);

        objModel.draw(outlineShader);
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
