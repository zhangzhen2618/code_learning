export BUILD_DIR_ROOT ?= build
PORT ?= /dev/ttyCH341USB0

asm_targets := $(addprefix asm__, $(patsubst %.asm, %, $(notdir $(shell ls ./80C51/asm/*.asm))))
c_targets := $(addprefix c__, $(patsubst %.c, %, $(notdir $(shell ls ./80C51/src/*.c))))

clean_targets := $(addprefix clean_80C51__, $(asm_targets))
clean_targets += $(addprefix clean_80C51__, $(c_targets))
upload_targets := $(addprefix upload_80C51__, $(asm_targets))
upload_targets += $(addprefix upload_80C51__, $(c_targets))


${asm_targets}: asm__% : ./80C51/asm/%.asm
	@${MAKE} -f ./80C51/80C51_rules.mk 80C51_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/80C51/asm\
		ASM_FILE=$< TARGET_FILE_NAME=$(patsubst asm__%,%,$@)
	@echo "\nMemory: " & tail -n 5 ${BUILD_DIR_ROOT}/80C51/$(subst __,/,$@)/*.mem
	
${c_targets}: c__% : ./80C51/src/%.c
	@${MAKE} -f ./80C51/80C51_rules.mk 80C51_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/80C51/c\
		C_FILE=$< TARGET_FILE_NAME=$(patsubst c__%,%,$@)
	@echo "\nMemory: " & tail -n 5 ${BUILD_DIR_ROOT}/80C51/$(subst __,/,$@)/*.mem

${clean_targets} : clean_% : 
	@rm -rf ${BUILD_DIR_ROOT}/$(subst __,/, $(patsubst clean_%,%,$@))

${upload_targets}: upload_80C51__% : %
	@stcgal -o cpu_6t_enabled=True -P stc89 -p ${PORT} ${UPLOAD_OPTIONS} ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%,$@))/*.hex