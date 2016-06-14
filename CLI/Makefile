#
# JPEGMetaExtractor/CLI/Makefile
#
NAME := ImageMetaExtractorCLI
ROOT := ${CURDIR}
TEST := ${CURDIR}/Test

_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include
_LIB := ${ROOT}/Libraries
_BLD := ${ROOT}/Build
_OBJ := ${_BLD}/Objects
_FNL := ${_BLD}/Final

TARGET := ${_FNL}/${NAME}
TARGET_FLAGS := $(shell find ${TEST} -type f -name "*.*")

CC := gcc
CCFLAGS := -Wall -Werror -ggdb -I${_INC}

VAL := valgrind
VALFLAGS := --leak-check=yes --track-origins=yes ${TARGET} ${TARGET_FLAGS}

SOURCES := $(shell find ${_SRC} -type f -name "*.c")
SOURCE_OBJECTS := $(patsubst ${_SRC}/%.c, ${_OBJ}/%.src.o, ${SOURCES})

LIBRARIES := $(shell find ${_LIB} -type f -name "*.a")

.PHONY: all
all: cli_all

# Name: setup_structure
# Description: This target is used to setup the directory-structure for the
#  executable, and should only be run once.
setup_structure:
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${TEST})' directory"
	@mkdir -p ${TEST}
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${_BLD})' directory"
	@mkdir -p ${_BLD}
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${_OBJ})' directory"
	@mkdir -p ${_OBJ}
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${_FNL})' directory"
	@mkdir -p ${_FNL}

# Name: cli_all
# Description: This target, when invoked, invokes all other executable-related
#  targets.
cli_all: cli_clean cli_sources cli_create

# Name: cli_clean
# Description: This target deletes any build-resources (objects files, etc.)
#  used during the creation of the executable.
cli_clean:
	@echo "-- Removing old object files from '$(patsubst ${ROOT}/%,%, ${_OBJ})'"
	@rm -rf ${_OBJ}/*
	@echo "-- Removing old executable files from '$(patsubst ${ROOT}/%,%, ${_FNL})'"
	@rm -rf ${_FNL}/*

# Name: cli_sources
# Description: This target compiles all of the executable's source (*.c files).
cli_sources:
	@echo "-- Compiling library sources"
	@make ${SOURCE_OBJECTS}

# Name: cli_create
# Description: This target combines all of our previously generated object
#  files, into a single executable file.
cli_create:
	@echo "-- Creating executable file"
	@${CC} ${CCFLAGS} -o ${TARGET} ${LIBRARIES} ${SOURCE_OBJECTS}
	@chmod +x ${TARGET}

# Name: cli_run
# Description: This target launches the executable.
cli_run:
	@echo "-- Launching executable"
	@${TARGET} ${TARGET_FLAGS}

# Name: cli_test
# Description: Runs valgrind against executable.
cli_test:
	@echo "-- Running valgrind against executable"
	@${VAL} ${VALFLAGS}

#### MARK: COMPILATION TARGETS ####
${_OBJ}/%.src.o: ${_SRC}/%.c
	@echo "-- Source file:" $(patsubst ${_SRC}/%.c, %.c, $^)
	@mkdir -p $(dir $@)
	@${CC} -c ${CCFLAGS} $^ -o ${_OBJ}/$(notdir $@)
###################################