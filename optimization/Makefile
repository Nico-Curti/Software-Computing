
all: initial optimized vectorized soa
	@echo initial version   : ; ./bin/initial
	@echo optimization flag : ; ./bin/initial_optimized
	@echo vectorization     : ; ./bin/vectorized
	@echo AoS vs SoA        : ; ./bin/soa

initial: initial.cpp
	@mkdir -p bin
	$(CXX) -std=c++11 -O0 initial.cpp -o ./bin/initial

optimized: initial.cpp
	@mkdir -p bin
	$(CXX) -std=c++11 -O3 initial.cpp -o ./bin/initial_optimized

vectorized: vect.cpp
	@mkdir -p bin
	$(CXX) -std=c++11 -Ofast -mavx vect.cpp -o ./bin/vectorized

soa: soa.cpp
	@mkdir -p bin
	$(CXX) -std=c++11 -Ofast -mavx soa.cpp -o ./bin/soa

omp: omp.cpp
	@mkdir -p bin
	$(CXX) -std=c++11 -Ofast -mavx omp.cpp -o ./bin/omp -fopenmp
