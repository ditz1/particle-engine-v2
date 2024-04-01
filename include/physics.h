#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <raymath.h>
#include <particle.h>
#include <grid.h>
#include <stdio.h>

static const float restitution = 0.2f;
static const float dampening = 0.98f;
static const float gravity = 250.0f;

void BoundParticles(Particle *particles, int num_particles, int bounds_width, int bounds_height, int mode) {
    
    float bounce_factor = -1 * Clamp(((1.0f / particles[0].mass)), 0.1f, 0.8f);
    switch (mode) {
    case 9:
    case 8:
    case 7:
    case 6:
    case 5:
    case 4:
    case 3: {
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
            } 
            /*else if (dist_to_top < particles[i].radius) {
                particles[i].current_position.y = particles[i].radius;
            }*/
        }
        break;
    }
    case 1: {
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
        break;
    } case 2: {
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
        break;
    }
    }
}



void UpdateParticleGravity(Particle *p, float dt) {
    if (p->current_position.y + p->radius >= 900) {
        p->current_position.y = 900 - p->radius;
        p->velocity.y *= -restitution;
        p->velocity.y *= dampening;
    } else {
        p->acceleration.y += gravity; 
    }
}


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
    //substep
    
    for (int i = 0; i < num_particles; i++) {
        UpdateParticle(&particles[i], dt);
    }
}

void CheckCellCollisions(Particle* p1, Particle* p2, float dt) {
    if (p1 && p2 && p1 != p2) {
        Vector2 delta = Vector2Subtract(p1->current_position, p2->current_position);
        float distance = Vector2Length(delta);
        float radii_sum = p1->radius + p2->radius;
        
        if (distance < radii_sum) {
            float penetration_depth = radii_sum - distance;
            Vector2 collision_normal = Vector2Scale(delta, 1.0f / distance);
            
            float max_penetration = 1.1f * (p1->radius + p2->radius);
            penetration_depth = fminf(penetration_depth, max_penetration);

            //substep            
            int max_iterations = 8;
            float iteration_factor = 1.0f / max_iterations;
            
            for (int i = 0; i < max_iterations; i++) {
                float correction_magnitude = penetration_depth * iteration_factor;
                Vector2 correction = Vector2Scale(collision_normal, correction_magnitude);
                
                p1->current_position = Vector2Add(p1->current_position, Vector2Scale(correction, p2->mass / (p1->mass + p2->mass)));
                p2->current_position = Vector2Subtract(p2->current_position, Vector2Scale(correction, p1->mass / (p1->mass + p2->mass)));
                
                delta = Vector2Subtract(p1->current_position, p2->current_position);
                distance = Vector2Length(delta);
                penetration_depth = fminf(radii_sum - distance, max_penetration);
            }
            
            float elasticity = 0.8f;
            Vector2 relative_velocity = Vector2Subtract(p1->velocity, p2->velocity);
            float velocity_along_normal = Vector2DotProduct(relative_velocity, collision_normal);
            
            if (velocity_along_normal > 0) return;
            
            float p1_speed = Vector2Length(p1->velocity);
            float p2_speed = Vector2Length(p2->velocity);
            float rest_threshold = 0.2f;
            
            if (p1_speed < rest_threshold || p2_speed < rest_threshold) {
                elasticity *= 0.9f;
            }
            
            float impulse_magnitude = -(1 + elasticity) * velocity_along_normal;
            impulse_magnitude /= p1->mass + p2->mass;
            
            // Limit the maximum impulse magnitude
            float max_impulse = 3.0f;
            impulse_magnitude = fminf(impulse_magnitude, max_impulse);
            
            Vector2 impulse = Vector2Scale(collision_normal, impulse_magnitude);
            p1->velocity = Vector2Add(p1->velocity, Vector2Scale(impulse, 1 / p1->mass));
            p2->velocity = Vector2Subtract(p2->velocity, Vector2Scale(impulse, 1 / p2->mass));
            float vel_cap = 10.0f;
            if (p1->velocity.x > vel_cap) {
                p1->velocity.x = vel_cap;
            }
            if (p1->velocity.y > vel_cap) {
                p1->velocity.y = vel_cap;
            }
            if (p2->velocity.x > vel_cap) {
                p2->velocity.x = vel_cap;
            }
            if (p2->velocity.y > vel_cap) {
                p2->velocity.y = vel_cap;
            }
        }
    }
}



void FindCollisionsGrid(Grid* grid, float dt) {
    for (int x = 0; x < grid->width; ++x) {
        for (int y = 0; y < grid->height; ++y) {
            GridCell current_cell = grid->cells[y * grid->width + x];
            
            for (int i = 0; i < current_cell.particle_count; i++) {
                Particle* p1 = current_cell.particles[i];
                
                // Check collisions with particles in the same cell
                for (int j = i + 1; j < current_cell.particle_count; j++) {
                    Particle* p2 = current_cell.particles[j];
                    CheckCellCollisions(p1, p2, dt);
                }
                
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        
                        int adj_x = x + dx;
                        int adj_y = y + dy;
                        
                        if (adj_x >= 0 && adj_x < grid->width && adj_y >= 0 && adj_y < grid->height) {
                            GridCell adjacent_cell = grid->cells[adj_y * grid->width + adj_x];
                            
                            for (int k = 0; k < adjacent_cell.particle_count; k++) {
                                Particle* p2 = adjacent_cell.particles[k];
                                CheckCellCollisions(p1, p2, dt);
                            }
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
                CheckCellCollisions(&particles[i], &particles[j], (1.0f/60.0f));
            }
        }
    }
}





#endif // PHYSICS_H
