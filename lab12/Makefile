all: end

main.o:
	gcc -c app/main.c -I ./background/
back.o:
	gcc -c background/back.c -I ./pipes/
read_pipe.o:
	gcc -c pipes/read_pipe.c
write_pipe.o:
	gcc -c pipes/write_pipe.c

end: main.o back.o read_pipe.o write_pipe.o
	gcc main.o back.o read_pipe.o write_pipe.o -o out
	rm -r *.o

