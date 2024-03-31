#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

static Color font_color = { 225, 225, 225,  255 };
static float time_elapsed = 0.0f;

void DrawStartGui(int screen_width, int screen_height) {

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
    float gui_end_y = 300;
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
    DrawRectangleRounded(select_box_rect_1, 0.3f, 20, RED);
    
    DrawText("press space to start / stop simulation", text_spacing_x, text_spacing_y, start_font_size, font_color);
    DrawText("press r to reset simulation", text_spacing_x, text_spacing_y + 50, start_font_size, font_color);

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

void DrawSimGui(int screen_width, int screen_height) { 

    float dt = 1.0f/60.0f;
    int x_spacing = 20;
    int starting_y = 20;
    int y_spacing = 50;
    int running_font_size = 20;
    time_elapsed += dt;
    DrawText("particle engine v2", x_spacing, starting_y, running_font_size, font_color);
    DrawText("press 'r' to reset", x_spacing, starting_y + y_spacing, running_font_size, font_color);
    DrawText(TextFormat("dt: %.4f", dt), x_spacing, starting_y + y_spacing * 2, running_font_size, font_color);
    DrawText(TextFormat("time elapsed: %.4f", time_elapsed), x_spacing, starting_y + y_spacing * 3, running_font_size, font_color);
    DrawFPS(x_spacing, starting_y + y_spacing * 4);

}

void RecordSimInput(int* sim_is_running, int* sim_should_start, int* stage_mode)  {
    // reset simulation
    if (IsKeyPressed(KEY_TWO)){
        *stage_mode = 2;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;

    } else if (IsKeyPressed(KEY_ONE)){
        *stage_mode = 1;
        printf("stage mode: %d\n", *stage_mode);
        *sim_should_start = 2;
        *sim_is_running = 0;
    }
    if (IsKeyPressed(KEY_R) && *sim_is_running == 0) {
        printf("asked to reset sim\n");
        *sim_should_start = 2;
        *sim_is_running = 0;
    
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
}