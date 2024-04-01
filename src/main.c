#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <grid.h>
#include <particle.h>
#include <gui.h>
#include <physics.h>


// we will figure out the math later
// but we need to use multiples of 3 and 9

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900


int main(void)
{   
    //little bit lighter than 0, 0, 0
    Color sim_background_color = BLACK;
    sim_background_color.a = 255;
    sim_background_color.r = 30;
    sim_background_color.g = 30;
    sim_background_color.b = 30;

    // mode 0 = debug
    // mode 1 = release
    int sim_mode = 0;
    // stage_mode 1 = screen bounds
    // stage_mode 2 = sphere bounds
    // stage_mode 3 = rect bounds
    int stage_mode = 1;

    // will do debug as default for now
    int num_particles = 500;
    Particle* particles_in_scene = (Particle *)malloc(num_particles * sizeof(Particle));

    const int sim_screen_bounds_width = 900;
    const int sim_screen_bounds_height = 900;

    // fix this
    // if (stage_mode == 3) {
    //     sim_screen_bounds_width = 600;
    //     sim_screen_bounds_height = 600;
    // }

    int next_action = 0;
    int sim_is_running = 0;
    int sim_should_start = 1;
    int debug_mode = 0;

    // sphere bounds
    float sphere_bounds_radius = 300.0f;
    Vector2 bounds_center = (Vector2){sim_screen_bounds_width / 2.0f, sim_screen_bounds_height / 2.0f};



    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "particle engine v2");
    const float dt = 1.0f / 120.0f;
    float time_elapsed = 0.0f;
    SetTargetFPS(300);               

    // add some function to do all this so we can reset the simulation
    // "init_simulation" or something

    InitParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
    int cell_size = (int)particles_in_scene[0].radius * 2; // diameter
    int grid_width = sim_screen_bounds_width / cell_size;
    int grid_height = sim_screen_bounds_height / cell_size;
    Grid grid = {
        .width = grid_width,
        .height = grid_height,
        .cell_size = cell_size,
        .cells = (GridCell *)calloc(grid_width * grid_height, sizeof(GridCell)) // calloc initializes to 0
    };

    
    int scene_is_loading = 0;

    while (!WindowShouldClose())   
    {

        if (stage_mode == 1) {
            num_particles = 500;
        } else if (stage_mode == 2) {
            num_particles = 350;
        } else if (stage_mode == 3) {
            num_particles = 3000;
        } else if (stage_mode == 4) {
            num_particles = 6000;
        } else if (stage_mode == 5) {
            num_particles = 8000;
        } else if (stage_mode == 6) {
            num_particles = 12000;
        } else if (stage_mode == 7) {
            num_particles = 800 + 1;
        } else if (stage_mode == 8) {
            num_particles = 3500 + 20;
        } else if (stage_mode == 9) {
            num_particles = 4000 + 40;
        }

        if (sim_should_start == 2) {
            time_elapsed = 0.0f;
            free(particles_in_scene);
            printf("freed particles\n");
            if ((particles_in_scene = (Particle *)malloc(num_particles * sizeof(Particle))) != NULL) {
                printf("allocated new particles\n");
                scene_is_loading = 1;
                InitParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                //update grid
                int cell_size = (int)particles_in_scene[0].radius * 2;
                if (stage_mode == 7){
                    cell_size = (int)particles_in_scene[1].radius * 2;
                } else if (stage_mode == 8){
                    cell_size = (int)particles_in_scene[21].radius * 2;
                } else if (stage_mode == 9){
                    cell_size = (int)particles_in_scene[41].radius * 2;
                }
                int grid_width = sim_screen_bounds_width / cell_size;
                int grid_height = sim_screen_bounds_height / cell_size;
                free(grid.cells);
                grid.width = grid_width;
                grid.height = grid_height;
                grid.cell_size = cell_size;
                grid.cells = (GridCell *)calloc(grid_width * grid_height, sizeof(GridCell));
                printf("reset grid\n");
                sim_should_start = 1;
                printf("resetting simulation...\n");
                scene_is_loading = 0;
            } else {
                printf("failed to allocate new particles\n");
                break;
            }
        }
        
        // BoundParticles(particles_in_scene, num_particles, screen_width, screen_height);
        // UpdateParticles(particles_in_scene, num_particles, dt);
        //printf("sim_is_running: %d\n sim_should_start: %d\n", sim_is_running, sim_should_start);
        
        if (sim_is_running) {
            switch (stage_mode) {
                case 1: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;    
                }
                case 2: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 3: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 4: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 5: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 6: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 7: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 8: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
                case 9: {
                    BoundParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height, stage_mode);
                    break;
                }
            }

            //ResolveCollisions(&grid, particles_in_scene, num_particles, dt);
            if (stage_mode == 7){
                UpdateGridKahuna(&grid, particles_in_scene, num_particles);
            } else if (stage_mode == 8){
                UpdateGridMeteors(&grid, particles_in_scene, num_particles, 20);
            } else if (stage_mode == 9){
                UpdateGridMeteors(&grid, particles_in_scene, num_particles, 40);
            } else {
                UpdateGrid(&grid, particles_in_scene, num_particles);
            }
            FindCollisionsGrid(&grid, dt);
            //BruteForceCollisions(particles_in_scene, num_particles);
            UpdateParticles(particles_in_scene, num_particles, dt);
        }
        // both false means reset
        // have to figure out how to manage this memory because we 
        // should probably free the memory when we reset the simulation
        /*
        if (!sim_is_running && !sim_should_start) {
            InitParticles(particles_in_scene, num_particles, sim_screen_bounds_width, sim_screen_bounds_height);
        }
        */
       //printf("particle radius %f\n", particles_in_scene[0].radius);
        BeginDrawing();
            
            ClearBackground(sim_background_color);
            RecordSimInput(&sim_is_running, &sim_should_start, &stage_mode, &debug_mode);

            if (!sim_is_running && sim_should_start){
                DrawStartGui(SCREEN_WIDTH, SCREEN_HEIGHT, stage_mode, scene_is_loading);
            } else if (sim_is_running) {
                DrawParticleBounds(stage_mode, sim_screen_bounds_width, sim_screen_bounds_height);
                DrawParticles(particles_in_scene, num_particles);
                DrawSimGui(SCREEN_WIDTH, SCREEN_HEIGHT, num_particles, stage_mode, sim_is_running, sim_should_start);

                if (debug_mode == 1) {
                    if (stage_mode == 7){
                        DrawCollisionGridKahuna(particles_in_scene[1].radius, sim_screen_bounds_width, sim_screen_bounds_height, &grid);                          
                    } else if (stage_mode == 8) {
                        DrawCollisionGridMeteors(particles_in_scene[20].radius, sim_screen_bounds_width, sim_screen_bounds_height, &grid);
                    } else if (stage_mode == 9) {
                        DrawCollisionGridMeteors(particles_in_scene[40].radius, sim_screen_bounds_width, sim_screen_bounds_height, &grid);
                    } else {
                        DrawCollisionGrid(particles_in_scene[0].radius, sim_screen_bounds_width, sim_screen_bounds_height, &grid);
                    }
                }
            }
            
            
        

            
                
        EndDrawing();



        // if (next_action != 0) {
        //     printf("next action: %d\n", next_action);
        // }
            
    }

    free(particles_in_scene);
    free(grid.cells);
    CloseWindow();


    return 0;
}


