#include <iostream>
#include <cudaq.h>

#define PI 3.14159265358979323846


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
__qpu__ void kernel(int qubit_count, int inputValue) {
	cudaq::qvector qubits(qubit_count);

	prepareStateFromClassic(inputValue, qubits);

	// Make a QFT then an iQFT. Should get back exactly with the original input
	qft(qubits);
	iqft(qubits);

	mz(qubits);
}

// Classic functions
int generateVectorWithFrequency(int frequency, int qubit_count) {
  int inputValue = 0;
  for (int i = 0; i < qubit_count; i++) {
    if (i % frequency == 0) {
      inputValue = inputValue | (0x1 << i);
    }
  }
  return inputValue;
}

int main(int argc, char *argv[]) {
	int qubit_count = 1 < argc ? atoi(argv[1]) : 20;
	int frequency = 2 < argc ? atoi(argv[2]) : 5;

	// Generate a classic input vector
	int inputValue = generateVectorWithFrequency(frequency, qubit_count);

	// Print classic input value
	std::cout << "Classic input value:";
	for (int i = 0; i < qubit_count; i++) {
		std::cout << ((inputValue & (0x1 << i)) >> i);
	}
	std::cout << std::endl;

	// Run the quantum QFT than iQFT
	auto result = cudaq::sample(10000, kernel, qubit_count, inputValue);

	// The output should be exactly the input
	result.dump();
}
