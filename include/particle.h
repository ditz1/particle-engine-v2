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


void InitParticles(Particle *particles, int num_particles, int screen_width, int screen_height, int mode) {
    float dt = 1.0f/120.0f;
    float particle_radius = 9.0f;
    float particle_mass = 1.0f;
    float rand_num_1 = GetRandomValue(180, 255);
    printf("rand_num_1: %f\n", rand_num_1);
    float rand_num_2 = GetRandomValue(180, 255);
    printf("rand_num_2: %f\n", rand_num_2);
    switch (mode){
        case 1: {
        for (int i = 0; i < num_particles; i++) {
            particles[i].radius = particle_radius * 1.2;
            particles[i].velocity = (Vector2){0, 0};
            particles[i].acceleration = (Vector2){0, 0};
            particles[i].mass = particle_mass;        
            particles[i].current_position = (Vector2) {
                GetRandomValue(particles[i].radius, screen_width - particles[i].radius),
                GetRandomValue(particles[i].radius, screen_height - particles[i].radius)
            };        
            for (int j = 0; j < i; j++) {
                Vector2 delta = Vector2Subtract(particles[i].current_position, particles[j].current_position);
                float distance = Vector2Length(delta);
                float radii_sum = particles[i].radius + particles[j].radius;            
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
            /*float t = (float)i / (num_particles - 1);
        particles[i].color = (Color){
            (unsigned char)(255 * t),
            0,
            (unsigned char)(255 * (1 - t)),
            255
        };*/
        break;
    } case 2: {
        for (int i = 0; i < num_particles; i++) {
            float circle_center_x = screen_width / 2.0f;
            float circle_center_y = screen_height / 2.0f;
            Vector2 circle_center = (Vector2) {circle_center_x, circle_center_y};
            float circle_radius =  400.0f;
            particles[i].radius = particle_radius * 1.2;
            particles[i].velocity = (Vector2){0, 0};
            particles[i].acceleration = (Vector2){0, 0};
            particles[i].mass = particle_mass;        
            float angle = GetRandomValue(0, 360);
            float radius = GetRandomValue(0, circle_radius);
            particles[i].current_position = (Vector2) {circle_center_x + radius * cos(angle), circle_center_y + radius * sin(angle)};       
            for (int j = 0; j < i; j++) {
                Vector2 delta = Vector2Subtract(particles[i].current_position, particles[j].current_position);
                float distance = Vector2Length(delta);
                float radii_sum = particles[i].radius + particles[j].radius;            
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
        break; 
    
    } case 3: {
        printf("particle stream activated\n");
        for (int i = 0; i < num_particles; i++) {
            particles[i].radius = particle_radius;
            particles[i].velocity = (Vector2){0, 0};
            particles[i].acceleration = (Vector2){GetRandomValue(10, 20), GetRandomValue(7, 13)};
            particles[i].mass = particle_mass;        
            particles[i].current_position = (Vector2) { screen_width / 2, (-i * 30.0f) };        
            particles[i].next_position = particles[i].current_position;
            particles[i].last_position = particles[i].current_position;
            particles[i].color = (Color){GetRandomValue(150, 255),  GetRandomValue(0, 120) , GetRandomValue(150, 255), 255};
            particles[i].idx = i;
            particles[i].cell_index_x = 0;
            particles[i].cell_index_y = 0;
        }
        break;
    } case 4: {
        printf("particle stream activated\n");
        
        for (int i = 0; i < num_particles; i++) {
            
            float particle_offset = i * 2 * PI / num_particles;
            particles[i].radius = particle_radius * 0.8f;
            particles[i].velocity = (Vector2){0, 0};
            particles[i].acceleration = (Vector2){GetRandomValue(128, 255), (GetRandomValue(-1, 1))};
            particles[i].mass = particle_mass;
            if (i > 2000 && i < 4000) {
                particles[i].current_position = (Vector2){ 700, -25.0f * (i-999)};
            } else if (i < 2000) {
                particles[i].current_position = (Vector2){ 100, -25.0f * i};
            } else if (i > 4000)  {
                particles[i].current_position = (Vector2){ 400, -25.0f * (i-1999)};
            }      
            particles[i].next_position = particles[i].current_position;
            particles[i].last_position = particles[i].current_position;
            particles[i].color = (Color){GetRandomValue(0, rand_num_1),  GetRandomValue(0, 20) , GetRandomValue(0, rand_num_2), 255};
            particles[i].idx = i;
            particles[i].cell_index_x = 0;
            particles[i].cell_index_y = 0;
        }
        break;
    } case 5: {
        printf("particle stream activated\n");
        float amplitude = 350.0f;
        float center = 450.0f;
        float freq = 8.0f;
        for (int i = 0; i < num_particles; i++) {
            float phase_offset = (float)i/num_particles * 2 * PI;
            float wave_position = sinf(freq * dt + phase_offset);
            float new_x = center + wave_position * amplitude;
            //printf("new x: %f\n", new_x);
            particles[i].radius = particle_radius * 0.7f;
            particles[i].velocity = (Vector2){0, 0};
            particles[i].acceleration = (Vector2){0, 0};
            particles[i].mass = particle_mass;
            particles[i].current_position = (Vector2){ new_x + particles[i].radius, -12.0f * i};      
            particles[i].next_position = particles[i].current_position;
            particles[i].last_position = particles[i].current_position;
            particles[i].color = (Color){GetRandomValue(0, 0),  GetRandomValue(0, rand_num_1) , GetRandomValue(0, rand_num_2), 255};
            particles[i].idx = i;
            particles[i].cell_index_x = 0;
            particles[i].cell_index_y = 0;
        }
        break;
    } case 6: {
        printf("particle stream activated\n");
        float amplitude = 350.0f;
        float center = 450.0f;
        float freq = 28.0f;
        for (int i = 0; i < num_particles; i++) {
            float phase_offset = (float)i/num_particles * 2 * PI;
            float wave_position = sinf(freq * dt + phase_offset);
            float new_x = center + wave_position * amplitude;
            particles[i].radius = particle_radius * 0.5f;
            particles[i].velocity = (Vector2){0, 0};
            particles[i].acceleration = (Vector2){0, 0};
            particles[i].mass = particle_mass;
            particles[i].current_position = (Vector2){ new_x, -15.0f * i};      
            particles[i].next_position = particles[i].current_position;
            particles[i].last_position = particles[i].current_position;
            particles[i].color = (Color){GetRandomValue(150, 255),  GetRandomValue(90, 180) , GetRandomValue(0, 30), 255};
            particles[i].idx = i;
            particles[i].cell_index_x = 0;
            particles[i].cell_index_y = 0;
        
            }
        break;
        }
    }
}

void DrawParticle(Particle *particle) {
    //Color DEBUG_COLOR = GREEN;
    //DEBUG_COLOR.a = 150;
    // white border around particles
    //DrawCircleV(particle->last_position, particle->radius, DEBUG_COLOR);
    
    DrawCircleV(particle->current_position, particle->radius, particle->color);
    //DrawCircleV(particle->current_position, particle->radius - 
    //            (particle->radius * 0.05f), particle->color);
    // next position for debug
    

    // Draw particle number
    //DrawText(TextFormat("%d", particle->idx), particle->current_position.x - 5, particle->current_position.y - 5, 10, RAYWHITE);

}


void DrawParticles(Particle *particles, int num_particles)
{
    for (int i = 0; i < num_particles; i++)
    {
        DrawParticle(&particles[i]);
    }
}







#endif // PARTICLE_H
