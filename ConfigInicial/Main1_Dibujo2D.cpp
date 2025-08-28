/*
======================================================
Alcalá Briseño Martha Alondra
Práctica 2 - Computación Gráfica
22/08/25
319300602
======================================================
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    //Verificación de compatibilidad 
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2 Alondra Alcala", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    //Verificación de errores de creación ventana
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Verificación de errores de inicialización de glew
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Imprimimos información de OpenGL del sistema
    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Vértices:
    float vertices[] = {
        // Ojo negro
        -0.2f,  0.2f, 0.0f,  0.0f,0.0f,0.0f, // 0
        -0.2f,  0.1f, 0.0f,  0.0f,0.0f,0.0f, // 1
        -0.3f,  0.1f, 0.0f,  0.0f,0.0f,0.0f, // 2
        -0.3f,  0.2f, 0.0f,  0.0f,0.0f,0.0f, // 3

        // Segundo ojo negro
        0.2f,  0.2f, 0.0f,  0.0f,0.0f,0.0f, // 4
        0.2f,  0.1f, 0.0f,  0.0f,0.0f,0.0f, // 5
        0.3f,  0.1f, 0.0f,  0.0f,0.0f,0.0f, // 6
        0.3f,  0.2f, 0.0f,  0.0f,0.0f,0.0f, // 7

        // Cuerpo
         0.4f,  0.1f, 0.0f,  1.0f,0.0f,0.0f, // 8
         0.4f, -0.6f, 0.0f,  1.0f,0.0f,0.0f, // 9
        -0.4f, -0.6f, 0.0f,  1.0f,0.0f,0.0f, // 10
        -0.4f,  0.1f, 0.0f,  1.0f,0.0f,0.0f, // 11

        //Colita
        0.2f,  -0.6f, 0.0f,  1.0f,0.0f,0.0f, // 12
         0.2f, -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 13
        -0.2f, -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 14
        -0.2f,  -0.6f, 0.0f,  1.0f,0.0f,0.0f, // 15

        //rec1
        -0.4f,  -0.5f, 0.0f,  1.0f,0.0f,0.0f, // 16
        -0.4f, -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 17
        -0.5f,  -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 18
        -0.5f, -0.5f, 0.0f,  1.0f,0.0f,0.0f, // 19

        //rec2
        0.5f,  -0.5f, 0.0f,  1.0f,0.0f,0.0f, // 20
        0.5f, -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 21
        0.4f,  -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 22
        0.4f, -0.5f, 0.0f,  1.0f,0.0f,0.0f, // 23

        //
        -0.5f,  -0.6f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.5f, -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.6f,  -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.6f, -0.6f, 0.0f,  1.0f,0.0f,0.0f, // 

        //
       0.6f,  -0.6f, 0.0f,  1.0f,0.0f,0.0f, //
        0.6f, -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.5f,  -0.7f, 0.0f,  1.0f,0.0f,0.0f, // 
       0.5f, -0.6f, 0.0f,  1.0f,0.0f,0.0f, //  

       -0.4f,  0.0f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.4f, -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.5f,  -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.5f, -0.0f, 0.0f,  1.0f,0.0f,0.0f, // 

        0.5f,  0.0f, 0.0f,  1.0f,0.0f,0.0f, //
        0.5f, -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.4f,  -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
       0.4f, -0.0f, 0.0f,  1.0f,0.0f,0.0f, // 

        -0.5f,  -0.3f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.5f, -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.7f,  -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.7f, -0.3f, 0.0f,  1.0f,0.0f,0.0f, //

        0.5f,  -0.4f, 0.0f,  1.0f,0.0f,0.0f, //
        0.5f, -0.3f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.7f,  -0.3f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.7f, -0.4f, 0.0f,  1.0f,0.0f,0.0f, //

        -0.6f,  -0.4f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.6f, -0.5f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.8f,  -0.5f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.8f, -0.4f, 0.0f,  1.0f,0.0f,0.0f, //

        0.6f,  -0.5f, 0.0f,  1.0f,0.0f,0.0f, //
        0.6f, -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.8f,  -0.4f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.8f, -0.5f, 0.0f,  1.0f,0.0f,0.0f, //

        -0.5f,  0.0f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.5f, -0.2f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.7f,  -0.2f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.7f, 00.0f, 0.0f,  1.0f,0.0f,0.0f, //

        0.5f,  -0.2f, 0.0f,  1.0f,0.0f,0.0f, //
        0.5f, 0.0f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.7f,  0.0f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.7f, -0.2f, 0.0f,  1.0f,0.0f,0.0f, //

         -0.6f,  0.3f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.6f, -0.1f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.8f,  -0.1f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.8f, 0.3f, 0.0f,  1.0f,0.0f,0.0f, //

        0.6f,  -0.1f, 0.0f,  1.0f,0.0f,0.0f, //
        0.6f, 0.3f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.8f,  0.3f, 0.0f,  1.0f,0.0f,0.0f, // 
        0.8f, -0.1f, 0.0f,  1.0f,0.0f,0.0f, //

        -0.4f,  0.5f, 0.0f,  1.0f,0.0f,0.0f, //
        -0.4f, 0.2f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.7f,  0.2f, 0.0f,  1.0f,0.0f,0.0f, // 
        -0.7f, 0.5f, 0.0f,  1.0f,0.0f,0.0f, //

        0.7f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //
        0.7f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.4f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.4f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //

        -0.2f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f, //
        -0.2f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        -0.6f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        -0.6f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f, //

        0.6f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f, //
        0.6f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.2f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.2f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f, //

        -0.3f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //
        -0.3f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        -0.4f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        -0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //

        0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //
        0.4f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.3f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.3f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //

        -0.2f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //
        -0.2f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        -0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        -0.3f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //

        0.3f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //
        0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.2f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // 
        0.2f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //
    };

    unsigned int indices[] = {
        // Ojo (negro)
        0, 1, 2, // primer triángulo
        0, 2, 3, // segundo triángulo

        // Segundo ojo negro
        4, 5, 6, // tercer triángulo
        4, 6, 7,  // cuarto triángulo

        // Cuerpo rojo
        8, 9, 10, // tercer triángulo
        8, 10, 11,  // cuarto triángulo

        // Colita
        12, 13, 14, // tercer triángulo
        12, 14, 15,  // cuarto triángulo

        16, 17, 18,
        16, 18, 19, //30

        20,21,22,
        20,22,23,

        24,25,26,
        24,26,27,//

        28,29,30,
        28,30,31,//

        32,33,34,
        32,34,35,//

        36,37,38,
        36,38,39,//

        40,41,42,
        40,42,43,//

        44,45,46,
        44,46,47,//

        48,49,50,
        48,50,51,//

        52,53,54,
        52,54,55,//

        56,57,58,
        56,58,59,//

        60,61,62,
        60,62,63,//

        64,65,66,
        64,66,67,//1

        68,69,70,
        68,70,71,//2

        72,73,74,
        72,74,75,//3

        76,77,78,
        76,78,79,//4

        80,81,82,
        80,82,83,//5

        84,85,86,
        84,86,87,//6

        88,89,90,
        88,90,91,//7

        92,93,94,
        92,94,95,//8

        96,97,98,
        96,98,99,//9

        100,101,102,
        100,102,103//10


        //Total indices: 156
        //!!Agregar en         glDrawElements(GL_TRIANGLES, XXXXXXXX, GL_UNSIGNED_INT, 0);
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Enlazar Vertex Array Object
    glBindVertexArray(VAO);

    // Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Despues colocamos las características de los vertices

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind VAO

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // fondo blanco
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);

        //xxxxxxxxxxxxxxx 6 por indice
      glDrawElements(GL_TRIANGLES, 156, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}