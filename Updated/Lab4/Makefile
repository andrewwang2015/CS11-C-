CXXFLAGS = -Wall -std=c++14
CONVERT_OBJS = units.o convert.o
TEST_OBJS = units.o testbase.o hw3testunits.o 
all : convert hw3testunits

convert : $(CONVERT_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test : hw3testunits 

hw3testunits : $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

doc : 
	doxygen

clean : 
	rm -f convert hw3testunits *.o *~
	rm -rf docs

.PHONY: all test doc clean