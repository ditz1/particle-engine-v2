#ifndef GRID_H
#define GRID_H

#include <raylib.h>
#include <stdio.h>
#include <particle.h>

#define MAX_PARTICLES_PER_CELL 8

// not sure if it would make it faster
// if i had a "particle index" but 
// at the same time its just a pointer 
// so it should be fine

typedef struct {
    int x;
    int y;
    Particle *particles[MAX_PARTICLES_PER_CELL]; 
    int particle_count;
} GridCell;

typedef struct {
    int width;
    int height; // this should be the same as width
    int cell_size; // this should be diameter as well
    GridCell *cells;
} Grid;


void DrawCollisionGrid(float particle_radius, int screen_bounds_width, int screen_bounds_height, Grid* grid) {
    Color GRID_COLOR = (Color){200, 200, 200, 100};
    
    for (int i = 0; i < screen_bounds_width; i += grid->cell_size) {
        DrawLine(i, 0, i, screen_bounds_height, GRID_COLOR);
    }
    
    for (int i = 0; i < screen_bounds_height; i += grid->cell_size) {
        DrawLine(0, i, screen_bounds_width, i, GRID_COLOR);
    }
    
    Color PARTICLE_COLOR = RED;
    
    float circle_radius = particle_radius * 0.25f;
    
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            int index = y * grid->width + x;
            GridCell cell = grid->cells[index];
            
            for (int i = 0; i < cell.particle_count; i++) {
                Particle* particle = cell.particles[i];
                Vector2 cell_center = {
                    (float)(x * grid->cell_size + grid->cell_size / 2),
                    (float)(y * grid->cell_size + grid->cell_size / 2)
                };
                DrawCircleV(cell_center, circle_radius, PARTICLE_COLOR);
            }
        }
    }
    
}



void ClearGrid(Grid *grid) {
    for (int i = 0; i < grid->width * grid->height; i++) {
        grid->cells[i].particle_count = 0;
    }
}

void UpdateGrid(Grid* grid, Particle* particles, int num_particles) {
    ClearGrid(grid);
    
    for (int i = 0; i < num_particles; i++) {
        int cell_x = (int)(particles[i].current_position.x / grid->cell_size);
        int cell_y = (int)(particles[i].current_position.y / grid->cell_size);
        
        if (cell_x >= 0 && cell_x < grid->width && cell_y >= 0 && cell_y < grid->height) {
            int index = cell_y * grid->width + cell_x;
            GridCell *cell = &grid->cells[index];
            
            if (cell->particle_count < MAX_PARTICLES_PER_CELL) {
                cell->particles[cell->particle_count] = &particles[i];
                cell->particle_count++;
                particles[i].cell_index_x = cell_x;
                particles[i].cell_index_y = cell_y;
            }
        } else {
            particles[i].cell_index_x = -1;
            particles[i].cell_index_y = -1;
        }
    }
}

#endif 