CXX = g++-10
CXXFLAGS =-Wall -Wextra -g -std=c++20
EXTRA_CFLAGS = -lncurses

SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.h)
OBJS = $(SRCS:.cpp=.o)
EXEC = pong_game

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(EXTRA_CFLAGS) -o $(EXEC)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

