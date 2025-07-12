CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc
SRCDIR = src
BINDIR = bin
TARGET = $(BINDIR)/main

SOURCES = $(SRCDIR)/main/main.c $(SRCDIR)/lexer/lexer.c
OBJECTS = $(SOURCES:.c=.o)

# Create bin directory if it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Main target
make: $(BINDIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rmdir $(BINDIR) 2>/dev/null || true

.PHONY: make clean
