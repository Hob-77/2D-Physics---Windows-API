#pragma once
#include <glad/glad.h>
#include "Vec2.h"

class SimpleRenderer {
public:
    SimpleRenderer();
    ~SimpleRenderer();

    void Initialize();
    void SetProjection(float left, float right, float bottom, float top);
    void DrawRectangle(const Vec2& position, const Vec2& size, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    void DrawWireframeRectangle(const Vec2& position, const Vec2& size, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;
    int projectionLoc, modelLoc, colorLoc;

    void CreateShaders();
    void CreateGeometry();

    // Vertex shader source
    const char* vertexShaderSource = R"(
        #version 460 core
        layout (location = 0) in vec2 aPos;
        
        uniform mat4 projection;
        uniform mat4 model;
        
        void main() {
            gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
        }
    )";

    // Fragment shader source
    const char* fragmentShaderSource = R"(
        #version 460 core
        out vec4 FragColor;
        
        uniform vec4 color;
        
        void main() {
            FragColor = color;
        }
    )";
};