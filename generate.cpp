#include "Header.h"

void generate_distribution(PearsonDistributionType2 p) {
	std::ofstream file1, file2;
	std::string s_number;
	double number;


	file1.open("x.txt", std::ios::out);
	file2.open("fx.txt", std::ios::out);

	for (int i = 0; i < 10000; i++) {
		number = p.get_model();

		s_number = std::to_string(number);
		s_number[s_number.find(".")] = ',';
		file1 << s_number << "\n";

		s_number = std::to_string(p.get_f(number));
		s_number[s_number.find(".")] = ',';
		file2 << s_number << "\n";
	}

	file1.close();
}