#include "animate.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		animate_demo_usage(argv[0]);
	}
	demo(argv[1]);
	return 0;
}
