#include <iostream>
#include <cudaq.h>

#define PI 3.14159265358979323846

__qpu__ void kernel(int qubit_count, int inputValue) {
  cudaq::qvector qubits(qubit_count);

  // Prepare the initial qbit value for the operation
  for (auto i = 0; i < qubit_count; i++) {
    if (inputValue & (0x1 << i)) {
      x(qubits[i]);
    }
  }

  double theta1 = PI/2;
  double theta2 = PI/4;
  double theta3 = PI/8;

  h(qubits[0]);
  cry(theta1, qubits[0], qubits[1]);
  cry(theta2, qubits[0], qubits[2]);
  cry(theta3, qubits[0], qubits[3]);

  h(qubits[1]);
  cry(theta1, qubits[1], qubits[2]);
  cry(theta2, qubits[1], qubits[3]);

  h(qubits[2]);
  cry(theta3, qubits[2], qubits[3]);

  h(qubits[3]);

  swap(qubits[0], qubits[3]);
  swap(qubits[1], qubits[2]);

  mz(qubits);
}

int generateVectorWithFrequency(int frequency, int qubit_count) {
  int inputValue = 0;
  for (auto i = 0; i < qubit_count; i++) {
    if (i % frequency == 0) {
      inputValue = inputValue | (0x1 << i);
    }
  }
  return inputValue;
}

int main(int argc, char *argv[]) {
  auto qubit_count = 4;
  int frequency = 2;
  // Prepare a classic input vector
  int inputValue = generateVectorWithFrequency(frequency, qubit_count);

  // Run the quantum circuit
  auto result = cudaq::sample(kernel, qubit_count, inputValue);

  // Dump all possibilities
  result.dump();

  // Print the most likely
  std::cout << "Most likely: " << result.most_probable() << std::endl;
}
