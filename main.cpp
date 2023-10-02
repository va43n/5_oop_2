#include "Header.h"

int main() {
	srand(time(NULL));
	PearsonDistributionType2 p(4.3, 6.1, 10);

	test();

	p.generate_distribution();
	
	return 0;
}
