# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/ :)
TARGET_EXEC := plasmvm64
BUILD_DIR := ./build
SRC_DIRS := ./plasmvm
SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
UNAME_S := $(shell uname -s)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP
ifeq ($(UNAME_S),Linux)
        CPPFLAGS += -lSDL2 -I /usr/include/SDL2/ -I/usr/include/SDL2_ttf -lm -ldl
		LNKFLAGS := -lSDL2 -lSDL2_ttf -lm -ldl
endif
ifeq ($(UNAME_S),Darwin)
        CPPFLAGS += -I"/usr/local/Cellar/sdl2/2.0.20/include/SDL2" -I"/usr/local/Cellar/sdl2_ttf/2.0.18_1/include/SDL2"
		LNKFLAGS := -lSDL2 -L"/usr/local/Cellar/sdl2/2.0.20/lib/libSDL2.a" -lSDL2_ttf -L"/usr/local/Cellar/sdl2_ttf/2.0.18_1/lib/libSDL2_ttf.a"
endif
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LNKFLAGS)
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
-include $(DEPS)
