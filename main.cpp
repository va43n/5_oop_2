#include "Header.h"

int main() {
	srand(time(NULL));
	PearsonDistributionType2 p(4.3, 6.1, 10);

	test();

	generate_distribution(p);
	
	return 0;
}
