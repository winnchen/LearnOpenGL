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
    
    glEnable(GL_DEPTH_TEST);


    std::stringstream objVertexShader, objFragmentShader;
    objVertexShader << dir << "/" << "obj_vertex_shader.vs";
    objFragmentShader << dir << "/" << "obj_fragment_shader.fs";
    Shader objShader(objVertexShader.str().c_str(), objFragmentShader.str().c_str());

    std::stringstream lampVertexShader, lampFragmentShader;
    lampVertexShader << dir << "/" << "lamp_vertex_shader.vs";
    lampFragmentShader << dir << "/" << "lamp_fragment_shader.fs";
    Shader lampShader(lampVertexShader.str().c_str(), lampFragmentShader.str().c_str());
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( -4.0f,  1.0f,  0.0f), 
        glm::vec3( -2.0f,  1.0f,  0.0f), 
        glm::vec3(  0.0f,  1.0f,  0.0f),   
        glm::vec3(  2.0f,  1.0f,  0.0f), 
        glm::vec3(  4.0f,  1.0f,  0.0f), 
        glm::vec3( -4.0f,  -1.0f,  0.0f), 
        glm::vec3( -2.0f,  -1.0f,  0.0f), 
        glm::vec3(  0.0f,  -1.0f,  0.0f), 
        glm::vec3(  2.0f,  -1.0f,  0.0f), 
        glm::vec3(  4.0f,  -1.0f,  0.0f)
    };

    glm::vec3 cubeAmbient[] = {
        glm::vec3(0.0215f,	0.1745f, 0.0215f),
        glm::vec3(0.25f, 0.20725f, 0.20725f),
        glm::vec3(0.2125f, 0.1275f, 0.054f),
        glm::vec3(0.24725f, 0.1995f, 0.0745f),
        glm::vec3(0.0f, 0.1f, 0.06f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.05f, 0.0f),
        glm::vec3(0.05f, 0.05f, 0.0f),
        glm::vec3(0.19225f, 0.19225f, 0.19225f),
        glm::vec3(0.25f, 0.25f, 0.25f)
    };

    glm::vec3 cubDiffuse[] = {
        glm::vec3(0.07568f, 0.61424f, 0.07568f),
        glm::vec3(1.0f, 0.829f, 0.829f),
        glm::vec3(0.714f, 0.4284f, 0.18144f),
        glm::vec3(0.75164f, 0.60648f, 0.22648f),
        glm::vec3(0.0f, 0.50980392f, 0.50980392f),
        glm::vec3(0.5f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.5f, 0.4f),
        glm::vec3(0.5f, 0.5f, 0.4f),
        glm::vec3(0.50754f, 0.50754f, 0.50754f),
        glm::vec3(0.4f, 0.4f, 0.4f)
    };

    glm::vec3 cubeSpecular[] = {
        glm::vec3(0.633f, 0.727811f, 0.633f),
        glm::vec3(0.296648f, 0.296648f, 0.296648f),
        glm::vec3(0.393548f, 0.271906f, 0.166721f),
        glm::vec3(0.628281f, 0.555802f, 0.366065f),
        glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
        glm::vec3(0.7f, 0.6f, 0.6f),
        glm::vec3(0.04f, 0.7f, 0.04f),
        glm::vec3(0.7f, 0.7f, 0.04f),
        glm::vec3(0.508273f, 0.508273f, 0.508273f),
        glm::vec3(0.774597f, 0.774597f, 0.774597f)
    };

    float cubeShininess[] = {
        0.6f, 
        0.088f, 
        0.2f,
        0.4f,
        0.25f,
        0.25f,
        0.078125f,
        0.078125f,
        0.4f,
        0.6f
    };




    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        float radius = 0.6f;
        

        glm::mat4 model;
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,  0.1f, 100.0f);  //透视       

        glm::vec3 lightPos = glm::vec3(sin(glfwGetTime()) * radius, 0.1f, cos(glfwGetTime()) * radius);
        glm::vec3 lightColor =  glm::vec3(1.0f, 1.0f, 1.0f);// glm::vec3(sin(currentFrame) * 2.0f, sin(currentFrame) * 0.3f, sin(currentFrame) * 1.7f);  

        for (int i = 0; i < 10; i++) {
            objShader.use();
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.5f));
            
            objShader.setMat4("model", model);
            objShader.setMat4("view", view);
            objShader.setMat4("projection", projection);
            
            objShader.setVec3("viewPos", camera.Position);

            objShader.setVec3("material.ambient", cubeAmbient[i]);
            objShader.setVec3("material.diffuse", cubDiffuse[i]);
            objShader.setVec3("material.specular", cubeSpecular[i]);
            objShader.setFloat("material.shininess", cubeShininess[i] * 128.f);

            
            objShader.setVec3("light.position", cubePositions[i] + lightPos);
            objShader.setVec3("light.ambient", lightColor * glm::vec3(1.0f));
            objShader.setVec3("light.diffuse", lightColor * glm::vec3(0.2f));
            objShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            lampShader.use();
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));

            lampShader.setMat4("model", model);
            lampShader.setMat4("view", view);
            lampShader.setMat4("projection", projection);

            lampShader.setVec3("lightColor", lightColor);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();

    return 0;
}
