export BUILD_DIR_ROOT ?= build
PORT ?= /dev/ttyCH341USB0

asm_targets := $(addprefix asm__, $(patsubst %.asm, %, $(notdir $(shell ls ./80C51/asm/*.asm))))
clean_targets := $(addprefix clean_80C51__, $(asm_targets))
upload_targets := $(addprefix upload_80C51__, $(asm_targets))


${asm_targets}: asm__% : ./80C51/asm/%.asm
	@${MAKE} -f ./80C51/80C51_rules.mk 80C51_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/80C51/asm\
		ASM_FILE=$< TARGET_FILE_NAME=$(patsubst asm__%,%,$@)

${clean_targets} : clean_% : 
	@rm -rf ${BUILD_DIR_ROOT}/$(subst __,/, $(patsubst clean_%,%,$@))

${upload_targets}: upload_80C51__% : %
	@stcgal -P stc89 -p ${PORT} ${UPLOAD_OPTIONS} ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%,$@))/*.hex