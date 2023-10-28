CXX = g++
CXXFLAGS = -std=c++11

SRCS = main.cpp solute.cpp foramt.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)
