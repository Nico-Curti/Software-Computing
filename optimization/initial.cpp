#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#define MAGIC_NUMBER 42
#define N 1024
#define n_steps 100

struct particle
{
  float pos[3];
  float vel[3];
  float acc[3];
  float *pos2;
  float mass;
  particle()
  {
    pos[0] = 0.; pos[1] = 0.; pos[2] = 0.;
    vel[0] = 0.; vel[1] = 0.; vel[2] = 0.;
    acc[0] = 0.; acc[1] = 0.; acc[2] = 0.;
    mass   = 0.;
  }
};

void init(particle * particles)
{
  std::random_device rd;  //random number generator
  std::mt19937 gen(MAGIC_NUMBER);
  std::uniform_real_distribution<float> unif_d(0, 1.);

  for(int i = 0; i < N; ++i)
  {
    // initialize positions
    particles[i].pos[0] = unif_d(gen);
    particles[i].pos[1] = unif_d(gen);
    particles[i].pos[2] = unif_d(gen);

    // initialize velocity
    particles[i].vel[0] = unif_d(gen) * 1.0e-3;
    particles[i].vel[1] = unif_d(gen) * 1.0e-3;
    particles[i].vel[2] = unif_d(gen) * 1.0e-3;

    // initialize accelaration
    particles[i].acc[0] = 0.;
    particles[i].acc[1] = 0.;
    particles[i].acc[2] = 0.;

    // initialize masses
    particles[i].mass = N * unif_d(gen);
  }
}

float distance(const particle &p1, const particle &p2)
{
  return std::sqrt( std::pow(p1.pos[0] - p2.pos[0], 2) + std::pow(p1.pos[1] - p2.pos[1], 2) + std::pow(p1.pos[2] - p2.pos[2], 2) );
}


int main()
{
  float energy;
  float _kenergy;
  const float dt = 1e-3;
  particle *particles = new particle[N];
  const double G = 6.67259e-11;

  init(particles);

  double time = 0.;

  for (int s = 1; s <= n_steps; s++)
  {
    const auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)// update acceleration
      for (int j = 0; j < N; j++)
      {
        float dx, dy, dz;
        float distanceSqr = 0.0;
        float distanceInv = 0.0;

        dx = particles[j].pos[0] - particles[i].pos[0]; //1flop
        dy = particles[j].pos[1] - particles[i].pos[1]; //1flop
        dz = particles[j].pos[2] - particles[i].pos[2]; //1flop

        distanceSqr = distance(particles[i], particles[j]);
        distanceInv = 1.0 / distanceSqr;      //1div+1sqrt

        particles[i].acc[0] += dx * G * particles[j].mass * distanceInv * distanceInv * distanceInv;  //6flops
        particles[i].acc[1] += dy * G * particles[j].mass * distanceInv * distanceInv * distanceInv;  //6flops
        particles[i].acc[2] += dz * G * particles[j].mass * distanceInv * distanceInv * distanceInv;  //6flops

      }

    energy = 0;

    for (int i = 0; i < N; i++)// update position and velocity
    {
      particles[i].vel[0] += particles[i].acc[0] * dt;  //2flops
      particles[i].vel[1] += particles[i].acc[1] * dt;  //2flops
      particles[i].vel[2] += particles[i].acc[2] * dt;  //2flops

      particles[i].pos[0] += particles[i].vel[0] * dt;  //2flops
      particles[i].pos[1] += particles[i].vel[1] * dt;  //2flops
      particles[i].pos[2] += particles[i].vel[2] * dt;  //2flops

      particles[i].acc[0] = 0.;
      particles[i].acc[1] = 0.;
      particles[i].acc[2] = 0.;

      energy += particles[i].mass * ( particles[i].vel[0]*particles[i].vel[0] +
                                      particles[i].vel[1]*particles[i].vel[1] +
                                      particles[i].vel[2]*particles[i].vel[2]
                                    ); //7flops
    }

    _kenergy = 0.5 * energy;

    const auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
    time += std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

  } //end of the time step loop


  std::cout << std::endl;
  std::cout << "# Number of particles        : " << N              << std::endl;
  std::cout << "# Number of simulations      : " << n_steps        << std::endl;
  std::cout << "# Total Time (s)             : " << std::setprecision(3) << (time / 1e3)           << std::endl;
  std::cout << "# Average Time per iteration : " << std::setprecision(3) << (time / 1e3) / n_steps << std::endl;
  std::cout << std::endl;

  return 0;
}

