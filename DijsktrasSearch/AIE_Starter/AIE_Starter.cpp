#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1100;
    int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000000000000");
    asciiMap.push_back("0111111111110001111110");
    asciiMap.push_back("0111011011010111001010");
    asciiMap.push_back("0101111001011100111010");
    asciiMap.push_back("0110011011100100001010");
    asciiMap.push_back("0111111011011111101010");
    asciiMap.push_back("0101001011110100111110");
    asciiMap.push_back("0101111011110110000010");
    asciiMap.push_back("0101111111111111110010");
    asciiMap.push_back("0100111100110111010110");
    asciiMap.push_back("0111101111110111011110");
    asciiMap.push_back("0101101100001111100110");
    asciiMap.push_back("0111001111111111111110");
    asciiMap.push_back("0000000000000000000000");

    NodeMap nodeMap;
    nodeMap.Initialise(asciiMap, 50);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(20, 12);
    nodeMap.path = nodeMap.AStarSearch(start, end);


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(0)) {
            Vector2 mousePos = GetMousePosition();
            start = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            nodeMap.path = nodeMap.AStarSearch(start, end);
        }
        if (IsMouseButtonPressed(1)) {
            Vector2 mousePos = GetMousePosition();
            end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            nodeMap.path = nodeMap.AStarSearch(start, end);
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        nodeMap.Draw();
        nodeMap.DrawPath();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}