CXXFLAGS = -Wall -std=c++14
TEST_OBJS = rational.o testbase.o test-rational.o

all: test-rational

test-rational: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: test-rational
	./$^

clean : 
	rm -f test-rational testbase *.o *~
	rm -rf docs

.PHONY: all test clean