## libs list ##
libs_list = common_files/command.o common_files/utils.o common_files/stack_cpu.o common_files/linker.o

output: gen.o enviroment.o $(libs_list)
	g++ gen.o enviroment.o $(libs_list) -o output
	chmod +x output
	
########################################################################
gen.o: gen.asm
	nasm -f elf64 gen.asm -o gen.o
	
enviroment.o: BUILD.H enviroment.cpp
	g++ -Wall -c -I"./" -I"./common_files/" enviroment.cpp -o enviroment.o
	
########################################################################
## common_files/stack_cpu.o lib ##
common_files/stack_cpu.o: BUILD.H ./common_files/stack_cpu.hpp ./common_files/stack_cpu.cpp
	make -C common_files/ stack_cpu.o
	
## common_files/command.o lib ##
common_files/command.o: BUILD.H ./common_files/command.hpp ./common_files/command.cpp
	make -C common_files/ command.o
	
## common_files/utils.o lib ##
common_files/utils.o: BUILD.H ./common_files/utils.hpp ./common_files/utils.cpp
	make -C common_files/ utils.o
	
## common_files/linker.o lib ##
common_files/linker.o: BUILD.H ./common_files/linker.hpp ./common_files/linker.cpp
	make -C common_files/ linker.o
	
BUILD.H: common_files/BUILD.H
#nothing

########################################################################
	
clean:
	rm `find . -type f -perm /+u+x` -f
	rm *.gch -f 
	rm *.o -f
	
run: clean output
	@ls
	@echo "|------------------------------------"
	./output
	
########################################################################
generator: generator.o $(libs_list)
	g++ -Wall generator.o $(libs_list) -o generator
	
generator.o: generator.cpp
	g++ -Wall -c -I"./" -I"./common_files/" generator.cpp -o generator.o 
