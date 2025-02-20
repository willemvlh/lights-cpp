CC = clang++-13
CFLAGS =  -g -I/usr/local/include -std=c++20
CFLAGS_FULL = -Wall -Wextra -fsanitize=address 
CFLAGS_TEST = -I src -I lib $(CFLAGS_FULL)
LDFLAGS = -lpaho-mqttpp3 -lpaho-mqtt3a -lpthread
ifneq ($(findstring microsoft,$(shell uname -r)),microsoft)
	LDFLAGS += -lws2811
endif
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

debug: CFLAGS += $(CFLAGS_FULL)
debug: $(TARGET)

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
	rm -f $(TEST_OBJS) $(BUILD_DIR/$(TARGET))

