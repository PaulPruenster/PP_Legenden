#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GRAVITATIONAL_CONSTANT 1.0
#define NUM_PARTICLES 500
#define TIMESTEPS 100

typedef struct {
    double x, y, z; // Position
    double vx, vy, vz; // Velocity
    double mass; // Mass
} Particle;

double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

void compute_force(Particle* particles, int num_particles) {
    for (int i = 0; i < num_particles; i++) {
        double ax = 0.0, ay = 0.0, az = 0.0;
        for (int j = 0; j < num_particles; j++) {
            if (i != j) {
                double dx = particles[j].x - particles[i].x;
                double dy = particles[j].y - particles[i].y;
                double dz = particles[j].z - particles[i].z;
                double r = distance(particles[i].x, particles[i].y, particles[i].z,
                                    particles[j].x, particles[j].y, particles[j].z);
                double force = GRAVITATIONAL_CONSTANT * particles[i].mass * particles[j].mass / (r * r * r);

                ax += force * dx;
                ay += force * dy;
                az += force * dz;
            }
        }

        particles[i].vx += ax / particles[i].mass;
        particles[i].vy += ay / particles[i].mass;
        particles[i].vz += az / particles[i].mass;
    }
}

void move_particles(Particle* particles, int num_particles) {
    for (int i = 0; i < num_particles; i++) {
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
        particles[i].z += particles[i].vz;
    }
}

int main() {
    srand(time(NULL));

    Particle particles[NUM_PARTICLES];

    // Initialize particles with random positions, velocities, and masses
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x = random_double(0.0, 100.0);
        particles[i].y = random_double(0.0, 100.0);
        particles[i].z = random_double(0.0, 100.0);
        particles[i].vx = random_double(-1.0, 1.0);
        particles[i].vy = random_double(-1.0, 1.0);
        particles[i].vz = random_double(-1.0, 1.0);
        particles[i].mass = random_double(1.0, 10.0);
    }

    for (int t = 0; t < TIMESTEPS; t++) {
        compute_force(particles, NUM_PARTICLES);
        move_particles(particles, NUM_PARTICLES);

        for (int i = 0; i < NUM_PARTICLES; i++) {
            printf("%f, %f, %f\n", particles[i].x, particles[i].y, particles[i].z);
        }
        printf("\n\n");
    }


    return 0;
}
