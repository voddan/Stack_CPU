output: gen.o enviroment.o
	g++ gen.o enviroment.o -o output
	chmod +x output
	
gen.o: gen.asm
	nasm -f elf64 gen.asm -o gen.o
	
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
