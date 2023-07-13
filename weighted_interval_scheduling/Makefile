CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic -O2 -g

benchmark:
	$(CXX) $(CXXFLAGS) -o wis_benchmark wis.cpp wis_benchmark.cpp -isystem benchmark/include -lpthread -lbenchmark $(LDFLAGS)

test:
	$(CXX) $(CXXFLAGS) -o wis_test wis.cpp wis_test.cpp  -lgtest $(LDFLAGS)

fib: fib.o
	$(CXX) $(CXXFLAGS) -o wis wis.cpp $(LDFLAGS)

plot: benchmark
	./wis_benchmark --benchmark_out_format=json --benchmark_out=benchmark.json
	python3 ../utils/plot.py -f benchmark.json

clean:
	rm -f wis wis_test wis_benchmark *.o *.out *.gch *.csv