## command.o lib ##
command.o: BUILD.H command.hpp command.cpp
	g++ -Wall -I"./" -c "command.cpp"
	
## command.o lib ##
utils.o: BUILD.H utils.hpp utils.cpp
	g++ -Wall -I"./" -c "utils.cpp"

clean:
	rm $(find . -type f -perm /+u+x) &
	rm *.gch &
	rm *.o
	
BUILD.H:
#nothing
