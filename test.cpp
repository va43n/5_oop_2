#include "Header.h"

void test() {
	double* m;
	double number;
	std::string input[5] = {"f.txt", "file1", "file1.txt", "file2.txt", "file3.txt"};
	std::string output[3] = { "o.txt", "out1", "out1.txt" };

	PearsonDistributionType2 p1;

	//test 1 - first constructor
	std::cout << "\t\t----------test 1----------" << std::endl;
	if (p1.getMU() == 0 && p1.getLA() == 1 && p1.getNU() == 0) {
		std::cout << ":D First constructor is correct:" << std::endl;
	}
	else {
		std::cout << ":C First constructor is incorrect:" << std::endl;
	}
	m = p1.get_moments();
	std::cout << "\tmu la nu: "<< p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
	std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl << std::endl;

	//test 2 - set
	std::cout << "\t\t----------test 2----------" << std::endl;
	p1.setMU(10);
	p1.setLA(5);
	p1.setNU(1);

	if (p1.getMU() == 10 && p1.getLA() == 5 && p1.getNU() == 1) {
		std::cout << ":D If you try to enter correct parameters in set functions all will be correct:" << std::endl;
		std::cout << "\tmu la nu: " << p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
		std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl;
	}
	else {
		std::cout << ":C When you try to enter correct parameters in set functions something is not correct" << std::endl;
		std::cout << "\tmu la nu: " << p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
		std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl;
	}

	try {
		p1.setMU(-100000);
	}
	catch (const char* error) {
		std::cout << ":D If you try to enter incorrect parameter to mu you will get that message:\n\t";
		std::cout << error << std::endl;
		std::cout << "\tmu la nu: " << p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
		std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl;

	}
	try {
		p1.setLA(-10);
	}
	catch (const char* error) {
		std::cout << ":D If you try to enter incorrect parameter to la you will get that message:\n\t";
		std::cout << error << std::endl;
		std::cout << "\tmu la nu: " << p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
		std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl;
	}
	try {
		p1.setNU(-1);
	}
	catch (const char* error) {
		std::cout << ":D If you try to enter incorrect parameter to nu you will get that message:\n\t";
		std::cout << error << std::endl;
		std::cout << "\tmu la nu: " << p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
		std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl << std::endl;
	}

	//test 3 - get_f, get_model
	std::cout << "\t\t----------test 3----------" << std::endl;
	number = 10.;
	std::cout << "get_f(" << number << ") = " << p1.get_f(number) << std::endl;
	number = 14.;
	std::cout << "get_f(" << number << ") = " << p1.get_f(number) << std::endl;
	number = -2.;
	std::cout << "get_f(" << number << ") = " << p1.get_f(number) << std::endl;

	for (int i = 0; i < 5; i++) {
		number = p1.get_model();
		if (number >= p1.getMU() - p1.getLA() && number <= p1.getMU() + p1.getLA()) {
			std::cout << ":D get_model(" << p1.getMU() << ", " << p1.getLA() << ", " << p1.getNU() << ") = " << number << " correct: " << p1.getMU() - p1.getLA() << " <= " << number << " <= " << p1.getMU() + p1.getLA() << std::endl;
		}
		else {
			std::cout << ":C get_model(" << p1.getMU() << ", " << p1.getLA() << ", " << p1.getNU() << ") = " << number << " incorrect" << std::endl;
		}
	}
	std::cout << std::endl;

	//test 4 - load, save
	//file1.txt - ok, file2.txt - not enough params, file3.txt - consist not only numbers
	std::cout << "\t\t----------test 4----------" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "Name of file: " << input[i] << std::endl;
		try {
			p1.load(input[i]);
			std::cout << "\tFile was successfully read." << std::endl;
			std::cout << "\tmu la nu: " << p1.getMU() << " " << p1.getLA() << " " << p1.getNU() << "; " << std::endl;
			std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl;
		}
		catch (const char* error) {
			std::cout << "\t" << error << std::endl;
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < 3; i++) {
		std::cout << "Name of file: " << output[i] << std::endl;
		try {
			p1.save(output[i]);
			std::cout << "\tInformation was successfully entered in the file." << std::endl;
		}
		catch (const char* error) {
			std::cout << "\t" << error << std::endl;
		}
	}
	std::cout << std::endl;

	//test 5 Second constructor
	std::cout << "\t\t----------test 5----------" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "Name of file: " << input[i] << std::endl;
		try {
			PearsonDistributionType2 p2(input[i]);
			std::cout << "\tFile was successfully read." << std::endl;
			std::cout << "\tmu la nu: " << p2.getMU() << " " << p2.getLA() << " " << p2.getNU() << "; " << std::endl;
			std::cout << "\tmoments: " << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << std::endl;
		}
		catch (const char* error) {
			std::cout << "\t" << error << std::endl;
		}
	}
	std::cout << std::endl;
}
