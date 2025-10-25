CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = main
TEST_TARGET = test
LIB_SRCS =
SRCS = main.cpp $(LIB_SRCS)
TEST_SRCS = test.cpp $(LIB_SRCS)
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(TARGET) $(TEST_TARGET) run_tests

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)


$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

out: clean $(TARGET) $(TEST_TARGET) run


run: main
	./main

run_tests: $(TEST_TARGET)
	./test

clean:
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)
	rm -f *.o

everything:
