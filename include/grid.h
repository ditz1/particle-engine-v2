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
    PARTICLE_COLOR.a = 80;
    
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
                float x_start = cell_center.x - grid->cell_size / 2;
                float y_start = cell_center.y - grid->cell_size / 2;
                Vector2 start = {x_start, y_start};
                DrawRectangleV(start, (Vector2) {grid->cell_size, grid->cell_size}, PARTICLE_COLOR);

            }
        }
    }
}

void DrawCollisionGridKahuna(float particle_radius, int screen_bounds_width, int screen_bounds_height, Grid* grid) {
    Color GRID_COLOR = (Color){200, 200, 200, 100};
    for (int i = 0; i < screen_bounds_width; i += grid->cell_size) {
        DrawLine(i, 0, i, screen_bounds_height, GRID_COLOR);
    }
    for (int i = 0; i < screen_bounds_height; i += grid->cell_size) {
        DrawLine(0, i, screen_bounds_width, i, GRID_COLOR);
    }

    Color SMALL_PARTICLE_COLOR = RED;
    Color BIG_PARTICLE_COLOR = BLUE;
    SMALL_PARTICLE_COLOR.a = 80;
    BIG_PARTICLE_COLOR.a = 80;
    float small_circle_radius = particle_radius * 0.25f;
    float big_circle_radius = particle_radius * 0.5f;

    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            int index = y * grid->width + x;
            GridCell cell = grid->cells[index];
            for (int i = 0; i < cell.particle_count; i++) {
                Particle* particle = cell.particles[i];
                Vector2 cell_center = { (float)(x * grid->cell_size + grid->cell_size / 2), (float)(y * grid->cell_size + grid->cell_size / 2) };

                if (particle->idx == 0) {
                    // Draw a larger circle for the big particle
                    float x_start = cell_center.x - grid->cell_size / 2;
                    float y_start = cell_center.y - grid->cell_size / 2;
                    Vector2 start = {x_start, y_start};
                    DrawRectangleV(start, (Vector2) {grid->cell_size, grid->cell_size}, SMALL_PARTICLE_COLOR);
                } else {
                    // Draw a smaller circle for the smaller particles
                    float x_start = cell_center.x - grid->cell_size / 2;
                    float y_start = cell_center.y - grid->cell_size / 2;
                    Vector2 start = {x_start, y_start};
                    DrawRectangleV(start, (Vector2) {grid->cell_size, grid->cell_size}, BIG_PARTICLE_COLOR);
                }
            }
        }
    }
}

