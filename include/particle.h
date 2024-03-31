#ifndef PARTICLE_H
#define PARTICLE_H

#include <raylib.h>
#include <stdlib.h>
#include <raymath.h>


typedef struct Particle
{
    Vector2 current_position;
    Vector2 next_position;
    Vector2 last_position;
    Vector2 velocity; // DONT USE THIS but were keeping it here for errors? fix later
    Vector2 acceleration;
    float mass;
    float radius;
    Color color;
    int cell_index_x;
    int cell_index_y;
    int idx;

} Particle;


void InitParticles(Particle *particles, int num_particles, int screen_width, int screen_height) {
    for (int i = 0; i < num_particles; i++) {
        particles[i].radius = 30.0f;
        particles[i].velocity = (Vector2){0, 0};
        particles[i].acceleration = (Vector2){0, 0};
        particles[i].mass = 1.0f;
        
        // Generate random position for the particle
        particles[i].current_position = (Vector2) {
            GetRandomValue(particles[i].radius, screen_width - particles[i].radius),
            GetRandomValue(particles[i].radius, screen_height - particles[i].radius)
        };
        
        // Check for overlaps with previously spawned particles
        for (int j = 0; j < i; j++) {
            Vector2 delta = Vector2Subtract(particles[i].current_position, particles[j].current_position);
            float distance = Vector2Length(delta);
            float radii_sum = particles[i].radius + particles[j].radius;
            
            // If there is an overlap, generate a new position for the particle
            while (distance < radii_sum) {
                particles[i].current_position = (Vector2) {
                    GetRandomValue(particles[i].radius, screen_width - particles[i].radius),
                    GetRandomValue(particles[i].radius, screen_height - particles[i].radius)
                };
                
                delta = Vector2Subtract(particles[i].current_position, particles[j].current_position);
                distance = Vector2Length(delta);
            }
        }
        
        particles[i].next_position = particles[i].current_position;
        particles[i].last_position = particles[i].current_position;
        particles[i].color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        particles[i].idx = i;
        particles[i].cell_index_x = 0;
        particles[i].cell_index_y = 0;
    }
}

void DrawParticle(Particle *particle)
{
    Color DEBUG_COLOR = GREEN;
    DEBUG_COLOR.a = 150;
    // white border around particles
    DrawCircleV(particle->last_position, particle->radius, DEBUG_COLOR);
    
    DrawCircleV(particle->current_position, particle->radius, RAYWHITE);
    DrawCircleV(particle->current_position, particle->radius - 
                (particle->radius * 0.05f), particle->color);
    // next position for debug
    

    // Draw particle number
    DrawText(TextFormat("%d", particle->idx), particle->current_position.x - 5, particle->current_position.y - 5, 10, RAYWHITE);

}


void DrawParticles(Particle *particles, int num_particles)
{
    for (int i = 0; i < num_particles; i++)
    {
        DrawParticle(&particles[i]);
    }
}







#endif // PARTICLE_H