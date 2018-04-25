// //
// //  main.cpp
// //  GLFWTest
// //
// //  Created by wynne on 2018/3/22.
// //  Copyright © 2018年 wynne. All rights reserved.
// //

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <cmath>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow *window)
// {
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }


// const char* vertexShaderCode = "#version 330 core\n"
// "layout (location = 0) in vec3 pos;\n"
// "layout (location = 1) in vec3 color;\n"
// "out vec3 myColor;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
// "   myColor = color;\n"
// "}\n\0";


// const char* fragmentShaderCode = "#version 330 core\n"
// "out vec4 color;\n"
// "in vec3 myColor;\n"
// "uniform float alpha;\n"
// "void main()\n"
// "{\n"
// "   color = vec4(myColor, alpha);\n"
// "}\n\0";

// int main()
// {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     #endif
    
//     GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
    
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

    
    
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
//     glCompileShader(vertexShader);
    
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    
    
//     int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
//     glCompileShader(fragmentShader);
    

//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    
//     //link shader
//     int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
    
//     // check for linking errors
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//     }
    
//     //don't forget to delete the shader objects once we've linked them into the program object; we no longer need them anymore:
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
    
//     //vertex data
//     float vertices[] = {
//         -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,// left
//          0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,// right
//          0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,// top
//         //0.5f,  0.5f, 0.0f
        
//         // 0, -0.5f, 0.0f, // right
//         // 0.0f,  0.5f, 0.0f,  // top
//         // 0.5f,  0.5f, 0.0f
//     };
    
//     unsigned int indices[] = {  // note that we start from 0!
//         0, 1, 2,  // first Triangle
//         1, 2, 3   // second Triangle
//     };
    
    
//     //bind the array first
//     unsigned int VAO;
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);
    
//     //copy vertext array in a buffer for OpenGL to use
//     unsigned int VBO;
//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//     //
//     unsigned int EBO;
//     glGenBuffers(1, &EBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
//     //set vertex attributes pointers
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
    
    
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);


    
    
    
//     glViewport(0, 0, 800, 600);
    
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
//     while(!glfwWindowShouldClose(window))
//     {
//         processInput(window);
//         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         glUseProgram(shaderProgram);
//         float timeValue = glfwGetTime();
//         float alpha = (sin(timeValue) / 2.0f) + 0.5f;
//         int alphaLocation = glGetUniformLocation(shaderProgram, "alpha");
//         glUseProgram(shaderProgram);
//         glUniform1f(alphaLocation, alpha);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);
//         //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
    
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);
    
//     glfwTerminate();

//     return 0;
// }


//
//  main.cpp
//  GLFWTest
//
//  Created by wynne on 2018/3/22.
//  Copyright © 2018年 wynne. All rights reserved.
//

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <cmath>
// #include <unistd.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/type_ptr.hpp"

// float deltaTime = 0.0f;	// Time between current frame and last frame
// float lastFrame = 0.0f; // Time of last frame

// glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow *window)
// {
//     float speed = 2.5f * deltaTime;;
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
//     else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         cameraPos += speed * cameraFront;
//     else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         cameraPos -= speed * cameraFront;
//     else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         cameraPos -= speed * glm::normalize(glm::cross(cameraFront, cameraUp));
//     else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         cameraPos += speed * glm::normalize(glm::cross(cameraFront, cameraUp)); 

// }


// const char* vertexShaderCode = "#version 330 core\n"
// "layout (location = 0) in vec3 pos;\n"
// "layout (location = 1) in vec2 tex;"
// "out vec2 myTex;\n"
// "uniform float alpha;\n"
// "uniform mat4 trans;\n"
// "uniform mat4 model;\n"
// "uniform mat4 view;\n"
// "uniform mat4 projection;\n"
// "void main()\n"
// "{\n"
// "   //gl_Position = trans * vec4(pos.x , pos.y, pos.z, 1.0);\n"
// "   gl_Position = projection * view * model * vec4(pos, 1.0);\n"
// "   myTex = tex;\n"
// "}\n\0";


// const char* fragmentShaderCode = "#version 330 core\n"
// "out vec4 color;\n"
// "in vec3 myColor;\n"
// "in vec2 myTex;\n"
// "uniform float alpha;\n"
// "uniform sampler2D texture0;\n"
// "uniform sampler2D texture1;\n"
// "void main()\n"
// "{\n"
// "   //color = mix(texture(texture0, myTex), texture(texture1, myTex), alpha);\n"
// "   color = mix(texture(texture0, myTex), texture(texture1, myTex), 0.5);\n"
// "}\n\0";


// float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
// float pitch =  0.0f;
// float lastX =  800.0f / 2.0;
// float lastY =  600.0 / 2.0;
// float fov   =  45.0f;
// bool firstMouse = true;

// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//   if(fov >= 1.0f && fov <= 45.0f)
//   	fov -= yoffset;
//   if(fov <= 1.0f)
//   	fov = 1.0f;
//   if(fov >= 45.0f)
//   	fov = 45.0f;
// }

// void mouse_callback(GLFWwindow* window, double xpos, double ypos)
// {
//     if(firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; 
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.05;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw   += xoffset;
//     pitch += yoffset;

//     if(pitch > 89.0f)
//         pitch = 89.0f;
//     if(pitch < -89.0f)
//         pitch = -89.0f;

//     glm::vec3 front;
//     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front.y = sin(glm::radians(pitch));
//     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     cameraFront = glm::normalize(front);
// }


// int main()
// {
//     int width, height, nrChannels;
//     int width1, height1, nrChannels1;
//     stbi_set_flip_vertically_on_load(true);
//     char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below    
//     printf("Current dir: %s", dir);
//     std::stringstream ss1;
//     ss1 << dir << "/" << "container.jpg";
//     std::stringstream ss2;
//     ss2 << dir << "/" << "smile.png";
//     unsigned char *data = stbi_load(ss1.str().c_str(), &width, &height, &nrChannels, 0); 
//     unsigned char *data1 = stbi_load(ss2.str().c_str(), &width1, &height1, &nrChannels1, 0); 

//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     #endif
    
//     GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
    
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

    
    
//     glEnable(GL_BLEND);
//     glEnable(GL_DEPTH_TEST);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     glfwSetCursorPosCallback(window, mouse_callback);
//     glfwSetScrollCallback(window, scroll_callback);

//     unsigned int texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);

//     unsigned int texture1;
//     glGenTextures(1, &texture1);
//     glBindTexture(GL_TEXTURE_2D, texture1);

//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data1);


   



//     int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
//     glCompileShader(vertexShader);
    
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    
    
//     int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
//     glCompileShader(fragmentShader);
    

//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    
//     //link shader
//     int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
    
//     // check for linking errors
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//     }
    
//     //don't forget to delete the shader objects once we've linked them into the program object; we no longer need them anymore:
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
    
//     //vertex data
//     // float vertices[] = {
//     //     // positions          // texture coords
//     //      0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//     //      0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//     //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//     //     -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
//     // };
//     // unsigned int indices[] = {
//     //     0, 1, 3, // first triangle
//     //     1, 2, 3  // second triangle
//     // };
    
    
//     // //bind the array first
//     // unsigned int VAO;
//     // glGenVertexArrays(1, &VAO);
//     // glBindVertexArray(VAO);
    
//     // //copy vertext array in a buffer for OpenGL to use
//     // unsigned int VBO;
//     // glGenBuffers(1, &VBO);
//     // glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//     // //
//     // unsigned int EBO;
//     // glGenBuffers(1, &EBO);
//     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
//     // //set vertex attributes pointers
//     // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     // glEnableVertexAttribArray(0);

//     // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//     // glEnableVertexAttribArray(1);


    
//     // glBindBuffer(GL_ARRAY_BUFFER, 0);
//     // glBindVertexArray(0);

//     float vertices[] = {
//         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//     };
//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // position attribute
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // texture coord attribute
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

    
    
//     glViewport(0, 0, 800, 600);
    
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
//     glm::vec3 cubePositions[] = {
//     glm::vec3( 0.0f,  0.0f,  0.0f), 
//     glm::vec3( 2.0f,  5.0f, -15.0f), 
//     glm::vec3(-1.5f, -2.2f, -2.5f),  
//     glm::vec3(-3.8f, -2.0f, -12.3f),  
//     glm::vec3( 2.4f, -0.4f, -3.5f),  
//     glm::vec3(-1.7f,  3.0f, -7.5f),  
//     glm::vec3( 1.3f, -2.0f, -2.5f),  
//     glm::vec3( 1.5f,  2.0f, -2.5f), 
//     glm::vec3( 1.5f,  0.2f, -1.5f), 
//     glm::vec3(-1.3f,  1.0f, -1.5f)  
//     };

//     while(!glfwWindowShouldClose(window))
//     {
//         processInput(window);
//         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture);
//         glActiveTexture(GL_TEXTURE1);
//         glBindTexture(GL_TEXTURE_2D, texture1);
//         glUseProgram(shaderProgram);
//         glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0); 
//         glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 1); 
       
//         float timeValue = glfwGetTime();
//         float alpha = (sin(timeValue) / 2.0f) + 0.5f;
//         glm::mat4 trans;
//         //trans = glm::translate(trans, glm::vec3(alpha - 0.5f, -alpha + 0.5f, 0.0f));
//         //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
//         //trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f) * alpha);

