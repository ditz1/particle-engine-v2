#ifndef PARTICLE_H
#define PARTICLE_H

#include <raylib.h>
#include <stdlib.h>


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
    int idx;

} Particle;


void InitParticles(Particle *particles, int num_particles, int screen_width, int screen_height)
{
    for (int i = 0; i < num_particles; i++)
    {
        particles[i].radius = 30.0f;
        particles[i].velocity = (Vector2){0, 0};
        particles[i].acceleration = (Vector2){0, 0};
        particles[i].mass = 20.0f;
        particles[i].current_position = (Vector2) {
                                                GetRandomValue(particles[0].radius + 10.0f, screen_width - particles[0].radius - 10.0f), 
                                                GetRandomValue(particles[0].radius + 10.0f, screen_height - particles[0].radius - 10.0f) };
        particles[i].next_position = particles[i].current_position;
        particles[i].last_position = particles[i].current_position;
        // this breaks if below 1
        // make sure mass is above 1
        particles[i].color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        particles[i].idx = i;
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