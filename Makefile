demo: demo.o
	gcc demo.o animate.o -o demo -lncursesw

animate.o: animate.c animate.h
	gcc -c animate.c

demo.o: demo.c animate.o
	gcc -c demo.c 

clean:
	rm *.o demo demo_debug

cleanob:
	rm *.o

debug:
	gcc -c animate.c -ggdb -O0
	gcc -c demo.c -ggdb -O0
	gcc demo.o animate.o -o demo_debug -lncursesw
