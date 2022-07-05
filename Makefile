#this is a makefile
all:
	gcc assembler.c assembler.h -g -o assembler
exec: 
	./assembler test_input
clean: 
	rm -rf assembler
	rm -rf *.exe
	rm -rf *.o
