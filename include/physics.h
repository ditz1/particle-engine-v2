#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <raymath.h>
#include <particle.h>
#include <grid.h>
#include <stdio.h>

static const float restitution = 0.5f;
static const float dampening = 0.98f;
static const float gravity = 200.0f;

void BoundParticles(Particle *particles, int num_particles, int bounds_width, int bounds_height, int mode) {
    
    float bounce_factor = -1 * Clamp(((1.0f / particles[0].mass)), 0.1f, 0.8f);

    if (mode == 1){
        for (int i = 0; i < num_particles; i++) {
            float dist_to_left = particles[i].current_position.x;
            float dist_to_right = bounds_width - particles[i].current_position.x; 
            float dist_to_bottom = bounds_height - particles[i].current_position.y;
            float dist_to_top = particles[i].current_position.y;
            if (dist_to_left < particles[i].radius) {
                particles[i].current_position.x = particles[i].radius;
            } else if (dist_to_right < particles[i].radius) {
                particles[i].current_position.x = bounds_width - particles[i].radius;
            } else if (dist_to_bottom < particles[i].radius) {
                particles[i].current_position.y = bounds_height - particles[i].radius;
            } else if (dist_to_top < particles[i].radius) {
                particles[i].current_position.y = particles[i].radius;
            }
        }
    } else if (mode == 2) {
        float circle_center_x = bounds_width / 2.0f;
        float circle_center_y = bounds_height / 2.0f;
        Vector2 circle_center = (Vector2) {circle_center_x, circle_center_y};
        float circle_radius =  400.0f;
        for (int i = 0; i < num_particles; i++) {
            const float distance = Vector2Distance(particles[i].current_position, circle_center);
            if (distance > circle_radius - particles[i].radius){
                const Vector2 dir = Vector2Subtract(particles[i].current_position, circle_center);
                const Vector2 norm = Vector2Normalize(dir); 
                particles[i].current_position = Vector2Add(circle_center, Vector2Scale(norm, circle_radius - particles[i].radius));

                Vector2 tangent = (Vector2){ -norm.y, norm.x };
                float dot = Vector2DotProduct(particles[i].velocity, tangent);
                particles[i].velocity = Vector2Scale(tangent, dot);
            }
        }
    }
}

/*
void BoundParticles(Particle *particles, int num_particles, int screen_width, int screen_height) {
    for (int i = 0; i < num_particles; i++) {
        float bounce_factor = -1 * Clamp(((1.0f / particles[i].mass)), 0.1f, 0.8f);
        particles[i].current_position.x = Clamp(particles[i].current_position.x, particles[i].radius, screen_width - particles[i].radius);
        particles[i].current_position.y = Clamp(particles[i].current_position.y, particles[i].radius, screen_height - particles[i].radius);
        if (particles[i].current_position.x <= particles[i].radius || particles[i].current_position.x >= screen_width - particles[i].radius) {
            Vector2 velocity = Vector2Subtract(particles[i].current_position, particles[i].last_position);
            velocity.x *= -1 * bounce_factor;
            particles[i].last_position = Vector2Subtract(particles[i].current_position, velocity);
        }

        if (particles[i].current_position.y <= particles[i].radius || particles[i].current_position.y >= screen_height - particles[i].radius) {
            Vector2 velocity = Vector2Subtract(particles[i].current_position, particles[i].last_position);
            velocity.y *= -1 * bounce_factor;
            particles[i].last_position = Vector2Subtract(particles[i].current_position, velocity);
        }
    }
}*/

// maybe we want a gravity constant so it moves faster
void UpdateParticleGravity(Particle *p, float dt) {
    p->acceleration.y += gravity; 

}
/* the worst update particle scheme
void UpdateParticle(Particle* p, float dt) {

    p->last_position = p->current_position;
    UpdateParticleGravity(p, dt);
    
    Vector2 velocity = Vector2Subtract(p->next_position, p->last_position);
    
    
    if (velocity.x > 50.0f) {
        velocity.x = 50.0f;
    }
    if (velocity.y > 50.0f) {
        velocity.y = 50.0f;
    }
    p->next_position = Vector2Add(p->last_position, Vector2Scale(velocity, dt));
    p->current_position = p->next_position;
    p->current_position = p->next_position;

}
*/

void UpdateParticle(Particle* p, float dt) {

    UpdateParticleGravity(p, dt);
    Vector2 velocity = (Vector2) {0, 0};
    velocity.x = p->current_position.x - p->last_position.x;
    velocity.y = p->current_position.y - p->last_position.y;
    
    p->last_position.x = p->current_position.x;
    p->last_position.y = p->current_position.y;
    
    p->current_position.x += (velocity.x  + (p->acceleration.x * dt * dt));
    p->current_position.y += (velocity.y  + (p->acceleration.y * dt * dt)); 

    p->acceleration.x = 0.0f;
    p->acceleration.y = 0.0f;
}


