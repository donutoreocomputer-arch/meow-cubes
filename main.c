#include <raylib.h>

/* Compile with:
 * clang -std=c23 -Wall -Wextra -Wpedantic -Werror -o cats main.c -lraylib
 * I'll add a Makefile later.
 */

#define SCREEN_X GetScreenWidth()
#define SCREEN_Y GetScreenHeight()

int main(void) {
    InitWindow(1920, 1080, "Meow Cubes");
    SetTargetFPS(60);

    // Initialize variables
    char *title = "Meow Cubes !ALPHA!";
    Model kitty = LoadModel("assets/kitty.glb");
    Model grass = LoadModel("assets/grass.glb");
    
    Camera3D camera   = { 0 };
    camera.position   = (Vector3){ 0.0f, 3.0f, 4.0f };
    camera.target     = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up         = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // 3D Stuff
        BeginMode3D(camera);
        DrawModel(kitty, (Vector3){0.0f, 0.2f, 0.0f}, 1.0f, WHITE);
        DrawModel(grass, (Vector3){0, 0, 0}, 3.0f, WHITE);
        EndMode3D();

        // 2D UI
        int title_width = MeasureText(title, 32);
        DrawText(title, (SCREEN_X - title_width) / 2, 10, 32, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
