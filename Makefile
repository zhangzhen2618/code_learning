# export BUILD_DIR_ROOT ?= build
# export BUILD_DIR_ROOT := ${BUILD_DIR_ROOT}
include ./80C51/Makefile
include ./cc2510/Makefile
include ./STC8H8K64U/Makefile
include ./CC2530/Makefile

