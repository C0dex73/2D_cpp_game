#****************************************************************
#						      GLOBAL
#****************************************************************
#~CONSTANTS

#files
SRC_DIR:=src
INCLUDE_DIR:=include
TEMPLATE_DIR:=include/templates
BIN_DIR:=bin
BUILD_DIR:=build
LIB_DIR:=lib
SHADER_DIR:=assets
SRC_EXTENSION:=cc
HEADER_EXTENSION:=hh
TEMPLATE_EXTENSION:=tcc
OBJ_EXTENSION:=o
DEP_EXTENSION:=d
EXEC_EXTENSION:=run
SHADER_EXTENSION:=glsl
SHADER_OBJ:=rawShaders

#compiler/linker
COMPILER:=g++
FLAGS:=-std=c++20 -I./$(INCLUDE_DIR) -I./$(TEMPLATE_DIR)
CFLAGS:=
LFLAGS:=-lglfw -lGL
BUILD_FLAGS:=-s
BUILD_CFLAGS:=
BUILD_LFLAGS:=
DEBUG_FLAGS:=-g -Wall
DEBUG_CFLAGS:=
DEBUG_LFLAGS:=

STARTING_POINTS:=test game editor
EXEC=none

#~PROCESSED VAR
HEADERS:=$(wildcard ./$(INCLUDE_DIR)/*.$(HEADER_EXTENSION)) $(wildcard ./$(TEMPLATE_DIR)/*.$(TEMPLATE_EXTENSION))
SRC:=$(foreach file,$(foreach file,$(wildcard ./$(SRC_DIR)/*.$(SRC_EXTENSION)),$(file)),$(if $(findstring $(file:./$(SRC_DIR)/%.$(SRC_EXTENSION)=%),$(STARTING_POINTS)),,$(file)))
OBJ=./$(BIN_DIR)/$(SHADER_OBJ).$(OBJ_EXTENSION) $(foreach file,$(wildcard ./$(LIB_DIR)/*),$(file:./$(LIB_DIR)/%=./$(BIN_DIR)/%.$(OBJ_EXTENSION))) $(foreach file,$(SRC) $(if $(findstring none,$(EXEC)),,./$(SRC_DIR)/$(EXEC).$(SRC_EXTENSION)),$(file:./$(SRC_DIR)/%=./$(BIN_DIR)/%.$(OBJ_EXTENSION)))
DEP=$(OBJ:%.$(OBJ_EXTENSION)=%.$(DEP_EXTENSION))
SHADERS:=$(wildcard ./$(SHADER_DIR)/*.$(SHADER_EXTENSION))

#^ run command arguments parsing into RUN_ARGS
RULES_WITH_CONSOLE_ARGS:=
ifneq (,$(filter $(firstword $(MAKECMDGOALS)), $(RULES_WITH_CONSOLE_ARGS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

#~MAKEFILE

.PHONY: all reset

all: $(STARTING_POINTS)

reset:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)

build: $(BUILD_DIR)_rule $(STARTING_POINTS:%=build.%)
	rm -f $(BUILD_DIR)/*.d
	rm -f $(BUILD_DIR)/*.o

debug:
	echo There is no debug script written in $(CURDIR)/makefile :: debug

$(BIN_DIR)_rule:
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)_rule:
	mkdir -p $(BUILD_DIR)

$(BIN_DIR)/%.$(OBJ_EXTENSION): $(LIB_DIR)/%
	$(COMPILER) $(FLAGS) $(CFLAGS) $(DEBUG_FLAGS) $(DEBUG_CFLAGS) -c -o $@ $<

-include $(DEP)
$(BIN_DIR)/%.$(OBJ_EXTENSION): $(SRC_DIR)/%
	$(COMPILER) $(FLAGS) $(CFLAGS) $(DEBUG_FLAGS) $(DEBUG_CFLAGS) -MMD -c -o $@ $<

$(BUILD_DIR)/%.$(OBJ_EXTENSION): $(LIB_DIR)/%
	$(COMPILER) $(FLAGS) $(CFLAGS) $(BUILD_FLAGS) $(BUILD_CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.$(OBJ_EXTENSION): $(SRC_DIR)/%
	$(COMPILER) $(FLAGS) $(CFLAGS) $(BUILD_FLAGS) $(BUILD_CFLAGS) -c -o $@ $<

#****************************************************************
#						     SHADERS
#****************************************************************

shader: $(BIN_DIR)_rule $(BIN_DIR)/$(SHADER_OBJ).$(OBJ_EXTENSION)

$(BIN_DIR)/$(SHADER_OBJ).$(OBJ_EXTENSION): $(SHADERS)
	ld -r -b binary -o ./$(BIN_DIR)/$(SHADER_OBJ).$(OBJ_EXTENSION) $(SHADERS)

$(BUILD_DIR)/$(SHADER_OBJ).$(OBJ_EXTENSION): $(SHADERS)
	ld -r -b binary -o ./$(BUILD_DIR)/$(SHADER_OBJ).$(OBJ_EXTENSION) $(SHADERS)


#****************************************************************
#						   LEVEL EDITOR
#****************************************************************
EXEC=editor

editor: $(BIN_DIR)_rule .editor

.editor: $(OBJ)
	$(COMPILER) $(FLAGS) $(LFLAGS) $(DEBUG_FLAGS) $(DEBUG_LFLAGS) -o $(BIN_DIR)/editor.$(EXEC_EXTENSION) $^

build.editor: $(OBJ:./$(BIN_DIR)/%=./$(BUILD_DIR)/%)
	$(COMPILER) $(FLAGS) $(LFLAGS) $(BUILD_FLAGS) $(BUILD_LFLAGS) -o $(BUILD_DIR)/editor.$(EXEC_EXTENSION) $^

#****************************************************************
#						   	   GAME
#****************************************************************
EXEC=game

game: $(BIN_DIR)_rule .game

.game: $(OBJ)
	$(COMPILER) $(FLAGS) $(LFLAGS) $(DEBUG_FLAGS) $(DEBUG_LFLAGS) -o $(BIN_DIR)/game.$(EXEC_EXTENSION) $^

build.game: $(OBJ:./$(BIN_DIR)/%=./$(BUILD_DIR)/%)
	$(COMPILER) $(FLAGS) $(LFLAGS) $(BUILD_FLAGS) $(BUILD_LFLAGS) -o $(BUILD_DIR)/game..$(EXEC_EXTENSION) $^

#****************************************************************
#					  	     TEST EXEC
#****************************************************************
EXEC=test

test: $(BIN_DIR)_rule .test

.test: $(OBJ)
	$(COMPILER) $(FLAGS) $(LFLAGS) $(DEBUG_FLAGS) $(DEBUG_LFLAGS) -o $(BIN_DIR)/test.$(EXEC_EXTENSION) $^

build.test:
	echo Skipping test.run build because it is a developement tool...