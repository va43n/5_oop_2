#include "Header.h"

double get_f(double x, double mu, double la, double nu) {
	if (x > -1. * la + mu && x < 1. * la + mu) {
		return pow((1 - pow((x - mu) / la, 2)) / 4., nu) / (2 * std::tgamma(nu + 1) * std::tgamma(nu + 1) / std::tgamma(2 * nu + 2)) / la;
	}
	return 0;
}

double* get_moments(double mu, double la, double nu) {
	double* moments;

	moments = new double[4];

	moments[0] = 1. / 3. * (-1 * get_f(-1, 0, 1, nu) + 1 * get_f(1, 0, 1, nu)) + mu;
	moments[1] = pow(la, 2) / (2 * nu + 3);
	moments[2] = 1 / pow(moments[1], 3. / 2.) * 1 / 3 * (-1 * get_f(1, 0, 1, nu) + 1 * get_f(1, 0, 1, nu));
	moments[3] = -6. / (2 * nu + 5);

	return moments;
}

double get_model(double mu, double la, double nu) {
	double r1, r2;

	do r1 = (double)rand() / RAND_MAX; while (r1 == 0. || r1 == 1.);
	do r2 = (double)rand() / RAND_MAX; while (r2 == 0. || r2 == 1.);

	return sqrt(1 - pow(r1, 1 / (nu + 1. / 2.))) * cos(2 * PI * r2) * la + mu;
}

double check_x(double mu, double la) {
	std::string temp;
	double result;

	while (true) {
		std::cin >> temp;
		try {
			result = stod(temp);
		}
		catch (std::invalid_argument) {
			std::cout << "You should enter only number and \'.\' for real numbers ";
			continue;
		}
		if (!(result >= -1. * la + mu && result <= 1. * la + mu)) {
			std::cout << "x should be more or equal to " << -1. * la + mu << " and less or equal to " << 1. * la + mu << ". Try again: ";
			continue;
		}
		break;
	}
	return result;
}