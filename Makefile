CC = clang++
CFLAGS = -Wall -Wextra -I/usr/local/include -g
CFLAGS_TEST = -I src -I lib
LDFLAGS= -lws2811 -lpaho-mqttpp3
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_WITHOUT_MAIN = $(filter-out build/main.o, $(OBJS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS))
TARGET = main
TEST_TARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -c $< -o $@

$(TEST_TARGET): $(OBJS_WITHOUT_MAIN) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $(OBJS_WITHOUT_MAIN) $(TEST_OBJS) -o $(TEST_DIR)/$(TEST_TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(BUILD_DIR/$(TARGET))

