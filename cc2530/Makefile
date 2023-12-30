export BUILD_DIR_ROOT ?= build

targets := $(patsubst cc2510/%/, cc2510__%, $(shell ls -d cc2510/*/))

clean_targets := $(addprefix clean_, ${targets})
upload_targets := $(addprefix upload_, ${targets})

${targets}: cc2510__% : 
	@echo "build target : $@"
	@${MAKE} -f ./cc2510/cc2510_rules.mk CC2510_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/cc2510 \
		TARGET_FILE_NAME=$(patsubst cc2510__%,%,$@) \
		INCLUDE_PATH=./cc2510/${patsubst cc2510__%,%,$@}/include \
		SRCS=./cc2510/${patsubst cc2510__%,%,$@}/src
	@echo "\n\n***********************  Memory cost **************************"
	@echo "\nMemory: " & tail -n 5 ${BUILD_DIR_ROOT}/$(subst __,/,$@)/*.mem
	@echo "\n\n***********************  Memory cost *************************\n\n"

${clean_targets}: clean_%:
	@echo "clean target ${patsubst clean_%, %, $@}"
	@rm -rf ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst clean_%,%, $@))

${upload_targets}: upload_% : %
	@echo "Uploading target : ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_cc2510__%,%, $@).hex"
	@sudo cc-tool -f -e -v -w  ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_cc2510__%,%, $@).hex