#include <raylib.h>

/*
 * Meow Cubes - A game where the main objective it to throw cubes at cats
 * Copyright (c) 2026 Donut Oreo Computer
 *
 * This software is licensed under the GNU General Public License v3; You can
 * edit, modify or distribute this source code. Check the LICENSE file for
 * more information.
 */

#define SCREEN_X GetScreenWidth()
#define SCREEN_Y GetScreenHeight()

int main(void) {
    InitWindow(1920, 1080, "Meow Cubes");
    SetTargetFPS(60);
    DisableCursor();

    // Initialize variables
    char *title = "Meow Cubes v0";
    Model kitty = LoadModel("assets/animal-cat.glb");
    Model grass = LoadModel("assets/grass.glb");
    
    Camera3D camera   = { 0 };
    camera.position   = (Vector3){ -2.0f, 1.0f, 2.0f };
    camera.target     = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up         = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Main loop
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // 3D Stuff
        BeginMode3D(camera);

        DrawModel(kitty, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, RAYWHITE);
        DrawModel(grass, (Vector3){0.0f, 0.0f, 0.0f}, 10.0f, RAYWHITE);
        DrawCube((Vector3){2.0f, 1.0f, 0.0f}, 2.0f, 2.0f, 2.0f, DARKBLUE);
        
        EndMode3D();

        // 2D UI
        int title_width = MeasureText(title, 32);
        DrawText(title, (SCREEN_X - title_width) / 2, 10, 32, RAYWHITE);
        EndDrawing();
    }

    UnloadModel(kitty);
    UnloadModel(grass);
    CloseWindow();
    return 0;
}
