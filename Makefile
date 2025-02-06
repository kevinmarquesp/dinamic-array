CC := clang
CFLAGS := -Wall -Wextra -Iinclude
SRC_DIR := src
BUILD_DIR := build
TARGET := prog.out

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET) run

$(TARGET): $(OBJS)
	mkdir -vp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@./$<

clean:
	rm -f $(BUILD_DIR) $(TARGET)