void UpdateParticles(Particle *particles, int num_particles, float dt) {
    for (int i = 0; i < num_particles; i++) {
        UpdateParticle(&particles[i], dt);
    }
}

void CheckCellCollisions(Particle* p1, Particle* p2) {
    if (p1 && p2 && p1 != p2) {
        Vector2 delta = Vector2Subtract(p1->current_position, p2->current_position);
        float distance = Vector2Length(delta);
        float overlap = p1->radius + p2->radius - distance;

        if (overlap > 0) {
            // Collision detected, resolve the collision
            Vector2 normal = Vector2Normalize(delta);
            Vector2 separation = Vector2Scale(normal, overlap);

            // Apply separation to the particles' positions
            p1->current_position = Vector2Add(p1->current_position, Vector2Scale(separation, 0.5f));
            p2->current_position = Vector2Subtract(p2->current_position, Vector2Scale(separation, 0.5f));

            // Calculate the relative velocity
            Vector2 relativeVelocity = Vector2Subtract(p1->velocity, p2->velocity);

            // Calculate the impulse magnitude
            float impulseMagnitude = Vector2DotProduct(relativeVelocity, normal) / (1.0f / p1->mass + 1.0f / p2->mass);

            // Apply the impulse to the particles' velocities
            p1->velocity = Vector2Subtract(p1->velocity, Vector2Scale(normal, impulseMagnitude / p1->mass));
            p2->velocity = Vector2Add(p2->velocity, Vector2Scale(normal, impulseMagnitude / p2->mass));
        }
    }
}

void FindCollisionsGrid(Grid* grid) {
    for (int x = 1; x < grid->width - 1; ++x) {
        for (int y = 1; y < grid->height - 1; ++y) {
            GridCell current_cell = grid->cells[y * grid->width + x];
            // iterate on surrounding particles
            if (current_cell.particle != NULL) {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        GridCell other_cell = grid->cells[(y + dy) * grid->width + (x + dx)];
                        if (other_cell.particle) {
                            CheckCellCollisions(current_cell.particle, other_cell.particle);
                        }
                    }
                }
            }
        }
    }
}


void BruteForceCollisions(Particle* particles, int num_particles) {
    for (int i = 0; i < num_particles; i++) {
        for (int j = i + 1; j < num_particles; j++) {
            if (particles[i].current_position.x + particles[i].radius > particles[j].current_position.x - particles[j].radius &&
                particles[i].current_position.x - particles[i].radius < particles[j].current_position.x + particles[j].radius &&
                particles[i].current_position.y + particles[i].radius > particles[j].current_position.y - particles[j].radius &&
                particles[i].current_position.y - particles[i].radius < particles[j].current_position.y + particles[j].radius) {
                CheckCellCollisions(&particles[i], &particles[j]);
            }
        }
    }
}


/*
void ResolveCollisions(Grid* grid, Particle* particles, int num_particles, float dt) {
    
    int num_substeps = 8;
    float substep_dt = dt / num_substeps;
    
    // maybe substeps will improve stability
    // but will definitely slow down the simulation
    for (int substep = 0; substep < num_substeps; substep++) {
        for (int i = 0; i < num_particles; i++) { // all particles
            // get index of grid cell with particles
            int cell_x = (int)(particles[i].current_position.x / grid->cell_size);
            int cell_y = (int)(particles[i].current_position.y / grid->cell_size);

            // check all cells adjacent
            for (int y = cell_y - 1; y <= cell_y + 1; y++) {
                for (int x = cell_x - 1; x <= cell_x + 1; x++) {
                    // if next cell is within bounds
                    if (x >= 1 && x < grid->width - 1 && y >= 1 && y < grid->height - 1) {
                        int index = y * grid->width + x;
                        // next cell idx
                        Particle* other = grid->cells[index].particle;

                        if (other && other != &particles[i]) {
                            Vector2 delta = Vector2Subtract(particles[i].current_position, other->current_position);
                            float distance = Vector2Length(delta);
                            float overlap = particles[i].radius + other->radius - distance;

                            if (overlap > 0) {
                                Vector2 direction = Vector2Normalize(delta);
                                float separation_distance = particles[i].radius + other->radius;
                                Vector2 separation = Vector2Scale(direction, separation_distance);

                                // Check if the next_position will remain positive after applying the separation
                                if (particles[i].next_position.x + separation.x >= 0 && particles[i].next_position.y + separation.y >= 0) {
                                    particles[i].next_position = Vector2Add(particles[i].next_position, separation);
                                }
                                if (other->next_position.x - separation.x >= 0 && other->next_position.y - separation.y >= 0) {
                                    other->next_position = Vector2Subtract(other->next_position, separation);
                                }
                            }
                        }                       
                    }
                }
            }
        }
    }
}
*/


#endif // PHYSICS_H
