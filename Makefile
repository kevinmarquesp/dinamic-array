CC := clang
CFLAGS := -Wall -Wextra -Iinclude
SRC_DIR := src
BUILD_DIR := build
TARGET := prog.out

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

DOXYGEN := doxygen
HTML := html

all: init $(TARGET) run

init:
	@mkdir -vp $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@./$<

.PHONY: html
html:
	$(DOXYGEN)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(HTML)
