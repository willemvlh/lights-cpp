CC = clang++
CFLAGS = -Wall -Wextra -I/usr/local/include/ws2811
CFLAGS_TEST = -I src -I lib
LDFLAGS= -lws2811
SRC_DIR = src
BUILD_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR),$(BUILD_DIR),$(SRCS))
TARGET = main

#all:
#	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BUILD_DIR/$(TARGET))

test:
	$(CC) $(CFLAGS) $(CFLAGS_TEST) test/test_LedStrip.cpp -o tests && ./tests
