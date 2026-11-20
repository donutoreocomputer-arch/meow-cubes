#include <raylib.h>
#include <raymath.h>
#include <stdbool.h> // Mabye just use int?

/*
 * Meow Cubes - A game where the main objective it to throw cubes at cats.
 * Copyright (c) 2026 Donut Oreo Computer
 *
 * This software is licensed under the GNU General Public License v3; You can
 * edit, modify or distribute this source code. Check the LICENSE file for
 * more information.
 */

#define SCREEN_X GetScreenWidth()
#define SCREEN_Y GetScreenHeight()

typedef struct {
    char *model;
    Vector3 position;
    Vector3 velocity; /* Fiziks! */
} MeowCube;

void check_fence_collision(Camera3D *camera) {
    if (camera->position.x < -15.5f) camera->position.x = -15.5f;
    if (camera->position.x > 15.5f ) camera->position.x = 15.5f;
    if (camera->position.z < -15.5f) camera->position.z = -15.5f;
    if (camera->position.z > 15.5f ) camera->position.z = 15.5f;
}

/* ...What the what? */
void throw_meowcube(MeowCube *cube, Vector3 direction, float force) {
    direction = Vector3Normalize(direction);
    cube->velocity = Vector3Scale(direction, force);
}

void update_meowcube(MeowCube *cube, Vector3 cat_position) {
    cube->position = Vector3Add(cube->position, Vector3Scale(cube->velocity, GetFrameTime()));
    if (CheckCollisionSpheres(cube->position, 0.5f, cat_position, 0.8f)) {
        cube->velocity = Vector3Zero(); /* If cube has hit cat, make velocity 0. */
    }

    if (cube->position.x < -15.5f) {
        cube->position.x = -15.5f;
        cube->velocity = Vector3Zero();
    } if (cube->position.x > 15.5f ) {
        cube->position.x = 15.5f;
        cube->velocity = Vector3Zero();
    } if (cube->position.z < -15.5f) {
        cube->position.z = -15.5f;
        cube->velocity = Vector3Zero();
    } if (cube->position.z > 15.5f ) {
        cube->position.z = 15.5f;
        cube->velocity = Vector3Zero();
    } if (cube->position.y < 0.5f) {
        cube->position.y = 0.5f;
        cube->velocity = Vector3Zero();
    }
}

int main(void) {
    InitWindow(1920, 1080, "Meow Cubes");
    SetTargetFPS(120); /* Do not remove, except if you want coil whine. */
    DisableCursor();

    /* Initialize variables */
    char *title = "Meow Cubes v0";
    bool got_cube = false;
    Vector3 cat_position = { 0.0f, 0.0f, 0.0f };

    Model kitty = LoadModel("assets/animal-cat.glb");
    Model grass = LoadModel("assets/grass.glb");
    Model fence = LoadModel("assets/fence.glb");
    MeowCube the_default = {
        .model = "5-Year-Old Sister's cube",
        .position = { -2.0f, 1.0f, 0.0f },
        .velocity = { 0.0f, 0.0f, 0.0f }
    };
    
    /* Set up camera */
    Camera3D camera   = { 0 };
    camera.position   = (Vector3){ -2.0f, 1.0f, 2.0f };
    camera.target     = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up         = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    /* Main loop */
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        check_fence_collision(&camera);
        BeginDrawing();
        ClearBackground(DARKGRAY);
        if (got_cube == true) {
            Vector3 direction = Vector3Subtract(camera.target,camera.position);
            direction = Vector3Normalize(direction);
            Vector3 offset = Vector3Scale(direction, 2.0f); 
            the_default.position = Vector3Add(camera.position, offset);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                throw_meowcube(&the_default, direction, 10.0f);
                got_cube = false;
            }
        } else {
            update_meowcube(&the_default, cat_position);

            /* FIXME: Make it check if the player is next to the square. */
            if (IsKeyPressed(KEY_E)) {
                got_cube = true;
            }
        }

        /* 3D Stuff */
        BeginMode3D(camera);

        DrawModel(kitty, cat_position, 1.0f, RAYWHITE);
        DrawModel(grass, (Vector3){0.0f, 0.0f, 0.0f}, 32.0f, RAYWHITE);
        DrawCube(the_default.position, 1.0f, 1.0f, 1.0f, VIOLET);
        for (int i = -16; i <= 16; i++) {
            DrawModel(fence, (Vector3){i, 0, -16}, 1, RAYWHITE);
            DrawModel(fence, (Vector3){i, 0, 16}, 1, RAYWHITE);
            DrawModelEx(fence,(Vector3){-16, 0, i}, (Vector3){0, 1, 0}, 90, (Vector3){1, 1, 1}, RAYWHITE);
            DrawModelEx(fence, (Vector3){16, 0, i}, (Vector3){0, 1, 0}, 90, (Vector3){1, 1, 1}, RAYWHITE);
        }
        
        EndMode3D();

        /* 2D UI */
        int title_width = MeasureText(title, 32);
        DrawText(title, (SCREEN_X - title_width) / 2, 10, 32, RAYWHITE);
        DrawFPS(10, 50);
        EndDrawing();
    }

    UnloadModel(kitty);
    UnloadModel(grass);
    UnloadModel(fence);
    CloseWindow();
    return 0;
}
