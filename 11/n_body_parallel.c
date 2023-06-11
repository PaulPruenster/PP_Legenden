#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define G 1.0  // Gravitational constant
#define DT 1.0 // Time step

typedef struct {
  double x, y, z;    // Position
  double vx, vy, vz; // Velocity
  double mass;       // Mass
} Particle;

// Function to compute the force between two particles
void computeForce(Particle *p1, Particle *p2, double *fx, double *fy,
                  double *fz) {
  double dx = p2->x - p1->x;
  double dy = p2->y - p1->y;
  double dz = p2->z - p1->z;
  double distSquared = dx * dx + dy * dy + dz * dz;
  double force = G * p1->mass * p2->mass / distSquared;
  *fx = force * dx / sqrt(distSquared);
  *fy = force * dy / sqrt(distSquared);
  *fz = force * dz / sqrt(distSquared);
}

// Function to update the position and velocity of a particle
void updateParticle(Particle *p, double fx, double fy, double fz) {
  p->vx += fx / p->mass * DT;
  p->vy += fy / p->mass * DT;
  p->vz += fz / p->mass * DT;
  p->x += p->vx * DT;
  p->y += p->vy * DT;
  p->z += p->vz * DT;
}

// Function to perform the n-body simulation
void nBodySimulation(Particle *particles, int numParticles, int numSteps,
                     FILE *outputFile) {
  for (int step = 0; step < numSteps; step++) {

// Compute forces and update particles
#pragma omp for // private(fx, fy, fz) collapse(2)
    for (int i = 0; i < numParticles; i++) {
      double fx = 0.0, fy = 0.0, fz = 0.0;
      for (int j = 0; j < numParticles; j++) {
        if (i != j) {
          double dx, dy, dz;
          computeForce(&particles[i], &particles[j], &dx, &dy, &dz);
          fx += dx;
          fy += dy;
          fz += dz;
        }
      }
      // wenn mia des weggriagn kemma collapse mochn
      updateParticle(&particles[i], fx, fy, fz);
    }

    // Write particle data to file
    for (int i = 0; i < numParticles; i++) {
      fprintf(outputFile, "%.6f %.6f %.6f\n", particles[i].x, particles[i].y,
              particles[i].z);
    }
    fprintf(outputFile, "\n\n"); // Blank line to indicate end of time step
  }
}

int main() {
  srand(time(NULL)); // Initialize random seed

  int numParticles = 5000;
  int numSteps = 100;

  Particle *particles = malloc(numParticles * sizeof(Particle));

  // Generate random particles
  for (int i = 0; i < numParticles; i++) {
    particles[i].x = rand() / (double)RAND_MAX * 101.0 - 0.5;
    particles[i].y = rand() / (double)RAND_MAX * 101.0 - 0.5;
    particles[i].z = rand() / (double)RAND_MAX * 101.0 - 0.5;
    particles[i].vx = 0.0;
    particles[i].vy = 0.0;
    particles[i].vz = 0.0;
    particles[i].mass = 1.0;
  }

  FILE *outputFile = fopen("data.dat", "w");
  if (outputFile == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  double start_time = omp_get_wtime();
#pragma omp parallel
  { nBodySimulation(particles, numParticles, numSteps, outputFile); }
  double end_time = omp_get_wtime();
  double elapsed_time = end_time - start_time;
  printf("time = %f\n", elapsed_time);

  fclose(outputFile);
  free(particles);

  return 0;
}
