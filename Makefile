VPATH := src vendor/src lib/src

# removing src/ from file paths
SRC_FILES := $(notdir $(wildcard src/*.c) )
VENDOR_SRC_FILES := $(notdir $(wildcard vendor/src/*.c))
LIB_SRC_FILES := $(notdir $(wildcard lib/src/*.c))

CPP_SRC_FILES := $(notdir $(wildcard src/*.cpp))
CPP_VENDOR_SRC_FILES := $(notdir $(wildcard vendor/src/*.cpp))
CPP_LIB_SRC_FILES := $(notdir $(wildcard lib/src/*.cpp))

# all object file that have a corresponding .c file. Adding obj/ at the start
OBJ_FILES := $(addprefix obj/,$(SRC_FILES:c=o))
LIB_OBJ_FILES := $(addprefix lib/obj/,$(LIB_SRC_FILES:c=o))
VENDOR_OBJ_FILES := $(addprefix vendor/obj/,$(VENDOR_SRC_FILES:c=o))

CPP_OBJ_FILES := $(addprefix objCPP/,$(CPP_SRC_FILES:cpp=o))
CPP_LIB_OBJ_FILES := $(addprefix lib/objCPP/,$(CPP_LIB_SRC_FILES:cpp=o))
CPP_VENDOR_OBJ_FILES := $(addprefix vendor/objCPP/,$(CPP_VENDOR_SRC_FILES:cpp=o))

ALL_OBJ := $(OBJ_FILES) $(VENDOR_OBJ_FILES) $(LIB_OBJ_FILES) $(CPP_OBJ_FILES) $(CPP_VENDOR_OBJ_FILES) $(CPP_LIB_OBJ_FILES)


#G++ := "/c/MinGW/bin/g++.exe"
G++ := g++
G++_FLAGS := -Wall -Wextra -std=c++17
INC_DIR := -I./inc -I./vendor/inc -I./lib/inc
LD_FLAGS := -L./vendor/bin -lglfw3 -lGdi32

# builds each .o and stores in obj
obj/%.o: %.c | obj
	${G++} $(G++_FLAGS) $(INC_DIR) -c $< -o $@ $(LD_FLAGS)

vendor/obj/%.o: %.c | vendor/obj
	${G++} $(INC_DIR) -g -c $< -o $@

lib/obj/%.o: %.c | lib/obj
	${G++} $(INC_DIR) -g -c $< -o $@

# builds each .o and stores in obj
objCPP/%.o: %.cpp | objCPP
	${G++} $(G++_FLAGS) $(INC_DIR) -c $< -o $@ $(LD_FLAGS)

vendor/objCPP/%.o: %.cpp | vendor/objCPP
	${G++} $(INC_DIR) -g -c $< -o $@

lib/objCPP/%.o: %.cpp | lib/objCPP
	${G++} $(INC_DIR) -g -c $< -o $@

# creates the .o files for each file that should be in /obj dir. This is based on .c files in /src, then compiles into final bin
bin/renderer: $(ALL_OBJ) | bin
	${G++} $^ -o $@ $(LD_FLAGS)

all: bin/renderer

bin obj vendor/obj lib/obj objCPP vendor/objCPP lib/objCPP:
	@echo "Creating Directory $@"
	@mkdir $@/

clean:
	@rm -rf obj bin vendor/obj lib/obj objCPP vendor/objCPP lib/objCPP

remake: clean | bin/renderer

test1:
	$(G++) -o test.exe test.cpp

test2:
	${GCC} --version