#include "Header.h"

int main() {
	srand(time(NULL));

	try {
		test();
		mix_test();
		emp_test();
	}
	catch (const char* e) {
		std::cout << e;
	}
	
	return 0;
}