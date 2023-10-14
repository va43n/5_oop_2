#include "Header.h"

int main() {
	srand(time(NULL));

	try {
		PearsonDistributionType2 pd1(1., 2., 1.);
		PearsonDistributionType2 pd2(-3., 5., 5.);
		double p = 0.5;
		Mixture mix(pd1, pd2, p);

		std::cout << mix.getComponent1().getLA() << " " << mix.getComponent2().getMU();

		
		mix.generate_distribution();

		//test();

		//p.generate_distribution();
	}
	catch (const char* e) {
		std::cout << e;
	}
	
	return 0;
}