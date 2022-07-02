#this is a makefile
all:
	gcc assembler.c -g -o assembler
exec: 
	./assembler test_input.txt
clean: 
	rm -rf assembler
	rm -rf *.exe
	rm -rf *.o
