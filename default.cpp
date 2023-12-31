#include "Header.h"

PearsonDistributionType2::PearsonDistributionType2(double mu0, double la0, double nu0) {
	setMU(mu0);
	setLA(la0);
	setNU(nu0);
};

PearsonDistributionType2::PearsonDistributionType2(std::string name) {
	load(name);
}

void PearsonDistributionType2::setMU(double mu0) {
	mu = mu0 >= -10000 && mu0 <= 10000 ? mu0 : throw "ERROR: Bad mu. mu should be: -10000 <= mu <= 10000.";
	set_moments();
}

double PearsonDistributionType2::getMU() {
	return mu;
}

void PearsonDistributionType2::setLA(double la0) {
	la = la0 > 0 && la <= 10000 ? la0 : throw "ERROR: Bad la. la should be: 0 < la <= 10000.";
	set_moments();
}

double PearsonDistributionType2::getLA() {
	return la;
}

void PearsonDistributionType2::setNU(double nu0) {
	nu = nu0 >= 0 && nu <= 10000 ? nu0 : throw "ERROR: Bad nu. nu should be: 0 <= nu <= 10000.";
	set_moments();
}

double PearsonDistributionType2::getNU() {
	return nu;
}

double PearsonDistributionType2::get_f(double x) {
	if (x > -1. * la + mu && x < 1. * la + mu) {
		return pow((1 - pow((x - mu) / la, 2)) / 4., nu) / (2 * std::tgamma(nu + 1) * std::tgamma(nu + 1) / std::tgamma(2 * nu + 2)) / la;
	}
	return 0;
}

void PearsonDistributionType2::set_moments() {
	moments[0] = mu;
	moments[1] = pow(la, 2) / (2 * nu + 3);
	moments[2] = 1 / pow(moments[1], 3. / 2.) * 1 / 3 * (moments[0] - mu);
	moments[3] = -6. / (2 * nu + 5);
}

double* PearsonDistributionType2::get_moments() {
	return moments;
}

double PearsonDistributionType2::get_model() {
	double r1, r2;

	do r1 = (double)rand() / RAND_MAX; while (r1 == 0. || r1 == 1.);
	do r2 = (double)rand() / RAND_MAX; while (r2 == 0. || r2 == 1.);

	return sqrt(1 - pow(r1, 1 / (nu + 1. / 2.))) * cos(2 * PI * r2) * la + mu;
}

void PearsonDistributionType2::load(std::string name) {
	std::ifstream file;
	int counter = 0;
	double temp;
	std::string* args = new std::string[3];

	file.open(name);

	if (file.fail()) {
		throw "ERROR: Bad file name";
	}
	else {
		while (!file.eof() && counter < 3) {
			file >> args[counter];
			counter++;
		}

		if (counter < 3) {
			throw "ERROR: File should consist 3 parameters: mu, la, nu.";
		}

		for (int i = 0; i < 3; i++) {
			try {
				temp = stod(args[i]);
			}
			catch (std::invalid_argument) {
				throw "ERROR: One of the parameters is not a number. Check your file and try again.";
			}
		}

		setMU(stod(args[0]));
		setLA(stod(args[1]));
		setNU(stod(args[2]));
	}
	file.close();
}

void PearsonDistributionType2::save(std::string name) {
	std::ifstream check;
	std::ofstream file;

	check.open(name);

	if (check.fail()) {
		throw "ERROR: Bad file name";
	}
	else {
		check.close();
		file.open(name, std::ios::out);
		file << mu << " " << la << " " << nu;
	}
	file.close();
}

void PearsonDistributionType2::generate_distribution() {
	std::ofstream file1, file2;
	std::string s_number;
	double number;


	file1.open("x.txt", std::ios::out);
	file2.open("fx.txt", std::ios::out);

	for (int i = 0; i < 10000; i++) {
		number = get_model();

		s_number = std::to_string(number);
		s_number[s_number.find(".")] = ',';
		file1 << s_number << "\n";

		s_number = std::to_string(get_f(number));
		s_number[s_number.find(".")] = ',';
		file2 << s_number << "\n";
	}

	file1.close();
	file2.close();
}