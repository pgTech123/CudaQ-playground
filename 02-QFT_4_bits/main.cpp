#include <cudaq.h>

#define PI 3.14159265358979323846

__qpu__ void kernel(int qubit_count) {
  cudaq::qvector qubits(qubit_count);

  double theta1 = PI/2;
  h(qubits[0]);
  cr1(theta1, qubits[0], qubits[1]);
  cr1(theta1, qubits[0], qubits[2]);
  cr1(theta1, qubits[0], qubits[3]);

  double theta2 = PI/4;
  h(qubits[1]);
  cr1(theta1, qubits[1], qubits[2]);
  cr1(theta1, qubits[1], qubits[3]);

  double theta3 = PI/8;
  h(qubits[2]);
  cr1(theta3, qubits[2], qubits[3]);

  h(qubits[3]);

  swap(qubits[0], qubits[3]);
  swap(qubits[1], qubits[2]);

  mz(qubits);
}

int main(int argc, char *argv[]) {
  auto qubit_count = 4;
  auto result = cudaq::sample(kernel, qubit_count);
  result.dump();
}
