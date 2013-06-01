CXX = g++
CXXFLAGS = -g --std=c++0x
OBJS = list.o
BINS = list

all : $(BINS)
clean :
	rm $(OBJS)
	rm $(BINS)

list : $(OBJS)
	$(CXX) $(OBJS) -o list -lboost_unit_test_framework

list.o :
	$(CXX) $(CXXFLAGS) -c list.cpp
	