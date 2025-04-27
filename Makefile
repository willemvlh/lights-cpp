CC = clang++-13
CFLAGS = -I/usr/local/include -std=c++20
CFLAGS_DEBUG = -g -Wall -Wextra 
CFLAGS_SANITIZE=-fsanitize=address -fsanitize=undefined
CFLAGS_TEST = $(CFLAGS_DEBUG) -I src -I lib
LDFLAGS = -lpaho-mqttpp3 -lpaho-mqtt3a -lpthread
ifdef USE_WS2811
	CFLAGS += -DUSE_WS2811
	LDFLAGS += -lws2811
endif
ifdef USE_MQTT
	CFLAGS += -DUSE_MQTT
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

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(TARGET)
