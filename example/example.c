#include "raylib.h"

#define RAYLIBVIDEO_IMPL
#include <raylibvideo.h>

#define MAX_COLUMNS 5

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    ray_video_t video = ray_video_open("bjork-all-is-full-of-love.mpeg");

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int font_scale = 2;
    #define UI(X) (X * font_scale)

    InitWindow(screenWidth, screenHeight, "raylib [core] example - video playback");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Generates some random columns
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 4);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }

    SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        // update Video
        ray_video_update(&video, GetFrameTime());
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground

                // Draw some cubes around
                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                }

                // Draw Video as Billboard
                if(video.ok)
                {
                    DrawCubeTexture(video.texture, (Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                    DrawCubeTexture(video.texture, (Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                    DrawCubeTexture(video.texture, (Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
                    DrawBillboard(camera, video.texture, (Vector3){0,10,-30}, 20, WHITE);
                }

            EndMode3D();

            DrawRectangle     ( UI(10), UI(10), UI(220), UI(80), Fade(SKYBLUE, 0.8f));
            DrawRectangleLines( UI(10), UI(10), UI(220), UI(80), BLUE);

            DrawText(TextFormat("RAYLIB VIDEO EXAMPLE (%.1f FPS)", 1.0f / GetFrameTime()), UI(20), UI(20), UI(10), BLACK);
            DrawText("- Move with keys: W, A, S, D", UI(40), UI(30), UI(10), BLACK);
            DrawText("- Mouse move to look around", UI(40), UI(50), UI(10), BLACK);
            DrawText("- Exit with Escape key", UI(40), UI(70), UI(10), BLACK);
            if(!video.ok) DrawText("COULDN'T FIND THE VIDEO! \nYou must download the example file first. \nDouble click download_video_example.bat in the examples folder.", UI(10), UI(100), UI(10), RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    ray_video_destroy(&video);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}