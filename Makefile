#this is a makefile
all:
	gcc assembler.c assembler.h structs.h constants.h macro_deploy.c macro_deploy.h first_scan.h first_scan.c utils.c utils.h second_scan.h second_scan.c -o assembler
exec1: 
	./assembler test_input 
exec2: 
	./assembler test_input test_input_2
exec3: 
	./assembler test_input_noLabel
dbg:
	gcc assembler.c assembler.h structs.h constants.h macro_deploy.c macro_deploy.h first_scan.h first_scan.c utils.c utils.h second_scan.h second_scan.c -g -o assembler ;gdb --args ./assembler test_input
clean: 
	rm -rf assembler
	rm -rf *.exe
	rm -rf *.o
save:
	git add .; git commit; git push
