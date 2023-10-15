#include "Header.h"

MixtureDistribution::MixtureDistribution(std::string p_file, std::string pd1_file, std::string pd2_file) {
	load(p_file, pd1_file, pd2_file);
}

double MixtureDistribution::get_p() {
	return p;
}

void MixtureDistribution::set_p(double p0) {
	p = p0 > 0 && p0 < 1 ? p0 : throw "ERROR: Bad p. p should be: 0 < p < 1.";
}

double* MixtureDistribution::get_moments() {
	double* moments = new double[4];
	double* moments1 = pd1.get_moments();
	double* moments2 = pd2.get_moments();

	moments[0] = (1. - p) * moments1[0] + p * moments2[0];
	moments[1] = (1. - p) * (pow(moments1[0], 2) + moments1[1]) + p * (pow(moments2[0], 2) + moments2[1]) - pow(moments[0], 2);
	moments[2] = 1. / pow(moments[1], 3. / 2.) * ((1 - p) * (pow(moments1[0] - moments[0], 3) + 3 * moments1[1] * (moments1[0] - moments[0]) + pow(moments1[1], 3. / 2.) * moments1[2]) + (1 - p) * (pow(moments2[0] - moments[0], 3) + 3 * moments2[1] * (moments2[0] - moments[0]) + pow(moments2[1], 3. / 2.) * moments2[2]));
	moments[3] = 1. / pow(moments[1], 2) * ((1 - p) * (pow(moments1[0] - moments[0], 4) + 6 * moments1[1] * pow(moments1[0] - moments[0], 2) + 4 * (moments1[0] - moments[0]) * pow(moments1[1], 3. / 2.) * moments1[2] + pow(moments1[1], 2) * moments1[3]) + p * (pow(moments2[0] - moments[0], 4) + 6 * moments2[1] * pow(moments2[0] - moments[0], 2) + 4 * (moments2[0] - moments[0]) * pow(moments2[1], 3. / 2.) * moments2[2] + pow(moments2[1], 2) * moments2[3])) - 3;

	return moments;
}

double MixtureDistribution::get_f(double x) {
	return (1. - p) * pd1.get_f(x) + p * pd2.get_f(x);
}

double MixtureDistribution::get_model() {
	double r;

	do r = (double)rand() / RAND_MAX; while (r == 0. || r == 1.);
	if (r > p) {
		return pd1.get_model();
	}
	return pd2.get_model();
}

void MixtureDistribution::load(std::string p_file, std::string pd1_file, std::string pd2_file) {
	std::ifstream file;
	std::string str_p;

	file.open(p_file);

	if (file.fail()) {
		throw "ERROR: Bad file name";
	}

	if (!file.eof()) {
		file >> str_p;
	}
	else {
		throw "ERROR: File should consist mix parameter";
	}

	file.close();

	try {
		p = stod(str_p);
	}
	catch (std::invalid_argument) {
		throw "ERROR: p is not a number. Check your file and try again.";
	}

	pd1.load(pd1_file);
	pd2.load(pd2_file);
}

void MixtureDistribution::save(std::string p_file, std::string pd1_file, std::string pd2_file) {
	std::ifstream check;
	std::ofstream file;

	check.open(p_file);

	if (check.fail()) {
		throw "ERROR: Bad file name";
	}
	else {
		check.close();
		file.open(p_file, std::ios::out);
		file << p;
	}
	file.close();

	pd1.save(pd1_file);
	pd2.save(pd2_file);
}

void MixtureDistribution::generate_distribution() {
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