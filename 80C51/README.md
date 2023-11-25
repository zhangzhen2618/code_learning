# STC89C52RC ASSEMBLY AND C DEMO
## Same funcation using assembly and C language

* Here using the [sdcc](https://sdcc.sourceforge.net) to complie, and using the [stcgal](https://github.com/grigorig/stcgal) to upload the code. 
* You can use the apt to install sdcc and stcgal.

## Assembly : 
```
在80C52 中不同的寻址方式对应不同的物理地址，代码区（CODE, FLASH）和 数据区（RAM）以及SFR（特殊功能寄存器）和 位寻址区，其地址是有包含重合的，使用不同的寻址可访问对应的物理地址。这里面要注意的， 寻址方式有，立即寻址，直接寻址，间接寻址，寄存器寻址，相对寻址， 变址寻址， 位寻址；
```
[地址示意图]()
* 立即寻址 ：
```
```
* 直接寻址 ：

* 间接寻址 ： 

* 寄存器寻址 ：

* 相对寻址 ： 

* 变址寻址 ：

* 位寻址 ： 

## C ： 

## Documents : 
* [sdccman](./doc/sdccman.pdf)
* [asmxxx](./doc/asmlnk.pdf)
* [STC89C52](./doc/STC89C52.pdf)

## [HC6800-ES V2.0 SCHEMATIC](./doc/HC6800-ES%20V2.0原理图.pdf) : 
### Assembly ：
* [led blink using NOP director](./asm/led_blink.asm)
* [led blink using timer interrupt](./asm/led_blink_timer.asm)
* [7 segments led](./asm/7_seg_led.asm)

### C ：
* [led blink using NOP director](./asm/led_blink.c)
* [led blink using timer interrupt](./asm/led_blink_timer.c)
* [7 segments led](./src/7_seg_led.c)