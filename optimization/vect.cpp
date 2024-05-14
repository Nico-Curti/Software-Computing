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
  float mass;
  particle()
  {
    pos[0] = 0.f; pos[1] = 0.f; pos[2] = 0.f;
    vel[0] = 0.f; vel[1] = 0.f; vel[2] = 0.f;
    acc[0] = 0.f; acc[1] = 0.f; acc[2] = 0.f;
    mass   = 0.f;
  }
};


void init(particle * particles)
{
  std::random_device rd;  //random number generator
  std::mt19937 gen(MAGIC_NUMBER);
  std::uniform_real_distribution<float> unif_d(0.f, 1.f);

  for(int i = 0; i < N; ++i)
  {
    // initialize positions
    particles[i].pos[0] = unif_d(gen);
    particles[i].pos[1] = unif_d(gen);
    particles[i].pos[2] = unif_d(gen);

    // initialize velocity
    particles[i].vel[0] = unif_d(gen) * 1.0e-3f;
    particles[i].vel[1] = unif_d(gen) * 1.0e-3f;
    particles[i].vel[2] = unif_d(gen) * 1.0e-3f;

    // initialize accelaration
    particles[i].acc[0] = 0.f;
    particles[i].acc[1] = 0.f;
    particles[i].acc[2] = 0.f;

    // initialize masses
    particles[i].mass = N * unif_d(gen);
  }
}

struct
{
  float operator()(const float &dx, const float &dy, const float &dz)
  {
    return std::sqrt( dx * dx + dy * dy + dz * dz );
  }
} distance;

int main()
{
  float energy;
  float _kenergy;
  const float dt = 1e-3f;
  particle *particles = new particle[N];
  const float G = 6.67259e-11f;

  init(particles);

  double time = 0.;

  for (int s = 1; s <= n_steps; ++s)
  {
    const auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i)// update acceleration
      for (int j = 0; j < N; ++j)
      {
        float dx, dy, dz;
        float distanceSqr = 0.f;
        float distanceInv = 0.f;

        dx = particles[j].pos[0] - particles[i].pos[0]; //1flop
        dy = particles[j].pos[1] - particles[i].pos[1]; //1flop
        dz = particles[j].pos[2] - particles[i].pos[2]; //1flop

        distanceSqr = distance(dx, dy, dz);
        distanceInv = 1.f / distanceSqr;      //1div+1sqrt

        particles[i].acc[0] += dx * G * particles[j].mass * distanceInv * distanceInv * distanceInv;  //6flops
        particles[i].acc[1] += dy * G * particles[j].mass * distanceInv * distanceInv * distanceInv;  //6flops
        particles[i].acc[2] += dz * G * particles[j].mass * distanceInv * distanceInv * distanceInv;  //6flops

      }

    energy = 0.f;

    for (int i = 0; i < N; ++i)// update position and velocity
    {
      particles[i].vel[0] += particles[i].acc[0] * dt;  //2flops
      particles[i].vel[1] += particles[i].acc[1] * dt;  //2flops
      particles[i].vel[2] += particles[i].acc[2] * dt;  //2flops

      particles[i].pos[0] += particles[i].vel[0] * dt;  //2flops
      particles[i].pos[1] += particles[i].vel[1] * dt;  //2flops
      particles[i].pos[2] += particles[i].vel[2] * dt;  //2flops

      particles[i].acc[0] = 0.f;
      particles[i].acc[1] = 0.f;
      particles[i].acc[2] = 0.f;

      energy += particles[i].mass * ( particles[i].vel[0]*particles[i].vel[0] +
                                      particles[i].vel[1]*particles[i].vel[1] +
                                      particles[i].vel[2]*particles[i].vel[2]
                                    ); //7flops
    }

    _kenergy = 0.5f * energy;

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
