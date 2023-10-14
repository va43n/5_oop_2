#include "Header.h"

int main() {
	srand(time(NULL));

	try {
		PearsonDistributionType2 pd1(1., 2., 1.);
		PearsonDistributionType2 pd2(-3., 5., 5.);
		double p = 0.5;
		
		Empirical emp(10000, pd1);

		emp.generate_distribution();

		//pd1.generate_distribution();
		
		//test();

		//p.generate_distribution();
	}
	catch (const char* e) {
		std::cout << e;
	}
	
	return 0;
}