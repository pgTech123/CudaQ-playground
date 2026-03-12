#include <iostream>
#include <cudaq.h>

#define PI 3.14159265358979323846

#define IS_TRUE(x) { \
if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; \
}

__qpu__ void prepareStateFromClassic(int inputValue, cudaq::qview<> qubits) {
	int qubit_count = qubits.size();
	for (int i = 0; i < qubit_count; i++) {
		if (inputValue & (0x1 << i)) {
			x(qubits[i]);
		}
	}
}

__qpu__ void qft(cudaq::qview<> qubits) {
    int qubit_count = qubits.size();
  	for (int i = 0; i < qubit_count; i++) {
    	double divider = static_cast<double>(1 << (i + 1));
    	double angle = PI / divider;
    	h(qubits[i]);
    	for (int j = i+1; j < qubit_count; j++) {
    		cry(angle, qubits[i], qubits[j]);
    	}
  	}

  	for (int i = 0; i < qubit_count/2; i++) {
    	swap(qubits[i], qubits[qubit_count-i-1]);
  	}
}

__qpu__ void iqft(cudaq::qview<> qubits) {
    int qubit_count = qubits.size();

    for (int i = 0; i < qubit_count/2; i++) {
    	swap(qubits[i], qubits[qubit_count-i-1]);
  	}

  	for (int i = qubit_count-1; i >= 0; i--) {
    	double divider = static_cast<double>(1 << (i + 1));
    	double angle = -PI / divider;
    	for (int j = i+1; j < qubit_count; j++) {
    		cry(angle, qubits[i], qubits[j]);
    	}
    	h(qubits[i]);
  	}
}

// Main kernel
__qpu__ void kernel(int qubit_count, int numberToFactorize) {
	cudaq::qvector qubits_x(qubit_count);
	cudaq::qvector qubits_fx(2 * qubit_count);

	// ---------------------
	// - Prepare the state -
	// ---------------------
	// Hadamar the register to represent all possible integer between 0 and 2^qbit_count
	h(qubits_x);

	// f(qubits_x) = a^qubits_x mod N
	// Initialize fx to 1
	// TODO:
	x(qubits_fx);



	mz(qubits_fx);
}

// Classic functions
int getNumberOfBitsForNumber(int targetNumber) {
	int maxNumberWithBits = 0;
	// Limit to 32 bits
	for (int i = 0; i < 32; i++) {
		if (targetNumber >> i == 0) {
			return i;
		}
	}
	return -1;
}


void testGetNumberOfBitsForNumber() {
	IS_TRUE(getNumberOfBitsForNumber(0) == 0);
	IS_TRUE(getNumberOfBitsForNumber(1) == 1);
	IS_TRUE(getNumberOfBitsForNumber(2) == 2);
	IS_TRUE(getNumberOfBitsForNumber(3) == 2);
	IS_TRUE(getNumberOfBitsForNumber(4) == 3);
	IS_TRUE(getNumberOfBitsForNumber(5) == 3);
	IS_TRUE(getNumberOfBitsForNumber(6) == 3);
	IS_TRUE(getNumberOfBitsForNumber(7) == 3);
	IS_TRUE(getNumberOfBitsForNumber(8) == 4);
	IS_TRUE(getNumberOfBitsForNumber(9) == 4);
	IS_TRUE(getNumberOfBitsForNumber(15) == 4);
	IS_TRUE(getNumberOfBitsForNumber(16) == 5);
	IS_TRUE(getNumberOfBitsForNumber(245) == 8);
}

int main(int argc, char *argv[]) {
	int numberToFactorize = 1 < argc ? atoi(argv[1]) : 55;
	int runTests = true;

	if (runTests) {
		testGetNumberOfBitsForNumber();
	}

	// Get the number of Qbits required
	int numberOfBits = getNumberOfBitsForNumber(numberToFactorize);
	std::cout << numberToFactorize << " has " << numberOfBits << " bits" << std::endl;

	// Run Shor's algorithm
	auto result = cudaq::sample(10000, kernel, numberOfBits, numberToFactorize);

	// The output should be exactly the input
	result.dump();
}
