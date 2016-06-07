#
# JPEGMetaExtractor/Makefile
#
NAME := exifextract
ROOT := ${CURDIR}
_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include
_BLD := ${ROOT}/Build
_OBJ := ${_BLD}/Objects
_FNL := ${_BLD}/Final
TEST := ${CURDIR}/Test

TARGET := ${_FNL}/${NAME}
TARGETFLAGS := $(shell find ${TEST} -type f -name "*.*")

CC := gcc
CCFLAGS := -Wall -Werror -ggdb -I${_INC}

VAL := valgrind
VALFLAGS := --leak-check=yes --track-origins=yes

SRCS := $(shell find ${_SRC} -type f -name "*.c")
SRC_OBJS := $(patsubst ${_SRC}/%.c, ${_OBJ}/%.src.o, ${SRCS})

.PHONY: all
all: exifextract_all

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

exifextract_all: exifextract_clean exifextract_sources exifextract_create

exifextract_clean:
	@echo "-- Removing old object files from '$(patsubst ${ROOT}/%,%, ${_OBJ})'"
	@rm -rf ${_OBJ}/*
	@echo "-- Removing old binary files from '$(patsubst ${ROOT}/%,%, ${_FNL})'"
	@rm -rf ${_FNL}/*

exifextract_sources:
	@echo "-- Compiling library sources"
	@make ${SRC_OBJS}

exifextract_create:
	@echo "-- Creating binary executable"
	@${CC} ${CCFLAGS} -o ${TARGET} ${SRC_OBJS}
	@chmod +x ${TARGET}

exifextract_test:
	@echo "-- Running ${VAL} against binary executable"
	@${VAL} ${VALFLAGS} ${TARGET} ${TARGETFLAGS}

exifextract_run:
	@echo "-- Running binary executable"
	@echo "- BEGIN PROGRAM OUTPUT -"
	@${TARGET} ${TARGETFLAGS}
	@echo "- END PROGRAM OUTPUT -"

#### MARK: COMPILATION TARGETS ####
${_OBJ}/%.src.o: ${_SRC}/%.c
	@echo "-- Source file:" $(patsubst ${_SRC}/%.c, %.c, $^)
	@mkdir -p $(dir $@)
	@${CC} -c ${CCFLAGS} $^ -o $@
###################################