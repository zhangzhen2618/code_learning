export BUILD_DIR_ROOT ?= build

# filter out the target : __xxxxx
targets := $(filter-out CC2530/__%/, $(shell ls -d CC2530/*/)) 
targets := $(patsubst CC2530/%/, CC2530__%, ${targets})

clean_targets := $(addprefix clean_, ${targets})
upload_targets := $(addprefix upload_, ${targets})

${targets}: CC2530__% : ./CC2530/CC2530_rules.mk 
	@echo "build target : $@"
	@${MAKE} -f ./CC2530/CC2530_rules.mk CC2530_BUILD_ROOT_DIR=${BUILD_DIR_ROOT}/CC2530 \
		TARGET_FILE_NAME=$(patsubst CC2530__%,%,$@) \
		INCLUDE_PATH=./CC2530/${patsubst CC2530__%,%,$@}/include \
		SRCS=./CC2530/${patsubst CC2530__%,%,$@}/src
	@echo "\n\n***********************  Memory cost **************************"
	@echo "\nMemory: " & tail -n 5 ${BUILD_DIR_ROOT}/$(subst __,/,$@)/*.mem
	@echo "\n\n***********************  Memory cost *************************\n\n"

${clean_targets}: clean_%:
	@echo "clean target ${patsubst clean_%, %, $@}"
	@rm -rf ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst clean_%,%, $@))

${upload_targets}: upload_% : %
	@echo "Uploading target : ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_CC2530__%,%, $@).hex"
	@sudo cc-tool -f -e -v -w  ${BUILD_DIR_ROOT}/$(subst __,/,$(patsubst upload_%,%, $@))/$(patsubst upload_CC2530__%,%, $@).hex