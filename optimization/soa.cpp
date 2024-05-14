#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iomanip>

static constexpr int MAGIC_NUMBER = 42;
static constexpr int N = 1024;
static constexpr int n_steps = 100;

struct particleS
{
  float  *x,  *y,  *z,
        *vx, *vy, *vz,
        *ax, *ay, *az,
        *mass;
  particleS()
  {
    x  = new float[N];
    y  = new float[N];
    z  = new float[N];
    vx = new float[N];
    vy = new float[N];
    vz = new float[N];
    ax = new float[N];
    ay = new float[N];
    az = new float[N];
    mass = new float[N];
    std::fill_n(x, N, 0.f);
    std::fill_n(y, N, 0.f);
    std::fill_n(z, N, 0.f);
    std::fill_n(vx, N, 0.f);
    std::fill_n(vy, N, 0.f);
    std::fill_n(vz, N, 0.f);
    std::fill_n(ax, N, 0.f);
    std::fill_n(ay, N, 0.f);
    std::fill_n(az, N, 0.f);
    std::fill_n(mass, N, 0.f);
  }
  ~particleS()
  {
    delete[]  x;
    delete[]  y;
    delete[]  z;
    delete[] vx;
    delete[] vy;
    delete[] vz;
    delete[] ax;
    delete[] ay;
    delete[] az;
    delete[] mass;
  }
};


void init(particleS *particles)
{
  std::random_device rd;  //random number generator
  std::mt19937 gen(MAGIC_NUMBER);
  std::uniform_real_distribution<float> unif_d(0.f, 1.f);

  std::generate_n(particles->x,  N, [&](){return unif_d(gen);});
  std::generate_n(particles->y,  N, [&](){return unif_d(gen);});
  std::generate_n(particles->z,  N, [&](){return unif_d(gen);});
  std::generate_n(particles->vx, N, [&](){return unif_d(gen) * 1e-3f;});
  std::generate_n(particles->vy, N, [&](){return unif_d(gen) * 1e-3f;});
  std::generate_n(particles->vz, N, [&](){return unif_d(gen) * 1e-3f;});
  std::fill_n(    particles->ax, N, 0.f);
  std::fill_n(    particles->ay, N, 0.f);
  std::fill_n(    particles->az, N, 0.f);
  std::generate_n(particles->mass, N, [&](){return N * unif_d(gen);});
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
  const float G = 6.67259e-11f;

  particleS * particles = new particleS;

  init(particles);

  double time = 0.;
  float dx, dy, dz;
  float distanceInv;

  for (int s = 1; s <= n_steps; ++s)
  {
    const auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i)// update acceleration
      for (int j = 0; j < N; ++j)
      {
        dx = particles->x[j] - particles->x[i]; //1flop
        dy = particles->y[j] - particles->y[i]; //1flop
        dz = particles->z[j] - particles->z[i]; //1flop

        distanceInv = 1.f / std::sqrt(dx * dx + dy * dy + dz * dz);      //1div+1sqrt
        float pereppe = G * particles->mass[j] * distanceInv * distanceInv * distanceInv;
        particles->ax[i] += dx * pereppe;  //6flops
        particles->ay[i] += dy * pereppe;  //6flops
        particles->az[i] += dz * pereppe;  //6flops
      }

    energy = 0.f;

    for (int i = 0; i < N; ++i)// update position and velocity
    {
      particles->vx[i] += particles->ax[i] * dt;  //2flops
      particles->vy[i] += particles->ay[i] * dt;  //2flops
      particles->vz[i] += particles->az[i] * dt;  //2flops

      particles->x[i] += particles->vx[i] * dt;  //2flops
      particles->y[i] += particles->vy[i] * dt;  //2flops
      particles->z[i] += particles->vz[i] * dt;  //2flops

      particles->ax[i] = 0.f;
      particles->ay[i] = 0.f;
      particles->az[i] = 0.f;

      energy += particles->mass[i] * ( particles->vx[i] * particles->vx[i] +
                                       particles->vy[i] * particles->vy[i] +
                                       particles->vz[i] * particles->vz[i]
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
