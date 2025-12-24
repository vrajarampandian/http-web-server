CC=gcc
CFLAGS=-Wall -Wextra -g
TARGET=server

all: $(TARGET)

$(TARGET): src/server.c
	$(CC) $(CFLAGS) src/server.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
