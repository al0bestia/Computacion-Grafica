/*
======================================================
Alcalá Briseño Martha Alondra
Práctica 3 - Computación Gráfica
28/08/25
319300602
======================================================
*/


#include <iostream>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 3 AA", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    // OpenGL
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // === CUBO BASE (caras con colores distintos) ===
    float vertices[] = {
        //   pos xyz              color rgb
        // Frente (+Z) - rojo
        -0.5f,-0.5f, 0.5f,       1.0f,0.0f,0.0f,
         0.5f,-0.5f, 0.5f,       1.0f,0.0f,0.0f,
         0.5f, 0.5f, 0.5f,       1.0f,0.0f,0.0f,
         0.5f, 0.5f, 0.5f,       1.0f,0.0f,0.0f,
        -0.5f, 0.5f, 0.5f,       1.0f,0.0f,0.0f,
        -0.5f,-0.5f, 0.5f,       1.0f,0.0f,0.0f,

        // Atrás (−Z) - verde
        -0.5f,-0.5f,-0.5f,       0.0f,1.0f,0.0f,
         0.5f,-0.5f,-0.5f,       0.0f,1.0f,0.0f,
         0.5f, 0.5f,-0.5f,       0.0f,1.0f,0.0f,
         0.5f, 0.5f,-0.5f,       0.0f,1.0f,0.0f,
        -0.5f, 0.5f,-0.5f,       0.0f,1.0f,0.0f,
        -0.5f,-0.5f,-0.5f,       0.0f,1.0f,0.0f,

        // Derecha (+X) - azul
         0.5f,-0.5f, 0.5f,       0.0f,0.0f,1.0f,
         0.5f,-0.5f,-0.5f,       0.0f,0.0f,1.0f,
         0.5f, 0.5f,-0.5f,       0.0f,0.0f,1.0f,
         0.5f, 0.5f,-0.5f,       0.0f,0.0f,1.0f,
         0.5f, 0.5f, 0.5f,       0.0f,0.0f,1.0f,
         0.5f,-0.5f, 0.5f,       0.0f,0.0f,1.0f,

         // Izquierda (−X) - amarillo
         -0.5f, 0.5f, 0.5f,       1.0f,1.0f,0.0f,
         -0.5f, 0.5f,-0.5f,       1.0f,1.0f,0.0f,
         -0.5f,-0.5f,-0.5f,       1.0f,1.0f,0.0f,
         -0.5f,-0.5f,-0.5f,       1.0f,1.0f,0.0f,
         -0.5f,-0.5f, 0.5f,       1.0f,1.0f,0.0f,
         -0.5f, 0.5f, 0.5f,       1.0f,1.0f,0.0f,

         // Abajo (−Y) - cian
         -0.5f,-0.5f,-0.5f,       0.0f,1.0f,1.0f,
          0.5f,-0.5f,-0.5f,       0.0f,1.0f,1.0f,
          0.5f,-0.5f, 0.5f,       0.0f,1.0f,1.0f,
          0.5f,-0.5f, 0.5f,       0.0f,1.0f,1.0f,
         -0.5f,-0.5f, 0.5f,       0.0f,1.0f,1.0f,
         -0.5f,-0.5f,-0.5f,       0.0f,1.0f,1.0f,

         // Arriba (+Y) - magenta
         -0.5f, 0.5f,-0.5f,       1.0f,0.2f,0.5f,
          0.5f, 0.5f,-0.5f,       1.0f,0.2f,0.5f,
          0.5f, 0.5f, 0.5f,       1.0f,0.2f,0.5f,
          0.5f, 0.5f, 0.5f,       1.0f,0.2f,0.5f,
         -0.5f, 0.5f, 0.5f,       1.0f,0.2f,0.5f,
         -0.5f, 0.5f,-0.5f,       1.0f,0.2f,0.5f,
    };

    // Buffers
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atributos de vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Matrices
    glm::mat4 projection = glm::perspective(glm::radians(55.0f),
        (GLfloat)screenWidth / (GLfloat)screenHeight,
        0.1f, 100.0f);

    // === PIRÁMIDE COMPACTA ===
    const float step = 1.1f; // sep. horizontal (~0.1 de holgura)
    const float vstep = 1.1f; // sep. vertical
    glm::vec3 cubePositions[6] = {
        // Fila inferior (3)
        glm::vec3(-step, -vstep, 0.0f),
        glm::vec3(0.0f, -vstep, 0.0f),
        glm::vec3(step,  -vstep, 0.0f),
        // Fila media (2)
        glm::vec3(-step * 0.5f, 0.0f, 0.0f),
        glm::vec3(step * 0.5f, 0.0f, 0.0f),
        // Cima (1)
        glm::vec3(0.0f, vstep, 0.0f)
    };

    // Rotaciones por cubo para mostrar caras distintas al frente
    // +Z (rojo), −Z (verde), +X (azul), −X (amarillo), +Y (magenta), −Y (cian)
    float cubeRotAngleDeg[6] = {
        0.0f,    // +Z
        180.0f,  // −Z (Y 180°)
        -90.0f,  // +X (Y -90°)
        90.0f,   // −X (Y 90°)
        -90.0f,  // +Y (X -90°)
        90.0f    // −Y (X 90°)
    };
    glm::vec3 cubeRotAxis[6] = {
        {0.0f, 1.0f, 0.0f}, // 0°
        {0.0f, 1.0f, 0.0f}, // 180° Y
        {0.0f, 1.0f, 0.0f}, // -90° Y
        {0.0f, 1.0f, 0.0f}, //  90° Y
        {1.0f, 0.0f, 0.0f}, // -90° X
        {1.0f, 0.0f, 0.0f}  //  90° X
    };

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();

        // Cámara: un poco atrás e inclinada hacia abajo
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        view = glm::rotate(view, glm::radians(-12.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        for (int i = 0; i < 6; ++i) {
            glm::mat4 model = glm::mat4(1.0f);
            // T * R  -> rota en su centro y luego coloca el cubo en su posición
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(cubeRotAngleDeg[i]), cubeRotAxis[i]);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}
