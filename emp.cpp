#include "Header.h"

EmpiricalDistribution::EmpiricalDistribution(int n0, PearsonDistributionType2& pd, int k0) : n(n0 > 1 ? n0 : throw "ERROR: Bad n. n should be > 1."), k(k0 > 1 ? k0 : int(log(double(n)) / log(double(2.))) + 1.), data(new double[n]), counter(new int[k]), frequency(new double[k]), density(new double[k]) {
	for (int i = 0; i < n; i++) {
		data[i] = pd.get_model();
	}

	get_min_delta();
	get_counter_frequency_density();
}

EmpiricalDistribution::EmpiricalDistribution(int n0, MixtureDistribution& mix, int k0) : n(n0 > 1 ? n0 : throw "ERROR: Bad n. n should be > 1."), k(k0 > 1 ? k0 : int(log(double(n)) / log(double(2.))) + 1.), data(new double[n]), counter(new int[k]), frequency(new double[k]), density(new double[k]) {
	for (int i = 0; i < n; i++) {
		data[i] = mix.get_model();
	}

	get_min_delta();
	get_counter_frequency_density();
}

EmpiricalDistribution::EmpiricalDistribution(int n0, EmpiricalDistribution& emp, int k0) : n(n0 > 1 ? n0 : throw "ERROR: Bad n. n should be > 1."), k(k0 > 1 ? k0 : int(log(double(n)) / log(double(2.))) + 1.), data(new double[n]), counter(new int[k]), frequency(new double[k]), density(new double[k]) {
	for (int i = 0; i < n; i++) {
		data[i] = emp.get_model();
	}

	get_min_delta();
	get_counter_frequency_density();
}

EmpiricalDistribution::EmpiricalDistribution(std::string filename) {
	load(filename);
}

EmpiricalDistribution::EmpiricalDistribution(const EmpiricalDistribution& emp) {
	n = emp.n;
	k = emp.k;
	min = emp.min;
	delta = emp.delta;

	data = new double[n];
	for (int i = 0; i < n; i++) {
		data[i] = emp.data[i];
	}

	counter = new int[k];
	frequency = new double[k];
	density = new double[k];
	for (int i = 0; i < k; i++) {
		counter[i] = emp.counter[i];
		frequency[i] = emp.frequency[i];
		density[i] = emp.density[i];
	}
}

EmpiricalDistribution::~EmpiricalDistribution() {
	delete[] data, counter, frequency, density;
}

EmpiricalDistribution& EmpiricalDistribution::operator=(const EmpiricalDistribution& emp) {
	if (this == &emp) return *this;

	if (n != emp.n) {
		delete[] data;
		n = emp.n;
		data = new double[n];
	}
	
	if (k != emp.k) {
		delete[] counter, frequency, density;
		k = emp.k;
		counter = new int[k];
		frequency = new double[k];
		density = new double[k];
	}

	for (int i = 0; i < n; i++) {
		data[i] = emp.data[i];
	}

	for (int i = 0; i < k; i++) {
		counter[i] = emp.counter[i];
		frequency[i] = emp.frequency[i];
		density[i] = emp.density[i];
	}

	get_min_delta();

	return *this;
}

void EmpiricalDistribution::get_min_delta() {
	double max = data[0];
	min = data[0];

	for (int i = 0; i < n; i++) {
		if (data[i] > max) {
			max = data[i];
		}
		if (data[i] < min) {
			min = data[i];
		}
	}
	delta = (max - min) / k;
}

void EmpiricalDistribution::get_counter_frequency_density() {
	bool flag;

	counter = new int[k];

	for (int i = 0; i < k; i++) {
		counter[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		flag = false;
		for (int j = 0; j < k; j++) {
			if (data[i] >= min + delta * j && data[i] < min + delta * (j + 1)) {
				counter[j]++;
				flag = true;
				break;
			}
		}
		if (!flag) {
			counter[k - 1]++;
		}
	}

	for (int i = 0; i < k; i++) {
		frequency[i] = counter[i] / (double)n;
		density[i] = frequency[i] / delta;
	}
}

double EmpiricalDistribution::get_f(double x) {
	for (int i = 0; i < k; i++) {
		if (x >= min + i * delta && x < min + (i + 1) * delta) {
			return density[i];
		}
	}
	return density[k - 1];
}

double EmpiricalDistribution::get_model() {
	double r1, r2, sum = 0;

	do r1 = (double)rand() / RAND_MAX; while (r1 == 0. || r1 == 1.);

	for (int i = 0; i < k; i++) {
		sum += frequency[i];
		if (sum > r1) {
			if (i == k - 1) {
				r2 = (double)rand() / RAND_MAX;
			}
			else {
				do r2 = (double)rand() / RAND_MAX; while (r2 == 1.);
			}
			return  min + delta * i + r2 * delta;
		}
	}
	throw "ERROR: Something went wrong.";
}

double* EmpiricalDistribution::get_moments() {
	double* moments = new double[4];

	for (int i = 0; i < 4; i++) {
		moments[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		moments[0] += data[i];
	}
	moments[0] /= (double)n;

	for (int i = 0; i < n; i++) {
		moments[1] += pow(data[i] - moments[0], 2);
	}
	moments[1] /= (double)n;

	for (int i = 0; i < n; i++) {
		moments[2] += pow(data[i] - moments[0], 3);
	}
	moments[2] /= ((double)n * pow(moments[1], 3. / 2.));

	for (int i = 0; i < n; i++) {
		moments[3] += pow(data[i] - moments[0], 4);
	}
	moments[3] = moments[3] / ((double)n * pow(moments[1], 2)) - 3;

	return moments;
}

void EmpiricalDistribution::load(std::string filename) {
	std::ifstream file;
	std::string temp;
	int temp_n;
	double* temp_data;

	file.open(filename);

	if (file.fail()) {
		throw "ERROR: Bad file name";
	}

	if (!file.eof()) {
		file >> temp;
	}
	else {
		throw "ERROR: File should consist n";
	}
	try {
		temp_n = stoi(temp);
	}
	catch (std::invalid_argument) {
		throw "ERROR: n is not a number, check your file and try again";
	}

	if (temp_n <= 1) {
		throw "ERROR: n should be > 1";
	}

	temp_n = stoi(temp);

	temp_data = new double[temp_n];
	for (int i = 0; i < temp_n; i++) {
		if (file.eof()) {
			throw "ERROR: Not enough numbers in data, check your file and try again";
		}
		file >> temp;
		try {
			temp_data[i] = stod(temp);
		}
		catch (std::invalid_argument) {
			throw "ERROR: One of the numbers in data is not a number, check your file and try again";
		}
		temp_data[i] = stod(temp);
	}

	file.close();

	delete[] data;
	delete[] counter;
	delete[] frequency;
	delete[] density;

	n = temp_n;
	data = new double[n];

	k = int(log(double(n)) / log(double(2.))) + 1.;
	counter = new int[k];
	frequency = new double[k];
	density = new double[k];

	for (int i = 0; i < n; i++) {
		data[i] = temp_data[i];
	}

	get_min_delta();
	get_counter_frequency_density();
}

void EmpiricalDistribution::save(std::string filename) {
	std::ifstream check;
	std::ofstream file;

	check.open(filename);

	if (check.fail()) {
		throw "ERROR: Bad file name";
	}

	check.close();
	file.open(filename, std::ios::out);
	file << n << std::endl;

	for (int i = 0; i < n; i++) {
		file << data[i] << " ";
	}

	file.close();
}

void EmpiricalDistribution::generate_distribution() {
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