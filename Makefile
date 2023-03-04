demo: .demo.o
	gcc .demo.o .animate.o -o demo -lncursesw

.animate.o: animate_src/animate.c animate_src/animate.h
	gcc -c animate_src/animate.c -o .animate.o

.demo.o: demo_src/demo.c .animate.o
	gcc -c demo_src/demo.c -o .demo.o

clean:
	rm *.o demo demo_debug

cleanob:
	rm *.o

debug:
	gcc -c animate_src/animate.c -ggdb -O0 -o .animate.o
	gcc -c demo_src/demo.c -ggdb -O0 -o .demo.o
	gcc .demo.o .animate.o -o demo_debug -lncursesw
