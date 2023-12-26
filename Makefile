CC = clang
# Debugging doesn't work unless we use `-g`
# TODO: create debug and release builds
CFLAGS = -Wall -Wextra -Werror -g -std=c17

SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC:$(SRC_DIR)/%.c=%.o)
TARGET = monkey

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $<

# Phony target for cleaning up the project
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
