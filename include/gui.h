#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

static Color font_color = { 225, 225, 225,  255 };
static float time_elapsed = 0.0f;

void DrawStartGui(int screen_width, int screen_height, int stage_mode, int loading) {

    font_color.a = 255;
    font_color.r = 230;
    font_color.g = 230;
    font_color.b = 230;
    Color gui_color = PURPLE;
    gui_color.r -= 50;
    gui_color.g -= 50;    
    float center_x = screen_width / 2.0f;
    float center_y = screen_height / 2.0f;
    int start_font_size = 26;
    float gui_start_x = center_x - 300;
    float gui_start_y = center_y - 300;
    float gui_end_x = 600;
    float gui_end_y = 450;
    int text_spacing_x = gui_start_x + 20;
    int text_spacing_y = gui_start_y + 40;

    /*typedef struct Rectangle {
    float x;                // Rectangle top-left corner position x
    float y;                // Rectangle top-left corner position y
    float width;            // Rectangle width
    float height;           // Rectangle height
    } Rectangle;*/

    Rectangle gui_rect = {gui_start_x, gui_start_y, gui_end_x, gui_end_y};
    Rectangle select_box_rect_1 = {gui_end_x + 80, text_spacing_y, 30, 30};
//void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);

    DrawRectangleRounded(gui_rect, 0.3f, 20, gui_color);
    
    
    DrawText("press space to start / stop simulation", text_spacing_x, text_spacing_y, start_font_size, font_color);
    DrawText("press r to reset simulation", text_spacing_x, text_spacing_y + 50, start_font_size, font_color);
    DrawText("press 1 for screen bounds", text_spacing_x, text_spacing_y + 100, start_font_size, font_color);
    DrawText("press 2 for sphere bounds", text_spacing_x, text_spacing_y + 150, start_font_size, font_color);
    DrawText("press 3 for rect bounds", text_spacing_x, text_spacing_y + 200, start_font_size, font_color);
    DrawText("press 4 for lots of particles", text_spacing_x, text_spacing_y + 250, start_font_size, font_color);
    DrawText("press 5 for even more particles (will lag)", text_spacing_x, text_spacing_y + 300, start_font_size, font_color);
    DrawText(TextFormat("selected mode: %d", stage_mode), text_spacing_x + 30, text_spacing_y + 350, start_font_size, font_color);
    if (loading == 1) {
        DrawText("loading...", text_spacing_x + 30, text_spacing_y + 450, start_font_size, RAYWHITE);
    }
}


void DrawParticleBounds(int mode, int bounds_width, int bound_height){
    if (mode == 2)
    {
        Color circlecolor = RAYWHITE;
        circlecolor.a = 100;
        int circle_center_x = bounds_width / 2;
        int circle_center_y = bound_height / 2;
        Vector2 circle_center = (Vector2){circle_center_x, circle_center_y};
        int circle_radius = 400;
        DrawCircleV(circle_center, circle_radius, circlecolor);  
    }
}

void DrawSimGui(int screen_width, int screen_height, int num_particles, int mode, int sim_is_running, int sim_should_start) { 

    float dt = 1.0f/60.0f;
    int x_spacing = 20;
    int starting_y = 20;
    int y_spacing = 30;
    int running_font_size = 18;
    time_elapsed += dt;
    Rectangle gui_rect = {5, 5, 225, 240};
    DrawRectangleRounded(gui_rect, 0.3f, 20, GRAY);
    DrawText("particle engine v2", x_spacing, starting_y, running_font_size, font_color);
    DrawText("press 'r' to reset", x_spacing, starting_y + y_spacing, running_font_size, font_color);
    DrawText(TextFormat("dt: %.4f", dt), x_spacing, starting_y + y_spacing * 2, running_font_size, font_color);
    DrawText(TextFormat("time elapsed: %.4f", time_elapsed), x_spacing, starting_y + y_spacing * 3, running_font_size, font_color);
    DrawText(TextFormat("num particles: %d", num_particles), x_spacing, starting_y + y_spacing * 4, running_font_size, font_color);
    DrawText(TextFormat("stage mode: %d", mode), x_spacing, starting_y + y_spacing * 5, running_font_size, font_color);
    DrawFPS(x_spacing, starting_y + y_spacing * 6);

}

void RecordSimInput(int* sim_is_running, int* sim_should_start, int* stage_mode, int* debug_mode)  {
    // reset simulation
    if (IsKeyPressed(KEY_TWO)){
        *stage_mode = 2;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;

    } else if (IsKeyPressed(KEY_ONE)){
        *stage_mode = 1;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;

    } else if (IsKeyPressed(KEY_THREE)){
        *stage_mode = 3;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;

    } else if (IsKeyPressed(KEY_FOUR)){
        *stage_mode = 4;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;

    } else if (IsKeyPressed(KEY_FIVE)){
        *stage_mode = 5;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;

    } else if (IsKeyPressed(KEY_SIX)){
        *stage_mode = 6;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;

    }
    if (IsKeyPressed(KEY_R) && *sim_is_running == 0) {
        printf("asked to reset sim\n");
        *sim_should_start = 2;
        *sim_is_running = 0;
        time_elapsed = 0.0f;
    
    } else if (IsKeyPressed(KEY_SPACE)) {
        printf("start/stop simulation\n");
        if (*sim_is_running == 1 && *sim_should_start == 0) {
            *sim_is_running = 0;
            *sim_should_start = 1;

        } else if (*sim_is_running == 0 && *sim_should_start == 1){
            *sim_is_running = 1;
            *sim_should_start = 0;
        }
    }

    if (IsKeyPressed(KEY_D)) {
        if (*debug_mode == 1) {
            *debug_mode = 0;
            printf("debug mode off\n");
        } else {
            *debug_mode = 1;
            printf("debug mode on\n");
        }
    }
}