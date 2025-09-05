/*
====================================================== 
Alcalá Briseño Martha Alondra
Practica 4 - Computación Gráfica
05/09/25
319300602
======================================================
*/

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f, movY = 0.0f, movZ = -6.0f, rot = 0.0f;

GLuint makeCubeVAO(float r, float g, float b) {
    const float P[] = {
        // front
        -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,-0.5f, 0.5f,
         // back
         -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
          0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
          // right
           0.5f,-0.5f, 0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
           0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,  0.5f,-0.5f, 0.5f,
           // left
           -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
           -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
           // bottom
           -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
            0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,
            // top
            -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
             0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f
    };
    std::vector<float> V; V.reserve(36 * 6);
    for (int i = 0; i < 36; ++i) {
        V.push_back(P[i * 3 + 0]);
        V.push_back(P[i * 3 + 1]);
        V.push_back(P[i * 3 + 2]);
        V.push_back(r); V.push_back(g); V.push_back(b);
    }
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, V.size() * sizeof(float), V.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PRACTICA 4 AA", nullptr, nullptr);
    if (!window) { std::cout << "Failed to create window\n"; glfwTerminate(); return -1; }
    int screenWidth, screenHeight; glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { std::cout << "Failed to init GLEW\n"; return -1; }

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);

    Shader shader("Shader/core.vs", "Shader/core.frag");

    // --------- COLORES ---------
    const GLuint VAO_BROWN = makeCubeVAO(0.62f, 0.40f, 0.18f); // cafee
    const GLuint VAO_BEIGE = makeCubeVAO(0.93f, 0.86f, 0.72f); // beige
    const GLuint VAO_BLACK = makeCubeVAO(0.05f, 0.05f, 0.05f); // negro

    // --------- PARAMETROS ---------
    const glm::vec3 BODY_SCALE = glm::vec3(1.40f, 1.75f, 0.90f);

    const float NOSE_WX = 0.45f, NOSE_WY = 0.28f, NOSE_WZ = 0.12f;
    const float EYE_WX = 0.20f, EYE_HY = 0.45f, EYE_WZ = 0.10f;
    const float EYE_CENTER_X = (EYE_WX * 0.5f) + (NOSE_WX * 0.5f) + 0.10f;
    const float EYE_Y = 1.58f;

    // PANCITA
    const glm::vec3 BELLY_SCALE = glm::vec3(0.90f, 1.00f, 0.07f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0, 1, 0));

        GLint uModel = glGetUniformLocation(shader.Program, "model");
        GLint uView = glGetUniformLocation(shader.Program, "view");
        GLint uProj = glGetUniformLocation(shader.Program, "projection");
        glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 M;

        // ===== CUERPO =====
        glBindVertexArray(VAO_BROWN);
        M = glm::scale(glm::mat4(1.0f), BODY_SCALE);
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== PANCITA =====
        glBindVertexArray(VAO_BEIGE);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.10f, 0.492f));
        M = glm::scale(M, BELLY_SCALE);
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // pedacito extra de pancita, abajo 
        glBindVertexArray(VAO_BEIGE);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.475f, 0.492f));
        M = glm::scale(M, glm::vec3(0.37f, 0.15f, 0.07f)); // mismo tamaño en Y
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== CABEZA =====
        glBindVertexArray(VAO_BROWN);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.55f, 0.0f));
        M = glm::scale(M, glm::vec3(1.4f, 1.2f, 1.0f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== BOCA =====
        glBindVertexArray(VAO_BEIGE);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.25f, 0.505f));
        M = glm::scale(M, glm::vec3(1.00f, 0.45f, 0.30f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== NARIZ =====
        glBindVertexArray(VAO_BLACK);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.35f, 0.66f));
        M = glm::scale(M, glm::vec3(NOSE_WX, NOSE_WY, NOSE_WZ));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== OJOS =====
        glBindVertexArray(VAO_BLACK);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-EYE_CENTER_X, EYE_Y, 0.505f));
        M = glm::scale(M, glm::vec3(EYE_WX, EYE_HY, EYE_WZ));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        M = glm::translate(glm::mat4(1.0f), glm::vec3(EYE_CENTER_X, EYE_Y, 0.505f));
        M = glm::scale(M, glm::vec3(EYE_WX, EYE_HY, EYE_WZ));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== OREJAS =====
        glBindVertexArray(VAO_BROWN);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.72f, 2.22f, 0.10f));
        M = glm::scale(M, glm::vec3(0.40f, 0.40f, 0.40f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.72f, 2.22f, 0.10f));
        M = glm::scale(M, glm::vec3(0.40f, 0.40f, 0.40f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== HOMBROS (LATERALES) =====
        glBindVertexArray(VAO_BROWN);
        // izquierdo
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.875f, 0.40f, 0.10f));
        M = glm::scale(M, glm::vec3(0.35f, 0.35f, 0.35f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // derecho
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.875f, 0.40f, 0.10f));
        M = glm::scale(M, glm::vec3(0.35f, 0.35f, 0.35f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ===== BRAZOS (SOBRE PANCITA) =====
        glBindVertexArray(VAO_BROWN);
        // izquierdo
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.36f, 0.05f, 0.505f));
        M = glm::scale(M, glm::vec3(0.35f, 0.35f, 0.35f)); // mismo tamaño que hombros
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // derecho
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.36f, 0.05f, 0.505f));
        M = glm::scale(M, glm::vec3(0.35f, 0.35f, 0.35f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // ===== PIERNAS =====
        glBindVertexArray(VAO_BROWN);
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.38f, -1.05f, 0.05f));
        M = glm::scale(M, glm::vec3(0.25f, 0.26f, 0.30f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.38f, -1.05f, 0.05f));
        M = glm::scale(M, glm::vec3(0.25f, 0.26f, 0.30f));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    float moveStep = 0.02f;
    float rotStep = 0.1f;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movX += moveStep;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movX -= moveStep;
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) movY += moveStep;
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) movY -= moveStep;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movZ -= moveStep;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movZ += moveStep;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rot += rotStep;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rot -= rotStep;
}
