# rules for sdcc complie the 8051 default for the STC89C52RC
MCU := -mmcs51
CC := sdcc
ASM := sdas8051
INCLUDE_PATH:=-I./80c51/include
FLAGS := ${MCU} ${INCLUDE_PATH}
ROM_SIZE ?= 8192

BUILD_DIR := ${BUILD_DIR_ROOT}/80c51/${TARGET_FILE_NAME}

COBJS := $(addprefix ${BUILD_DIR}/, $(patsubst %.c, %.rel,$(filter-out $(notdir ${MAIN_FILE}), $(notdir ${SRCS}))))
# add parten %.c search path
vpath %.c $(sort $(dir ${SRCS}))

AOBJS := $(addprefix ${BUILD_DIR}/, $(patsubst %.asm, %.rel,$(notdir ${ASRCS})))
# add parten %.asm search path
vpath %.asm $(sort $(dir $(ASRCS)))

OBJS := ${COBJS} ${AOBJS}
IHX := ${BUILD_DIR}/${TARGET_FILE_NAME}.ihx
HEX := ${BUILD_DIR}/${TARGET_FILE_NAME}.hex
BINARY := ${BUILD_DIR}/${TARGET_FILE_NAME}.bin

all: ${BUILD_DIR} ${IHX} ${HEX} ${BINARY}

${BUILD_DIR}/%.rel: %.c
	@echo Generating object $@ 
	${CC} -c ${FLAGS} -o $@ $<

${BUILD_DIR}/%.rel: %.asm
	@echo Generating object $@
	$(ASM) -o -l $<

${BUILD_DIR}:
	@mkdir -p ${BUILD_DIR}

# generate the ihx file
${IHX}: ${MAKEFILE_LIST} ${OBJS}
	${CC} -o $@ ${MAIN_FILE} ${OBJS} ${FLAGS}
# convent ihx to hex
${HEX}: ${IHX}
	@packihx $< > $@
# use hex generate bin file
${BINARY}: ${HEX}
	@makebin -s ${ROM_SIZE} $< $@
