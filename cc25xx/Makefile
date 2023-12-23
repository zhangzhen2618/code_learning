export BUILD_DIR_ROOT ?= build

targets := $(patsubst cc25xx/%/, cc25xx__%, $(shell ls -d cc25xx/*/))

clean_targets := $(addprefix clean_, ${targets})
upload_targets := $(addprefix upload_, ${targets})

${targets}: cc25xx__% : 
	@echo "build target : $@"
	@${MAKE} -f ./cc25xx/cc25xx_rules.mk CC25XX_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/cc25xx \
		TARGET_FILE_NAME=$(patsubst cc25xx__%,%,$@) \
		INCLUDE_PATH=./cc25xx/${patsubst cc25xx__%,%,$@}/include \
		SRCS=./cc25xx/${patsubst cc25xx__%,%,$@}/src
	@echo "\n\n***********************  Memory cost **************************"
	@echo "\nMemory: " & tail -n 5 ${BUILD_DIR_ROOT}/$(subst __,/,$@)/*.mem
	@echo "\n\n***********************  Memory cost *************************\n\n"

${clean_targets}: clean_%:
	@echo "clean target ${patsubst clean_%, %, $@}"
	@rm -rf ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst clean_%,%, $@))

${upload_targets}: upload_% : %
	@echo "Uploading target : ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_cc25xx__%,%, $@).hex"
	@sudo cc-tool -f -e -v -w  ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_cc25xx__%,%, $@).hex