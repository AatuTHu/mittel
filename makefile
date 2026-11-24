CC        := gcc
CFLAGS    := -Wall -Wextra -Werror -O2 -std=c17 -MMD -MP
CPPFLAGS  := -Iinclude
LDFLAGS   :=
LDLIBS    :=

BUILD_DIR := build
SRC_DIR   := src
TARGET    := mittel

SRCS      := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS      := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: $(TARGET)
	@./$(TARGET) $(filter-out run,$(MAKECMDGOALS))

%:
	@:

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.SILENT:
.PHONY: all clean run
