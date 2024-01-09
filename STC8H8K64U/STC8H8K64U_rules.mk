# MCU := -mmcs51 --model-large
MCU := --out-fmt-ihx --code-loc 0x0000 \
	--xram-size 0x2000 --iram-size 0x200  --model-large \
		--code-size 65536 \
		--opt-code-speed -DFLASH_SIZE=65536 -DFLASH_PAGESIZE=0x200
CC := sdcc
ASM := sdas8051
INCLUDE_PATH_ =-I${INCLUDE_PATH} -I/usr/share/sdcc/include/ -I./STC8H8K64U/__common
FLAGS := ${MCU} ${INCLUDE_PATH_}
ROM_SIZE ?= 65536

TARGET_DIR := ${STC8H8K64U_BUILD_ROOT_DIR}/${TARGET_FILE_NAME}

IHX := ${TARGET_DIR}/${TARGET_FILE_NAME}.ihx
HEX := ${TARGET_DIR}/${TARGET_FILE_NAME}.hex
BINARY := ${TARGET_DIR}/${TARGET_FILE_NAME}.bin

COBJS = ${addprefix ${TARGET_DIR}/, $(patsubst %.c, %.rel, $(shell ls ${SRCS}))}

HEADER_FILES = $(foreach ipath, ${INCLUDE_PATH}, $(addprefix ${ipath}/, $(shell ls ${ipath})))

all: ${TARGET_DIR} ${IHX} ${HEX} ${BINARY}

vpath %.c ${SRCS}

${TARGET_DIR}/%.rel: %.c ${HEADER_FILES}
	@echo Generating object : $@ 
	@${CC} -c ${FLAGS} -o $@ $<

OBJS := ${COBJS}

${TARGET_DIR}:
	@mkdir -p ${TARGET_DIR}

# generate the ihx file
${IHX}: ${MAKEFILE_LIST} ${OBJS}
	@${CC} -o $@ ${OBJS} ${FLAGS}

# convent ihx to hex
${HEX}: ${IHX}
	@packihx $< > $@

# use hex generate bin file
${BINARY}: ${HEX}
	@makebin -s ${ROM_SIZE} $< $@
