#include <random>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <omp.h>
#define NUM_THREADS omp_get_max_threads()

using namespace std;

int main()
{
  random_device rd;
  mt19937 eng{rd()};
  size_t i, I, N = 1e5, N_run = 1e4, Nhits = 0;
  long double x, y, res, pi = 0, pi_tmp = 0;
  long double start_time, run_time;
  std::uniform_real_distribution<long double> uniform_dist{-1., 1.};

  omp_set_num_threads(NUM_THREADS);
  
  start_time = omp_get_wtime();
  #pragma omp parallel private(I, Nhits)
  {
    #pragma omp for reduction(+:pi_tmp)
    for(I = 0; I < N_run; ++I)
    {
      Nhits = 0;
      #pragma omp parallel private(i, x, y, res)
      {
        #pragma omp for reduction(+:Nhits)
        for(i = 0; i < N; ++i)
        {
          x = uniform_dist(eng);
          y = uniform_dist(eng);
          res = x*x + y*y;
          if(res < 1)
            Nhits += 1;
        }
      }
      pi_tmp += (4.0 * ((long double)Nhits/(long double)N));
    }
  }
  
  pi = pi_tmp / N_run;
  run_time = omp_get_wtime() - start_time;
  std::cout << "\n pi with " << N << " steps for " << N_run << " runs is " << std::setprecision(16) << pi << " in " << run_time << " sec" << std::endl;

  return 0;
}   
