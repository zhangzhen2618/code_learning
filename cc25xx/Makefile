export BUILD_DIR_ROOT ?= build

targets := $(patsubst cc25xx/%/, cc25xx__%, $(shell ls -d cc25xx/*/))

clean_targets := $(addprefix clean_, ${targets})
upload_targets := $(addprefix upload_, ${targets})

${targets}: cc25xx__% : 
	@echo "build target : $@"