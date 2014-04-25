output: generated.o enviroment.o
	g++ generated.o enviroment.o -o output
	chmod +x output
	
generated.o: generated.asm
	nasm -f elf64 generated.asm -o generated.o
	
enviroment.o: enviroment.cpp
	g++ -Wall -c enviroment.cpp -o enviroment.o
	
clean:
	rm `find . -type f -perm /+u+x` -f
	rm *.gch -f 
	rm *.o -f
	
run: clean output
	@ls
	@echo "|------------------------------------"
	./output
