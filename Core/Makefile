#
# JPEGMetaExtractor/Core/Makefile
#
NAME := ImageMetaExtractor

CORE := ./
CLI := ../CLI

_SRC := ${CORE}/Source
_INC := ${CORE}/Include
_BLD := ${CORE}/Build
_OBJ := ${_BLD}/Objects
_FNL := ${_BLD}/Final

COPY_TO := ${CLI}

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
	@echo "-- Creating '$(patsubst ${CORE}/%,%, ${_BLD})' directory"
	@mkdir -p ${_BLD}
	@echo "-- Creating '$(patsubst ${CORE}/%,%, ${_OBJ})' directory"
	@mkdir -p ${_OBJ}
	@echo "-- Creating '$(patsubst ${CORE}/%,%, ${_FNL})' directory"
	@mkdir -p ${_FNL}

# Name: library_all
# Description: This target, when invoked, invokes all other library-related
#  targets.
library_all: library_clean library_sources library_create library_copy

# Name: library_clean
# Description: This target deletes any build-resources (objects files, etc.)
#  used during the creation of the library.
library_clean:
	@echo "-- Removing old object files from '$(patsubst ${CORE}/%,%, ${_OBJ})'"
	@rm -rf ${_OBJ}/*
	@echo "-- Removing old library files from '$(patsubst ${CORE}/%,%, ${_FNL})'"
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

# Name: library_copy
# Description: This target copies all of the output files for this library, to
#  the directory that is specified in the '${COPY_TO}' variable
library_copy:
	@echo "-- Copying library files"
	@cp -r ${_FNL}/Include/* ${COPY_TO}/Include
	@cp ${TARGET} ${COPY_TO}/Libraries

#### MARK: COMPILATION TARGETS ####
${_OBJ}/%.src.o: ${_SRC}/%.c
	@echo "-- Source file:" $(patsubst ${_SRC}/%.c, %.c, $^)
	@mkdir -p $(dir $@)
	@${CC} ${CCFLAGS} $^ -o ${_OBJ}/$(notdir $@)
###################################