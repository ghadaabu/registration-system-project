CC = g++
CFLAGS = -Wall -std=c++11
SRCS = main.cpp register.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(OBJS)

