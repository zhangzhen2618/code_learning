export BUILD_DIR_ROOT ?= build
STC8H8K64U_PORT ?= /dev/ttyUSB0

targets := $(filter-out STC8H8K64U/__%/, $(shell ls -d STC8H8K64U/*/)) 
targets := $(patsubst STC8H8K64U/%/, STC8H8K64U__%, ${targets})

clean_targets := $(addprefix clean_, ${targets})
upload_targets := $(addprefix upload_, ${targets})

${targets}: STC8H8K64U__% : 
	@echo "build target : $@"
	@${MAKE} -f ./STC8H8K64U/STC8H8K64U_rules.mk STC8H8K64U_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/STC8H8K64U \
		TARGET_FILE_NAME=$(patsubst STC8H8K64U__%,%,$@) \
		INCLUDE_PATH=./STC8H8K64U/${patsubst STC8H8K64U__%,%,$@}/include \
		SRCS=./STC8H8K64U/${patsubst STC8H8K64U__%,%,$@}/src
	@echo "\n\n***********************  Memory cost **************************"
	@echo "\nMemory: " & tail -n 5 ${BUILD_DIR_ROOT}/$(subst __,/,$@)/*.mem
	@echo "\n\n***********************  Memory cost *************************\n\n"

${clean_targets}: clean_%:
	@echo "clean target ${patsubst clean_%, %, $@}"
	@rm -rf ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst clean_%,%, $@))

${upload_targets}: upload_% : %
	@echo "Uploading target : ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_STC8H8K64U__%,%, $@).hex"
	@stcgal -P stc8d -t 48000 -p ${STC8H8K64U_PORT}  ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_STC8H8K64U__%,%, $@).hex