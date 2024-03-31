#ifndef GRID_H
#define GRID_H

#include <raylib.h>
#include <stdio.h>
#include <particle.h>

// not sure if it would make it faster
// if i had a "particle index" but 
// at the same time its just a pointer 
// so it should be fine

typedef struct {
    int x;
    int y;
    Particle *particle; 
} GridCell;

typedef struct {
    int width;
    int height; // this should be the same as width
    int cell_size; // this should be diameter as well
    GridCell *cells;
} Grid;


void DrawCollisionGrid(float particle_radius, int screen_bounds_width, int screen_bounds_height)
{   
    // we are just expecting the particle_radius 
    // to be a whole number
    Color GRID_COLOR = (Color){200, 200, 200, 100};
    int particle_diameter = (int) particle_radius * 2;
    for (int i = 0; i < screen_bounds_width; i += particle_diameter)
    {
        DrawLine(i, 0, i, 900, GRID_COLOR);
    }

    for (int i = 0; i < 900; i += particle_diameter)
    {
        DrawLine(0, i, screen_bounds_height, i, GRID_COLOR);
    }
}



void ClearGrid(Grid *grid) {
    for (int i = 0; i < grid->width * grid->height; i++) {
        grid->cells[i].particle = NULL;
    }
}

void UpdateGrid(Grid* grid, Particle* particles, int num_particles) {
    
    ClearGrid(grid);

    for (int i = 0; i < num_particles; i++) {
        int cell_x = (int)(particles[i].current_position.x / grid->cell_size);
        int cell_y = (int)(particles[i].current_position.y / grid->cell_size);

        if (cell_x >= 0 && cell_x < grid->width && cell_y >= 0 && cell_y < grid->height) {
            int index = cell_y * grid->width + cell_x;
            grid->cells[index].particle = &particles[i];
        }
    }
}



#endif 