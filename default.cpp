#include "Header.h"

PearsonDistributionType2::PearsonDistributionType2(double mu0 = 0, double la0 = 1, double nu0 = 0) {
	setMU(mu0);
	setLA(la0);
	setNU(nu0);
	set_moments();
};

PearsonDistributionType2::PearsonDistributionType2(std::string name) {
	std::ifstream file;
	int counter = 0;
	double* args = new double[3];

	file.open(name);

	if (file.bad()) {
		throw "Bad file name";
	}
	else {
		while (!file.eof() && counter < 3) {
			file >> args[counter];
			counter++;
		}

		if (counter < 3) {
			throw "File should consist 3 parameters: mu, la, nu.";
		}

		setMU(args[0]);
		setLA(args[1]);
		setNU(args[2]);
		set_moments();
	}
	file.close();
}

void PearsonDistributionType2::setMU(double mu0) {
	mu = mu0 >= -10000 && mu0 <= 10000 ? mu0 : throw "Bad mu. -10000 <= mu <= 10000.";
}

double PearsonDistributionType2::getMU() {
	return mu;
}

void PearsonDistributionType2::setLA(double la0) {
	la = la0 > 0 ? la0 : throw "Bad la. la > 0.";
}

double PearsonDistributionType2::getLA() {
	return la;
}

void PearsonDistributionType2::setNU(double nu0) {
	nu = nu0 >= 0 ? nu0 : throw "Bad nu. nu >= 0.";
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
	double* args = new double[3];

	file.open(name);

	if (file.bad()) {
		throw "Bad file name";
	}
	else {
		while (!file.eof() && counter < 3) {
			file >> args[counter];
			counter++;
		}

		if (counter < 3) {
			throw "File should consist 3 parameters: mu, la, nu.";
		}

		setMU(args[0]);
		setLA(args[1]);
		setNU(args[2]);
		set_moments();
	}
	file.close();
}

void PearsonDistributionType2::save(std::string name) {
	std::ofstream file;

	file.open(name, std::ios::out);

	if (file.bad()) {
		throw "Bad file name";
	}
	else {
		file << mu << " " << la << " " << nu;
	}
	file.close();
}