## command.o lib ##
command.o: BUILD.H common_files/command.hpp common_files/command.cpp
	g++ -Wall -c "common_files/command.cpp"

clean:
	rm $(find . -type f -perm /+u+x) &
	rm *.gch &
	rm *.o
	
