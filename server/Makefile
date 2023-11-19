# Variables
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lmicrohttpd
TARGET =  main
OBJECTS = main.o

# Reglas
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