//         float currentFrame = glfwGetTime();
//         deltaTime = currentFrame - lastFrame;
//         lastFrame = currentFrame;  

//         for (unsigned int i = 0; i < 10; i++) {
//             glm::mat4 model;
//             model = glm::translate(model, cubePositions[i]);
//             //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));  //沿着x轴旋转55度
//             model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f) * (i + 1), glm::vec3(0.5f, 1.0f, 0.5f));  
//             glm::mat4 view;
//             float radius = 10.0f;
//             float camX = sin(glfwGetTime()) * radius;
//             float camZ = cos(glfwGetTime()) * radius;
//             view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//             //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //沿着z轴负方向移动

//             glm::mat4 projection;
//             projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);  //透视
            
//             glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "trans"), 1, GL_FALSE, glm::value_ptr(trans));
//             int alphaLocation = glGetUniformLocation(shaderProgram, "alpha");
//             glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//             glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//             glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//             glUseProgram(shaderProgram);
//             glUniform1f(alphaLocation, alpha);
//             glBindVertexArray(VAO);
//             glDrawArrays(GL_TRIANGLES, 0, 36);
//         }
        
//         //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
    
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     //glDeleteBuffers(1, &EBO);
    
//     glfwTerminate();

//     return 0;
// }



// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <cmath>
// #include <unistd.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/type_ptr.hpp"

// float deltaTime = 0.0f;	// Time between current frame and last frame
// float lastFrame = 0.0f; // Time of last frame

// glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow *window)
// {
//     float speed = 2.5f * deltaTime;;
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
//     else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         cameraPos += speed * cameraFront;
//     else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         cameraPos -= speed * cameraFront;
//     else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         cameraPos -= speed * glm::normalize(glm::cross(cameraFront, cameraUp));
//     else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         cameraPos += speed * glm::normalize(glm::cross(cameraFront, cameraUp)); 

// }


// const char* vertexShaderCode = "#version 330 core\n"
// "layout (location = 0) in vec3 pos;\n"
// "layout (location = 1) in vec3 normal;\n"
// "uniform mat4 model;\n"
// "uniform mat4 view;\n"
// "uniform mat4 projection;\n"
// "out vec3 WorldPos;\n"
// "out vec3 Normal;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = projection * view * model * vec4(pos, 1.0);\n"
// "   WorldPos = vec3(model * vec4(pos, 1.0));\n"
// "   Normal = mat3(transpose(inverse(model))) * normal;\n"
// "}\n\0";


// const char* fragmentShaderCode = "#version 330 core\n"
// "in vec3 WorldPos;\n"
// "in vec3 Normal;\n"
// "out vec4 color;\n"
// "uniform vec3 lightcolor;\n"
// "uniform vec3 objcolor;\n"
// "uniform vec3 lightpos;\n"
// "uniform vec3 viewpos;\n"
// "void main()\n"
// "{\n"
// "   float ambientStrength = 0.1f;\n"
// "   vec3 ambient = ambientStrength * lightcolor;\n"
// "   vec3 normal = normalize(Normal);\n"
// "   vec3 lightdir = normalize(lightpos - WorldPos);\n"
// "   float diff = max(dot(Normal, lightdir), 0.0);\n"
// "   vec3 diffuse = diff * lightcolor;\n"
// "   float specularStrength = 0.5;\n"
// "   vec3 viewdir = normalize(viewpos - WorldPos);\n"
// "   vec3 reflectdir = reflect(-lightdir, normal);\n"
// "   float spec = pow(max(dot(viewdir, reflectdir), 0.0), 256);\n"
// "   vec3 specular = specularStrength * spec * lightcolor;\n"
// "   color = vec4((ambient + diffuse + specular) * objcolor, 1.0);\n"
// "}\n\0";

// const char* lightFragmentShaderCode = "#version 330 core\n"
// "out vec4 color;\n"
// "uniform vec3 lightcolor;\n"
// "void main()\n"
// "{\n"
// "   color = vec4(lightcolor, 1.0);\n"
// "}\n\0";


// float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
// float pitch =  0.0f;
// float lastX =  800.0f / 2.0;
// float lastY =  600.0 / 2.0;
// float fov   =  45.0f;
// bool firstMouse = true;

// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//   if(fov >= 1.0f && fov <= 45.0f)
//   	fov -= yoffset;
//   if(fov <= 1.0f)
//   	fov = 1.0f;
//   if(fov >= 45.0f)
//   	fov = 45.0f;
// }

// void mouse_callback(GLFWwindow* window, double xpos, double ypos)
// {
//     if(firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; 
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.05;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw   += xoffset;
//     pitch += yoffset;

//     if(pitch > 89.0f)
//         pitch = 89.0f;
//     if(pitch < -89.0f)
//         pitch = -89.0f;