void DrawCollisionGridMeteors(float particle_radius, int screen_bounds_width, int screen_bounds_height, Grid* grid) {
    Color GRID_COLOR = (Color){200, 200, 200, 100};
    for (int i = 0; i < screen_bounds_width; i += grid->cell_size) {
        DrawLine(i, 0, i, screen_bounds_height, GRID_COLOR);
    }
    for (int i = 0; i < screen_bounds_height; i += grid->cell_size) {
        DrawLine(0, i, screen_bounds_width, i, GRID_COLOR);
    }

    Color REGULAR_PARTICLE_COLOR = GREEN;
    Color METEOR_PARTICLE_COLOR = RED;
    METEOR_PARTICLE_COLOR.a = 80;
    REGULAR_PARTICLE_COLOR.a = 80;
    float regular_circle_radius = particle_radius * 0.25f;
    float meteor_circle_radius = particle_radius * 0.5f;

    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            int index = y * grid->width + x;
            GridCell cell = grid->cells[index];
            for (int i = 0; i < cell.particle_count; i++) {
                Particle* particle = cell.particles[i];
                Vector2 cell_center = { (float)(x * grid->cell_size + grid->cell_size / 2), (float)(y * grid->cell_size + grid->cell_size / 2) };

                if (particle->idx >= 0 && particle->idx < 20) {
                    // Draw a larger circle for the big particle
                    float x_start = cell_center.x - grid->cell_size / 2;
                    float y_start = cell_center.y - grid->cell_size / 2;
                    Vector2 start = {x_start, y_start};
                    DrawRectangleV(start, (Vector2) {grid->cell_size, grid->cell_size}, REGULAR_PARTICLE_COLOR);
                } else {
                    // Draw a smaller circle for the smaller particles
                    float x_start = cell_center.x - grid->cell_size / 2;
                    float y_start = cell_center.y - grid->cell_size / 2;
                    Vector2 start = {x_start, y_start};
                    DrawRectangleV(start, (Vector2) {grid->cell_size, grid->cell_size}, METEOR_PARTICLE_COLOR);
                }
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

void UpdateGridKahuna(Grid* grid, Particle* particles, int num_particles) {
    ClearGrid(grid);

    // Handle the big particle separately
    Particle* bigParticle = &particles[0];
    int bigParticleRadius = (int)bigParticle->radius;
    int bigParticleCellX = (int)(bigParticle->current_position.x / grid->cell_size);
    int bigParticleCellY = (int)(bigParticle->current_position.y / grid->cell_size);

    // Calculate the range of cells the big particle occupies
    int startX = bigParticleCellX - bigParticleRadius / grid->cell_size;
    int endX = bigParticleCellX + bigParticleRadius / grid->cell_size;
    int startY = bigParticleCellY - bigParticleRadius / grid->cell_size;
    int endY = bigParticleCellY + bigParticleRadius / grid->cell_size;

    // Update the grid cells for the big particle
    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            if (x >= 0 && x < grid->width && y >= 0 && y < grid->height) {
                int index = y * grid->width + x;
                GridCell* cell = &grid->cells[index];
                if (cell->particle_count < MAX_PARTICLES_PER_CELL) {
                    cell->particles[cell->particle_count] = bigParticle;
                    cell->particle_count++;
                }
            }
        }
    }

    // Update the grid for the remaining particles
    for (int i = 1; i < num_particles; i++) {
        int cell_x = (int)(particles[i].current_position.x / grid->cell_size);
        int cell_y = (int)(particles[i].current_position.y / grid->cell_size);
        if (cell_x >= 0 && cell_x < grid->width && cell_y >= 0 && cell_y < grid->height) {
            int index = cell_y * grid->width + cell_x;
            GridCell* cell = &grid->cells[index];
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

void UpdateGridMeteors(Grid* grid, Particle* particles, int num_particles, int num_meteors) {
    ClearGrid(grid);

    for (int i = 0; i < num_meteors; i++) {
        Particle* meteorParticle = &particles[i];
        int meteorParticleRadius = (int)meteorParticle->radius;
        int meteorParticleCellX = (int)(meteorParticle->current_position.x / grid->cell_size);
        int meteorParticleCellY = (int)(meteorParticle->current_position.y / grid->cell_size);

        // Calculate the range of cells the meteor particle occupies
        int startX = meteorParticleCellX - meteorParticleRadius / grid->cell_size;
        int endX = meteorParticleCellX + meteorParticleRadius / grid->cell_size;
        int startY = meteorParticleCellY - meteorParticleRadius / grid->cell_size;
        int endY = meteorParticleCellY + meteorParticleRadius / grid->cell_size;

        // Update the grid cells for the meteor particle
        for (int y = startY; y <= endY; y++) {
            for (int x = startX; x <= endX; x++) {
                if (x >= 0 && x < grid->width && y >= 0 && y < grid->height) {
                    int index = y * grid->width + x;
                    GridCell* cell = &grid->cells[index];
                    if (cell->particle_count < MAX_PARTICLES_PER_CELL) {
                        cell->particles[cell->particle_count] = meteorParticle;
                        cell->particle_count++;
                    }
                }
            }
        }
    }

    // Update the grid for regular particles (indices 20 and above)
    for (int i = num_meteors; i < num_particles; i++) {
        int cell_x = (int)(particles[i].current_position.x / grid->cell_size);
        int cell_y = (int)(particles[i].current_position.y / grid->cell_size);
        if (cell_x >= 0 && cell_x < grid->width && cell_y >= 0 && cell_y < grid->height) {
            int index = cell_y * grid->width + cell_x;
            GridCell* cell = &grid->cells[index];
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
