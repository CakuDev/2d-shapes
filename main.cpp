#include <iostream>

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

int main(int argc, char* argv[]) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    rlImGuiSetup(true);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawText("Congrats! You created your first window!", 190, 200, 32, LIGHTGRAY);

            rlImGuiBegin();

            if (ImGui::Button("ImGui button", ImVec2{100.0f, 100.0f}))
            {
                std::cout << "Button pressed!!!" << std::endl;
            }

            rlImGuiEnd();

            EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rlImGuiShutdown();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}