//     glm::vec3 front;
//     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front.y = sin(glm::radians(pitch));
//     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     cameraFront = glm::normalize(front);
// }


// int main()
// {
//     int width, height, nrChannels;
//     int width1, height1, nrChannels1;
//     stbi_set_flip_vertically_on_load(true);
//     char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below    
//     printf("Current dir: %s", dir);
//     std::stringstream ss1;
//     ss1 << dir << "/" << "container.jpg";
//     std::stringstream ss2;
//     ss2 << dir << "/" << "smile.png";
//     unsigned char *data = stbi_load(ss1.str().c_str(), &width, &height, &nrChannels, 0); 
//     unsigned char *data1 = stbi_load(ss2.str().c_str(), &width1, &height1, &nrChannels1, 0); 

//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     #endif
    
//     GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
    
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

    
    
//     glEnable(GL_BLEND);
//     glEnable(GL_DEPTH_TEST);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     glfwSetCursorPosCallback(window, mouse_callback);
//     glfwSetScrollCallback(window, scroll_callback);

//     unsigned int texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);

//     unsigned int texture1;
//     glGenTextures(1, &texture1);
//     glBindTexture(GL_TEXTURE_2D, texture1);

//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data1);


   



//     int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
//     glCompileShader(vertexShader);
    
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    
    
//     int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
//     glCompileShader(fragmentShader);
    

//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    

//     int lightFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(lightFragmentShader, 1, &lightFragmentShaderCode, NULL);
//     glCompileShader(lightFragmentShader);
    

//     glGetShaderiv(lightFragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glad_glGetShaderInfoLog(lightFragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::LIGHT::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
    

//     //link shader
//     int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
    
//     // check for linking errors
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//     }

//     int lightShaderProgram = glCreateProgram();
//     glAttachShader(lightShaderProgram, vertexShader);
//     glAttachShader(lightShaderProgram, lightFragmentShader);
//     glLinkProgram(lightShaderProgram);
    
//     // check for linking errors
//     glGetProgramiv(lightShaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(lightShaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//     }
    
//     //don't forget to delete the shader objects once we've linked them into the program object; we no longer need them anymore:
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
//     glDeleteShader(lightFragmentShader);
    
    
//     float vertices[] = {
//         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//          0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

//         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//          0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

//         -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

//          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

//         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

//         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//     };
//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

    
//     glViewport(0, 0, 800, 600);
    
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     glm::vec3 objColor = glm::vec3(1.0f, 0.5f, 0.31f);
//     glm::vec3 lightpos = glm::vec3(1.0f, 0.0f, 2.0f);
//     while(!glfwWindowShouldClose(window))
//     {
//         processInput(window);
//         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         glUseProgram(shaderProgram);
        
       
//         float timeValue = glfwGetTime();
//         float alpha = (sin(timeValue) / 2.0f) + 0.5f;
//         float currentFrame = glfwGetTime();
//         deltaTime = currentFrame - lastFrame;
//         lastFrame = currentFrame;  

//         glm::mat4 model;
//         //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
//         glm::mat4 view;
//         float radius = 2.0f;
//         float camX = sin(glfwGetTime()) * radius;
//         float camZ = cos(glfwGetTime()) * radius;
//         view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//         //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //沿着z轴负方向移动


//         lightpos = glm::vec3(sin(glfwGetTime()) * radius, 0.0f, cos(glfwGetTime()) * radius);

//         glm::mat4 projection;
//         projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);  //透视       
//         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//         glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//         glUniform3fv(glGetUniformLocation(shaderProgram, "lightcolor"), 1, glm::value_ptr(lightColor));
//         glUniform3fv(glGetUniformLocation(shaderProgram, "objcolor"), 1,  glm::value_ptr(objColor));
//         glUniform3fv(glGetUniformLocation(shaderProgram, "lightpos"), 1,  glm::value_ptr(lightpos));
//         glUniform3fv(glGetUniformLocation(shaderProgram, "viewpos"), 1,  glm::value_ptr(cameraPos));
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 36);

//         glUseProgram(lightShaderProgram);
//         glm::mat4 model1;
//         model1 = glm::translate(model1, lightpos);
//         model1 = glm::scale(model1, glm::vec3(0.2f));
//         glUniformMatrix4fv(glGetUniformLocation(lightShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model1));
//         glUniformMatrix4fv(glGetUniformLocation(lightShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//         glUniformMatrix4fv(glGetUniformLocation(lightShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//         glUniform3fv(glGetUniformLocation(shaderProgram, "lightcolor"), 1, glm::value_ptr(lightColor));
        
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 36);


        
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
    
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
    
//     glfwTerminate();

//     return 0;
// }


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


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
    char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below    
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
