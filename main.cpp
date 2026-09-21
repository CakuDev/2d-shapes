#include <string>
#include <vector>

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

struct Circle
{
    std::string name = "Circle";
    float scale = 1.0f;
    float velocity[2] = { 1.0f, 1.0f };
    float position[2] = { 200.0f, 200.0f };
    float color[3] = { 1.0f, 0.0f, 0.0f };
    int radius = 100;
    bool is_drawn = true;
};

Color convertColor(float color[3])
{
    return Color
    { 
        static_cast<unsigned char>(color[0] * 255.0f), 
        static_cast<unsigned char>(color[1] * 255.0f), 
        static_cast<unsigned char>(color[2] * 255.0f), 
        255 
    };
}

void moveCircle(Circle& circle, int screenWidth, int screenHeight) {
    circle.position[0] += circle.velocity[0];
    circle.position[1] += circle.velocity[1];
    
    // SCREEN BORDER CHECKS
    // Horizontal check
    if (circle.position[0] - circle.radius * circle.scale <= 0)
    {
        circle.velocity[0] = -circle.velocity[0];
        circle.position[0] = 0 + circle.radius * circle.scale;
    } 
    else if (circle.position[0] + circle.radius * circle.scale >= screenWidth) {
        circle.velocity[0] = -circle.velocity[0];
        circle.position[0] = screenWidth - circle.radius * circle.scale;
    }
    
    // Vertical check
    if (circle.position[1] - circle.radius * circle.scale <= 0)
    {
        circle.velocity[1] = -circle.velocity[1];
        circle.position[1] = 0 + circle.radius * circle.scale;
    } 
    else if (circle.position[1] + circle.radius * circle.scale >= screenHeight)
    {
        circle.velocity[1] = -circle.velocity[1];
        circle.position[1] = screenHeight - circle.radius * circle.scale;
    }
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
    Circle circle;
    int selectedShapeIndex = 0;
    std::vector<const char*> shapeNames = { circle.name.c_str() };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        
        moveCircle(circle, screenWidth, screenHeight);
        
        if (circle.is_drawn)
        {
            DrawCircle(circle.position[0], circle.position[1], circle.radius * circle.scale, convertColor(circle.color));
            int textWidth = MeasureText(circle.name.c_str(), fontSize); 
            DrawText(circle.name.c_str(), circle.position[0] - textWidth / 2, circle.position[1] - fontSize / 2 , fontSize, WHITE);
        }

        rlImGuiBegin();

        ImGui::Begin("Shape property");
        ImGui::Combo("Shape", &selectedShapeIndex, shapeNames.data(), static_cast<int>(shapeNames.size()));
        ImGui::Checkbox("Draw Shape", &circle.is_drawn);
        ImGui::SliderFloat("Scale", &circle.scale, 0.0f, 3.0f);
        ImGui::SliderFloat2("Velocity", circle.velocity, -4.0f, 4.0f);
        ImGui::ColorEdit3("Color", circle.color);
        if (ImGui::InputText("Name", &circle.name))
        {
            shapeNames[selectedShapeIndex] = circle.name.c_str();
        }
        ImGui::End();

        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}