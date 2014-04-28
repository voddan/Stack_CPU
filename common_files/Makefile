## command.o lib ##
command.o: BUILD.H command.hpp command.cpp
	g++ -Wall -I"./" -c "command.cpp"
	
## utils.o lib ##
utils.o: BUILD.H utils.hpp utils.cpp
	g++ -Wall -I"./" -c "utils.cpp"

## linker.o lib ##
linker.o: BUILD.H linker.hpp linker.cpp
	g++ -Wall -I"./" -c "linker.cpp"
	
## stack_cpu.o lib ##
stack_cpu.o: BUILD.H stack_cpu.hpp stack_cpu.cpp
	g++ -Wall -I"./" -c "stack_cpu.cpp"

clean:
	rm $(find . -type f -perm /+u+x) &
	rm *.gch &
	rm *.o
	

