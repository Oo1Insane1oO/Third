LDFLAGS = -fopenmp -lpthread
CXXFLAGS = -g -std=c++11

main: random_number.cpp walker.cpp random_walk.cpp main.cpp
	g++ $(CXXFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm main
