#this is a makefile
all:
	gcc assembler.c assembler.h structs.h constants.h -g -o assembler
exec: 
	./assembler test_input test_input_2
clean: 
	rm -rf assembler
	rm -rf *.exe
	rm -rf *.o
