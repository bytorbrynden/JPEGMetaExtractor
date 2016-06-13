#
# JPEGMetaExtractor/Core/Makefile
#
NAME := ImageMetaExtractor
ROOT := ${CURDIR}

_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include
_BLD := ${ROOT}/Build
_OBJ := ${_BLD}/Objects
_FNL := ${_BLD}/Final

TARGET := ${_FNL}/${NAME}.a

CC := gcc
CCFLAGS := -c -Wall -Werror -ggdb -I${_INC}

SOURCES := $(shell find ${_SRC} -type f -name "*.c")
SOURCE_OBJECTS := $(patsubst ${_SRC}/%.c, ${_OBJ}/%.src.o, ${SOURCES})

.PHONY: all
all: library_all

# Name: setup_structure
# Description: This target is used to setup the directory-structure for the
#  library, and should only be run once.
setup_structure:
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${_BLD})' directory"
	@mkdir -p ${_BLD}
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${_OBJ})' directory"
	@mkdir -p ${_OBJ}
	@echo "-- Creating '$(patsubst ${ROOT}/%,%, ${_FNL})' directory"
	@mkdir -p ${_FNL}

# Name: library_all
# Description: This target, when invoked, invokes all other library-related
#  targets.
library_all: library_clean library_sources library_create

# Name: library_clean
# Description: This target deletes any build-resources (objects files, etc.)
#  used during the creation of the library.
library_clean:
	@echo "-- Removing old object files from '$(patsubst ${ROOT}/%,%, ${_OBJ})'"
	@rm -rf ${_OBJ}/*
	@echo "-- Removing old library files from '$(patsubst ${ROOT}/%,%, ${_FNL})'"
	@rm -rf ${_FNL}/*.a
	@rm -rf ${_FNL}/Include/*

# Name: library_sources
# Description: This target compiles all of the library's source (*.c files).
library_sources:
	@echo "-- Compiling library sources"
	@make ${SOURCE_OBJECTS}

# Name: library_create
# Description: This target combines all of our previously generated object
#  files, into a library (*.a) file.
library_create:
	@echo "-- Creating library file"
	@ar -rsc ${TARGET} $(shell find ${_OBJ} -type f -name "*.o")
	@cp -r ${_INC}/* ${_FNL}/Include

#### MARK: COMPILATION TARGETS ####
${_OBJ}/%.src.o: ${_SRC}/%.c
	@echo "-- Source file:" $(patsubst ${_SRC}/%.c, %.c, $^)
	@mkdir -p $(dir $@)
	@${CC} ${CCFLAGS} $^ -o ${_OBJ}/$(notdir $@)
###################################