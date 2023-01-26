all: test01 test02

clean:
	rm -rf test01 test01.dSYM
	rm -rf test02 test02.dSYM

test01: 
	gcc -o test01 test01.c ../disk/diskDriver.c ../io/File.c -w

test02: 
	gcc -o test02 test02.c ../disk/diskDriver.c ../io/File.c -w

