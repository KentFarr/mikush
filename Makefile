CC      = clang
CFLAGS  = -Wall -Wextra -pedantic -g
LIBS    = -lreadline
TARGET  = mikush
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o $(TARGET)

install: all
	cp $(TARGET) /usr/local/bin/$(TARGET)

.PHONY: all clean install
