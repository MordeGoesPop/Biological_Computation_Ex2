CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = main
SRCS = main.cpp Graph.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Graph.h utils.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
