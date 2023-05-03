led_blink: 
	${MAKE} --no-print-directory -f ./80c51/8051_rules.mk TARGET_FILE_NAME=$@ MAIN_FILE=./80c51/led_blink/led_main.c SRCS:="$(shell ls ./80c51/led_blink/*.c)"

led_blink_asm: 
	${MAKE} --no-print-directory -f ./80c51/8051_rules.mk TARGET_FILE_NAME=$@ ASRCS:="$(shell ls ./80c51/led_blink_asm/*.asm)"