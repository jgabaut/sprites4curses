demo: demo.o
	gcc demo.o animate.o -o demo -lncursesw

animate.o: animate.c animate.h
	gcc -c animate.c

demo.o: demo.c animate.o
	gcc -c demo.c 

clean:
	rm *.o demo

cleanob:
	rm *.o
