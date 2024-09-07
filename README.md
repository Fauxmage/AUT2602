# Flash C programs to AVR128DB48

The Makefile utilized MPLab's XC8 compiler, which is supported on Windows, MacOS, and Linux.

### Requirements:
 - Avrdude
 - Autolab XC8 compiler

### Using the Makefile:

Compile and convert C file to hex:

```make all```


Flash hex file onto micro controller:

```make flash```


Remove all compiled files from directory:

```make clean```


Depending on your OS, you may have to change some of the settings in this Makefile as this one is for MacOS. 
