CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic -O2 -g

benchmark:
	$(CXX) $(CXXFLAGS) -o fib_benchmark fib.cpp fib_benchmark.cpp -isystem benchmark/include -lpthread -lbenchmark $(LDFLAGS)

test:
	$(CXX) $(CXXFLAGS) -o fib_test fib.cpp fib_test.cpp  -lgtest $(LDFLAGS)

fib: fib.o
	$(CXX) $(CXXFLAGS) -o fib fib.cpp $(LDFLAGS)

plot: benchmark
	./fib_benchmark --benchmark_out_format=json --benchmark_out=benchmark.json
	python3 ../utils/plot.py -f benchmark.json


clean:
	rm -f fib fib_test fib_benchmark *.o *.out *.gch *.csv