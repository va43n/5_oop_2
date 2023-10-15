#include "Header.h"

void test() {
	double* m;
	double number;
	std::string input[5] = {"f.txt", "file1", "file1.txt", "file2.txt", "file3.txt"};
	std::string output[3] = { "o.txt", "out1", "out1.txt" };

	PearsonDistributionType2 p1;


	std::cout << std::endl << std::endl << "\t\t\t\t----------Pearson TEST----------" << std::endl;


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
	p1.setMU(3);
	p1.setLA(5);
	p1.setNU(3);

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
	number = 2.;
	std::cout << "get_f(" << number << ") = " << p1.get_f(number) << std::endl;
	number = -1.;
	std::cout << "get_f(" << number << ") = " << p1.get_f(number) << std::endl;
	number = 10.;
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


	std::cout << std::endl << std::endl << "\t\t\t\t----------Pearson TEST----------" << std::endl;
}

void mix_test() {
	PearsonDistributionType2 pd1(3., 5., 3.);
	PearsonDistributionType2 pd2(-1., 4., 9.);
	double* moments;
	double number;



	std::cout << std::endl << std::endl << "\t\t\t\t----------MIX TEST----------" << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 1----------" << std::endl;
	std::cout << "\t\t----------First constructor" << std::endl;
	Mixture mix1(pd1, pd2);
	if (mix1.get_p() == 0.5) {
		std::cout << ":D First constructor is correct." << std::endl;

		std::cout << "First component: " << pd1.getMU() << " " << pd1.getLA() << " " << pd1.getNU() << std::endl;
		std::cout << "Second component: " << pd2.getMU() << " " << pd2.getLA() << " " << pd2.getNU() << std::endl;

		moments = mix1.get_moments();
		std::cout << "\tmoments: ";
		for (int i = 0; i < 4; i++) {
			std::cout << moments[i] << " ";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << ":C First constructor is incorrect." << std::endl;
	}



	//
	std::cout << std::endl << std::endl << "\t\t----------test 2----------" << std::endl;
	std::cout << "\t\t----------set_p" << std::endl;

	std::cout << "set p = 0.6" << std::endl;
	mix1.set_p(0.6);
	std::cout << "p = " << mix1.get_p() << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 3----------" << std::endl;
	std::cout << "\t\t----------Enter wrong p (1.5) to constructor and \"set_p()\"" << std::endl;

	try {
		Mixture mix2(pd1, pd2, 1.5);
	}
	catch (const char* e) {
		std::cout << e << std::endl;
	}

	try {
		mix1.set_p(1.5);
	}
	catch (const char* e) {
		std::cout << e << std::endl;
	}



	//
	std::cout << std::endl << std::endl << "\t\t----------test 4----------" << std::endl;
	std::cout << "\t\t----------Get and set mu, la, nu of Pearson distributions in mix distribution" << std::endl;

	std::cout << "GET:" << std::endl;
	std::cout << "mu of the first component: " << mix1.getComponent1().getMU() << std::endl;
	std::cout << "la of the first component: " << mix1.getComponent1().getLA() << std::endl;
	std::cout << "nu of the first component: " << mix1.getComponent1().getNU() << std::endl;
	std::cout << "mu of the second component: " << mix1.getComponent2().getMU() << std::endl;
	std::cout << "la of the second component: " << mix1.getComponent2().getLA() << std::endl;
	std::cout << "nu of the second component: " << mix1.getComponent2().getNU() << std::endl << std::endl;

	std::cout << "SET:" << std::endl;
	mix1.getComponent1().setNU(2);
	std::cout << "Set nu of the first component " << mix1.getComponent1().getNU() << std::endl;
	mix1.getComponent1().setLA(8);
	std::cout << "Set la of the first component " << mix1.getComponent1().getLA() << std::endl;
	mix1.getComponent2().setMU(-4);
	std::cout << "Set mu of the second component " << mix1.getComponent2().getMU() << std::endl;
	mix1.getComponent2().setNU(6);
	std::cout << "Set nu of the second component " << mix1.getComponent2().getNU() << std::endl << std::endl;

	std::cout << "GET:" << std::endl;
	std::cout << "mu of the first component: " << mix1.getComponent1().getMU() << std::endl;
	std::cout << "la of the first component: " << mix1.getComponent1().getLA() << std::endl;
	std::cout << "nu of the first component: " << mix1.getComponent1().getNU() << std::endl;
	std::cout << "mu of the second component: " << mix1.getComponent2().getMU() << std::endl;
	std::cout << "la of the second component: " << mix1.getComponent2().getLA() << std::endl;
	std::cout << "nu of the second component: " << mix1.getComponent2().getNU() << std::endl << std::endl;

	std::cout << "WROND SET:" << std::endl;
	std::cout << "Try to set 100000 to mu of the first component:" << std::endl;
	try {
		mix1.getComponent1().setMU(100000);
	}
	catch (const char* e) {
		std::cout << e << std::endl;
	}
	std::cout << "Try to set -4 to la of the second component:" << std::endl;
	try {
		mix1.getComponent2().setLA(-4);
	}
	catch (const char* e) {
		std::cout << e << std::endl;
	}



	//
	std::cout << std::endl << std::endl << "\t\t----------test 5----------" << std::endl;
	std::cout << "\t\t----------get_f, get_model" << std::endl;

	std::cout << "get_f(" << 3 << ") = " << mix1.get_f(3) << std::endl;
	std::cout << "get_f(" << 0 << ") = " << mix1.get_f(0) << std::endl;
	std::cout << "get_f(" << 20 << ") = " << mix1.get_f(20) << std::endl << std::endl;

	for (int i = 0; i < 5; i++) {
		number = mix1.get_model();
		if (number >= mix1.getComponent1().getMU() - mix1.getComponent1().getLA() && number <= mix1.getComponent1().getMU() + mix1.getComponent1().getLA() || number >= mix1.getComponent2().getMU() - mix1.getComponent2().getLA() && number <= mix1.getComponent2().getMU() + mix1.getComponent2().getLA()) {
			std::cout << ":D get_model(" << mix1.getComponent1().getMU() << ", " << mix1.getComponent1().getLA() << ", " << mix1.getComponent1().getNU() << ", " << mix1.getComponent2().getMU() << ", " << mix1.getComponent2().getLA() << ", " << mix1.getComponent2().getNU() << ", p = " << mix1.get_p() << ") = " << number << " correct." << std::endl;
		}
		else {
			std::cout << ":C get_model(" << mix1.getComponent1().getMU() << ", " << mix1.getComponent1().getLA() << ", " << mix1.getComponent1().getNU() << ", " << mix1.getComponent2().getMU() << ", " << mix1.getComponent2().getLA() << ", " << mix1.getComponent2().getNU() << ", p = " << mix1.get_p() << ") = " << number << " incorrect" << std::endl;
		}
	}
	std::cout << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 6----------" << std::endl;
	std::cout << "\t\t----------save, load" << std::endl;

	std::cout << "SAVE: p - file1.txt, first component - file2.txt, second component - file3.txt" << std::endl << std::endl;
	mix1.save("file1.txt", "file2.txt", "file3.txt");

	Mixture mix2("file1.txt", "file2.txt", "file3.txt");
	std::cout << "LOAD: p - file1.txt, first component - file2.txt, second component - file3.txt" << std::endl;
	std::cout << "p: " << mix2.get_p() << std::endl;
	std::cout << "mu of the first component: " << mix2.getComponent1().getMU() << std::endl;
	std::cout << "la of the first component: " << mix2.getComponent1().getLA() << std::endl;
	std::cout << "nu of the first component: " << mix2.getComponent1().getNU() << std::endl;
	std::cout << "mu of the second component: " << mix2.getComponent2().getMU() << std::endl;
	std::cout << "la of the second component: " << mix2.getComponent2().getLA() << std::endl;
	std::cout << "nu of the second component: " << mix2.getComponent2().getNU() << std::endl;


	std::cout << std::endl << std::endl << "\t\t\t\t----------MIX TEST----------" << std::endl;
}

void emp_test() {
	PearsonDistributionType2 pd1(3., 5., 3.);
	PearsonDistributionType2 pd2(-1., 4., 5.);
	Mixture mix1(pd1, pd2, 0.6);
	double number;
	double* moments;



	std::cout << std::endl << std::endl << "\t\t\t\t----------EMP TEST----------" << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 1----------" << std::endl;
	std::cout << "\t\t----------First constructor" << std::endl;
	std::cout << "(Pearson distribution)" << std::endl;
	Empirical emp1(10000, pd1);
	//emp1.generate_distribution();
	//pd1.generate_distribution();
	std::cout << "Check emp_test1_1.png" << std::endl << std::endl;

	std::cout << "(Mixture distribution)" << std::endl;
	Empirical emp2(10000, mix1);
	//emp2.generate_distribution();
	//mix1.generate_distribution();
	std::cout << "Check emp_test1_2.png" << std::endl << std::endl;

	std::cout << "(Empirical distribution)" << std::endl;
	Empirical emp3(10000, emp2);
	//emp3.generate_distribution();
	//emp2.generate_distribution();
	std::cout << "Check emp_test1_3.png" << std::endl << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 2----------" << std::endl;
	std::cout << "\t\t----------First constructor, set k = 3" << std::endl;
	Empirical emp4(10000, pd2, 3);
	//emp4.generate_distribution();
	//pd2.generate_distribution();
	std::cout << "Check emp_test2_1.png" << std::endl << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 3----------" << std::endl;
	std::cout << "\t\t----------get_moments, get_f, get_model" << std::endl;

	std::cout << "mu of Pearson distribution: " << pd1.getMU() << std::endl;
	std::cout << "la of Pearson distribution: " << pd1.getLA() << std::endl;
	std::cout << "nu of Pearson distribution: " << pd1.getNU() << std::endl << std::endl;

	std::cout << "GET_MOMENTS" << std::endl;
	std::cout << "Moments of Pearson distribution:" << std::endl;
	std::cout << pd1.get_moments()[0] << " " << pd1.get_moments()[1] << " " << pd1.get_moments()[2] << " " << pd1.get_moments()[3] << std::endl;

	moments = emp1.get_moments();
	std::cout << "Moments of copied version of Pearson distribution:" << std::endl;
	std::cout << moments[0] << " " << moments[1] << " " << moments[2] << " " << moments[3] << std::endl << std::endl;

	std::cout << "GET_F" << std::endl;
	std::cout << "get_f(" << 2 << ") = " << emp1.get_f(2) << std::endl;
	std::cout << "get_f(" << -1 << ") = " << emp1.get_f(-1) << std::endl;
	std::cout << "get_f(" << 10 << ") = " << emp1.get_f(10) << std::endl << std::endl;

	std::cout << "GET_MODEL" << std::endl;
	for (int i = 0; i < 5; i++) {
		number = emp1.get_model();
		if (number >= pd1.getMU() - pd1.getLA() && number <= pd1.getMU() + pd1.getLA()) {
			std::cout << ":D empirical get_model of pearson distribution (" << pd1.getMU() << ", " << pd1.getLA() << ", " << pd1.getNU() << ") = " << number << " correct: " << pd1.getMU() - pd1.getLA() << " <= " << number << " <= " << pd1.getMU() + pd1.getLA() << std::endl;
		}
		else {
			std::cout << ":C empirical get_model of pearson distribution (" << pd1.getMU() << ", " << pd1.getLA() << ", " << pd1.getNU() << ") = " << number << " incorrect" << std::endl;
		}
	}
	std::cout << std::endl;



	//
	std::cout << std::endl << std::endl << "\t\t----------test 4----------" << std::endl;
	std::cout << "\t\t----------load, save" << std::endl;

	std::cout << "SAVE IN file1.txt:" << std::endl;
	emp1.save("file1.txt");
	std::cout << "Check file1.txt." << std::endl << std::endl;


	std::cout << "LOAD FROM file1.txt:" << std::endl;

	emp2.load("file1.txt");
	std::cout << "moments:" << std::endl;
	moments = emp1.get_moments();
	std::cout << moments[0] << " " << moments[1] << " " << moments[2] << " " << moments[3] << std::endl << std::endl;

	std::cout << "TRY TO LOAD FROM BAD FILES:" << std::endl;
	std::string filenames[] = { "emp_test_1.txt", "emp_test_2.txt", "emp_test_3.txt", "emp_test_4.txt" };
	for (int i = 0; i < 4; i++) {
		try {
			emp2.load(filenames[i]);
		}
		catch (const char* e) {
			std::cout << e << std::endl;
		}
	}



	//
	std::cout << std::endl << std::endl << "\t\t----------test 5----------" << std::endl;
	std::cout << "\t\t----------\operator \"=\" and copy constructor" << std::endl;

	std::cout << "OPERATOR \"=\":" << std::endl;
	Empirical emp5(1000, pd2);
	emp5 = emp1;
	moments = emp1.get_moments();
	std::cout << "Moments of start empirical distribution:" << std::endl;
	std::cout << moments[0] << " " << moments[1] << " " << moments[2] << " " << moments[3] << std::endl;

	moments = emp5.get_moments();
	std::cout << "Moments of copied version of start empirical distribution:" << std::endl;
	std::cout << moments[0] << " " << moments[1] << " " << moments[2] << " " << moments[3] << std::endl << std::endl;

	std::cout << "COPY CONSTRUCTOR:" << std::endl;
	Empirical emp6 = emp1;
	moments = emp1.get_moments();
	std::cout << "Moments of start empirical distribution:" << std::endl;
	std::cout << moments[0] << " " << moments[1] << " " << moments[2] << " " << moments[3] << std::endl;

	moments = emp6.get_moments();
	std::cout << "Moments of copied version of start empirical distribution:" << std::endl;
	std::cout << moments[0] << " " << moments[1] << " " << moments[2] << " " << moments[3] << std::endl << std::endl;




	std::cout << std::endl << std::endl << "\t\t\t\t----------EMP TEST----------" << std::endl;
}