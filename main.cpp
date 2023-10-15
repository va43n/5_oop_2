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

	PearsonDistributionType2 pd1(0., 1., 1.);
	PearsonDistributionType2 pd2(-3.6, 4., 3.);
	MixtureDistribution mix1(pd1, pd2, 0.9);
	EmpiricalDistribution emp1(5120000, mix1);
	EmpiricalDistribution emp2(5120000, emp1);
	mix1.generate_distribution();
	//emp1.generate_distribution();
	//emp2.generate_distribution();
	
	return 0;
}