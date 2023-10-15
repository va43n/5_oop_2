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

	void generate_distribution();

private:
	void set_moments();
};

class Mixture {
	PearsonDistributionType2 pd1, pd2;
	double p;

public:
	Mixture(PearsonDistributionType2& pd01, PearsonDistributionType2& pd02, double p0 = 0.5) : p(p0 > 0 && p0 < 1 ? p0 : throw "ERROR: Bad p. p should be: 0 < p < 1."), pd1(pd01), pd2(pd02) {}
	Mixture(std::string p_file, std::string pd1_file, std::string pd2_file);

	PearsonDistributionType2& getComponent1() { return pd1; }
	PearsonDistributionType2& getComponent2() { return pd2; }

	double get_p();
	void set_p(double p0);

	double* get_moments();

	double get_f(double x);
	double get_model();

	void load(std::string p_file, std::string pd1_file, std::string pd2_file);
	void save(std::string p_file, std::string pd1_file, std::string pd2_file);

	void generate_distribution();
};

class Empirical {
	int n, k;
	double delta, min;
	int* counter;
	double* data, *frequency, *density;

public:
	Empirical(int n0, PearsonDistributionType2& pd, int k0 = 1);
	Empirical(int n0, Mixture& pd, int k0 = 1);
	Empirical(int n0, Empirical& pd, int k0 = 1);
	Empirical(std::string filename);

	Empirical(const Empirical& emp);
	Empirical& operator=(const Empirical& emp);

	double get_f(double x);
	double get_model();

	double* get_moments();

	void load(std::string filename);
	void save(std::string filename);

	void generate_distribution();

	~Empirical();

private:
	void get_min_delta();
	void get_counter_frequency_density();
};

void test();
void mix_test();
void emp_test();