SRC_DIR = src
BUILD_DIR = build
PROGRAM = view_json
SCRIPT = main.cpp
CC = g++
CFLAGS = -Wall -Wextra

.PHONY: all

all: $(PROGRAM)

$(PROGRAM): $(SRC_DIR)/$(SCRIPT)
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm -f $(BUILD_DIR)/$(PROGRAM)
