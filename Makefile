CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS = -lcryptopp
SRCS = main.cpp register.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(OBJS)

