VPATH := src vendor/src lib/src

# removing src/ from file paths
SRC_FILES := $(notdir $(wildcard src/*.c))
VENDOR_SRC_FILES := $(notdir $(wildcard vendor/src/*.c))
LIB_SRC_FILES := $(notdir $(wildcard lib/src/*.c))
# all object file that have a corresponding .c file. Adding obj/ at the start
OBJ_FILES := $(addprefix obj/,$(SRC_FILES:c=o))
LIB_OBJ_FILES := $(addprefix lib/obj/,$(LIB_SRC_FILES:c=o))
VENDOR_OBJ_FILES := $(addprefix vendor/obj/,$(VENDOR_SRC_FILES:c=o))

GCC := "/c/msys64/mingw64/bin/gcc.exe"
GCC_FLAGS := -Wall -Wextra -g
INC_DIR := -I./inc -I./vendor/inc -I./lib/inc
LD_FLAGS := -L./vendor/bin -lglfw3 -lGdi32

# builds each .o and stores in obj
obj/%.o: %.c | obj
	@${GCC} $(GCC_FLAGS) $(INC_DIR) -c $< -o $@ $(LD_FLAGS)

vendor/obj/%.o: %.c | vendor/obj
	@${GCC} $(INC_DIR) -g -c $< -o $@

lib/obj/%.o: %.c | lib/obj
	@${GCC} $(INC_DIR) -g -c $< -o $@

# creates the .o files for each file that should be in /obj dir. This is based on .c files in /src, then compiles into final bin
bin/renderer: $(OBJ_FILES) $(VENDOR_OBJ_FILES) $(LIB_OBJ_FILES) | bin
	@${GCC} $^ -o $@ $(LD_FLAGS)

all: bin/renderer

bin obj vendor/obj lib/obj:
	@echo "Creating Directory $@"
	@mkdir $@

clean:
	@rm -rf obj bin vendor/obj lib/obj

test:
	@echo $(LIB_OBJ_FILES) $(LIB_SRC_FILES)