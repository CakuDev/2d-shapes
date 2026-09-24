#include <string>
#include <vector>

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

struct Shape
{
    std::string name = "Shape";
    float scale = 1.0f;
    float velocity[2] = { 1.0f, 1.0f };
    float position[2] = { 200.0f, 200.0f };
    float color[3] = { 1.0f, 0.0f, 0.0f };
    int width = 100;
    int height = 100;
    bool is_drawn = true;
    enum : char { CIRCLE } type = CIRCLE;
};

Color convertColor(const float color[3])
{
    return Color
    { 
        static_cast<unsigned char>(color[0] * 255.0f), 
        static_cast<unsigned char>(color[1] * 255.0f), 
        static_cast<unsigned char>(color[2] * 255.0f), 
        255 
    };
}

void moveShape(Shape& shape, int screenWidth, int screenHeight) {
    shape.position[0] += shape.velocity[0];
    shape.position[1] += shape.velocity[1];
    
    // SCREEN BORDER CHECKS
    // Horizontal check
    if (shape.position[0] - shape.width * shape.scale <= 0)
    {
        shape.velocity[0] = -shape.velocity[0];
        shape.position[0] = 0 + shape.width * shape.scale;
    } 
    else if (shape.position[0] + shape.width * shape.scale >= screenWidth) {
        shape.velocity[0] = -shape.velocity[0];
        shape.position[0] = screenWidth - shape.width * shape.scale;
    }
    
    // Vertical check
    if (shape.position[1] - shape.height * shape.scale <= 0)
    {
        shape.velocity[1] = -shape.velocity[1];
        shape.position[1] = 0 + shape.height * shape.scale;
    } 
    else if (shape.position[1] + shape.height * shape.scale >= screenHeight)
    {
        shape.velocity[1] = -shape.velocity[1];
        shape.position[1] = screenHeight - shape.height * shape.scale;
    }
}

void renderShape(const Shape& shape, int fontSize)
{
    if (!shape.is_drawn)
    {
        return;
    }
    DrawCircle(shape.position[0], shape.position[1], shape.width * shape.scale, convertColor(shape.color));
    int textWidth = MeasureText(shape.name.c_str(), fontSize); 
    DrawText(shape.name.c_str(), shape.position[0] - textWidth / 2, shape.position[1] - fontSize / 2 , fontSize, WHITE);
}

int main(int argc, char* argv[])
{
    // CONFIG PARAMS
    const char* windowName = "2D Shapes";
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const float mainScale = 2.0f;
    const int targetFPS = 144;
    const int fontSize = 32;

    // CONFIG
    InitWindow(screenWidth, screenHeight, windowName);
    SetTargetFPS(targetFPS);
    rlImGuiSetup(true);
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(mainScale);
    style.FontScaleDpi = mainScale;
    
    // APP STATE
    Shape shape;
    int selectedShapeIndex = 0;
    std::vector<const char*> shapeNames = { shape.name.c_str() };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        
        moveShape(shape, screenWidth, screenHeight);
        renderShape(shape, fontSize);

        rlImGuiBegin();

        ImGui::Begin("Shape property");
        ImGui::Combo("Shape", &selectedShapeIndex, shapeNames.data(), static_cast<int>(shapeNames.size()));
        ImGui::Checkbox("Draw Shape", &shape.is_drawn);
        ImGui::SliderFloat("Scale", &shape.scale, 0.0f, 3.0f);
        ImGui::SliderFloat2("Velocity", shape.velocity, -4.0f, 4.0f);
        ImGui::ColorEdit3("Color", shape.color);
        if (ImGui::InputText("Name", &shape.name))
        {
            shapeNames[selectedShapeIndex] = shape.name.c_str();
        }
        ImGui::End();

        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}