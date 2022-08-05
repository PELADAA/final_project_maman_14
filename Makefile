#this is a makefile
all:
	gcc assembler.c assembler.h structs.h constants.h macro_deploy.c macro_deploy.h first_scan.h first_scan.c utils.c utils.h -o assembler
exec1: 
	./assembler test_input 
exec2: 
	./assembler test_input test_input_2
dbg:
	gdb --args ./assembler test_input
clean: 
	rm -rf assembler
	rm -rf *.exe
	rm -rf *.o
make save:
	git add .; git commit; git push
