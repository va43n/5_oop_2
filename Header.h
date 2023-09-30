#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>

const double PI = std::acos(-1);

class PearsonDistributionType2 {
	double mu;
	double la;
	double nu;
	double* moments = new double[4];
	
public:
	PearsonDistributionType2(double mu0 = 0, double la0 = 1, double nu0 = 0);
	PearsonDistributionType2(std::string name);

	void setMU(double mu0);
	double getMU();

	void setLA(double la0);
	double getLA();

	void setNU(double nu0);
	double getNU();

	double* get_moments();

	double get_f(double x);
	double get_model();

	void load(std::string name);
	void save(std::string name);

private:
	void set_moments();
};

void test();

void generate_distribution(PearsonDistributionType2 p);