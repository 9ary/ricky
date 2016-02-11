NAME = rickygl

DEBUG = FALSE

CC = clang
CXX = clang++

CFLAGS_COMMON = -Wall -Wextra \
	$(addprefix -I,$(INCLUDE)) \
	-D'PROJ_NAME="$(NAME)"' \
	-MMD -MP \
	-pipe

CFLAGS = $(CFLAGS_COMMON) -std=c11
CXXFLAGS = $(CFLAGS_COMMON) -std=c++11

ifeq ($(DEBUG),FALSE)
	CFLAGS_COMMON += -O2 -flto
else
	CFLAGS_COMMON += -O0 -g
endif

LDFLAGS = -fuse-ld=gold -lGLEW -lGL -lsfml-system -lsfml-window

SRCS_C := $(wildcard src/*.c)
SRCS_CXX := $(wildcard src/*.cpp)
OBJS = $(BUILT_SRCS_C:%.c=%.o) $(BUILT_SRCS_CXX:%.cpp=%.o) \
	$(addprefix $(OUT)/,$(SRCS_C:%.c=%.o)) \
	$(addprefix $(OUT)/,$(SRCS_CXX:%.cpp=%.o))
INCLUDE := include
BUILT_HEADERS :=
BUILT_SRCS_C :=
BUILT_SRCS_CXX :=

OUT = out
EXE = $(OUT)/$(NAME)

# Figure out where we are
define whereami
$(strip $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST)))))
endef

.PHONY: all run clean cflags .FORCE

all: $(EXE)

# Object dependency files
-include $(OBJS:%.o=%.d)

$(OUT)/%.o: %.c | $(BUILT_HEADERS)
	@echo "  CC      $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: %.cpp | $(BUILT_HEADERS)
	@echo "  CXX     $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CXXFLAGS) -c $< -o $@

%.o: %.c | $(BUILT_HEADERS)
	@echo "  CC      $@"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp | $(BUILT_HEADERS)
	@echo "  CXX     $@"
	@$(CC) $(CXXFLAGS) -c $< -o $@

$(EXE): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "  CXXLD   $@"
	@+$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

run: all
	@./$(EXE)

clean:
	@echo "  RM      $(OUT)"
	@rm -rf $(OUT)

# YouCompleteMe configuration
cflags:
	@echo -n $(CXXFLAGS)

.FORCE:
