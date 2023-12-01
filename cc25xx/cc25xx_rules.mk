# rules for sdcc complie the 8051 default for the STC89C52RC
MCU := -mmcs51
CC := sdcc
ASM := sdas8051
INCLUDE_PATH += -I/usr/share/sdcc/include/macs51/
FLAGS := ${MCU} ${INCLUDE_PATH} --xram-size 256 --code-size 8192
ROM_SIZE ?= 8192

TARGET_DIR := ${CC25XX_BUILD_ROOT_DIR}/${TARGET_FILE_NAME}

IHX := ${TARGET_DIR}/${TARGET_FILE_NAME}.ihx
HEX := ${TARGET_DIR}/${TARGET_FILE_NAME}.hex
BINARY := ${TARGET_DIR}/${TARGET_FILE_NAME}.bin

all: ${TARGET_DIR} ${IHX} ${HEX} ${BINARY}

vpath %.c $(sort $(dir ${SRCS}))
${TARGET_DIR}/%.rel: %.c
	@echo Generating object $@ 
	${CC} -c ${FLAGS} -o $@ $<

OBJS := ${COBJS} ${AOBJS}

${TARGET_DIR}:
	@mkdir -p ${TARGET_DIR}

# generate the ihx file
${IHX}: ${MAKEFILE_LIST} ${OBJS}
	${CC} -o $@ ${OBJS} ${FLAGS}

# convent ihx to hex
${HEX}: ${IHX}
	@packihx $< > $@

# use hex generate bin file
${BINARY}: ${HEX}
	@makebin -s ${ROM_SIZE} $< $@
