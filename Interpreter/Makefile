# g++ -Wall -Wno-unused-variable -c "%f"
# g++ -Wall -o "%e" "%f"

## libs list ##
libs_list = common_files/command.o common_files/utils.o stack_cpu.o


## main ##
interpreter: BUILD.H interpreter.o $(libs_list)
	g++ -Wall -I"./" -I"./common_files/"  -o "interpreter" "interpreter.o" $(libs_list)
	
interpreter.o: BUILD.H interpreter.cpp
	g++ -Wall -I"./" -I"./common_files/"  -c "interpreter.cpp"
	
	
## test ##
testing: test
	./test

test: BUILD.H test.o $(libs_list)
	g++ -Wall -I"./" -I"./common_files/"  -o "test" "test.o" $(libs_list)
	
test.o: BUILD.H test.cpp
	g++ -Wall -I"./" -I"./common_files/"  -c "test.cpp"
	
## common_files/command.o lib ##
stack_cpu.o: BUILD.H stack_cpu.hpp stack_cpu.cpp
	g++ -Wall -I"./" -I"./common_files/"  -c "stack_cpu.cpp"
	
## common_files/command.o lib ##
common_files/command.o: BUILD.H ./common_files/command.hpp ./common_files/command.cpp
	make -C common_files/ command.o
	
## common_files/utils.o lib ##
common_files/utils.o: BUILD.H ./common_files/utils.hpp ./common_files/utils.cpp
	make -C common_files/ utils.o
	
## common_files/linker.o lib ##
common_files/utils.o: BUILD.H ./common_files/linker.hpp ./common_files/linker.cpp
	make -C common_files/ linker.o
	
BUILD.H:
#nothing

clean:
	rm "$(find . -type f -perm /+u+x)" &
	rm *.gch &
	rm *.o

