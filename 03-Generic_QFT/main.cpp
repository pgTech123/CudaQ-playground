#include <cudaq.h>
#include <math.h>

#define PI 3.14159265358979323846

__qpu__ void kernel(int qubit_count) {
  cudaq::qvector qubits(qubit_count);

  for (auto i = 0; i < qubit_count; i++) {
    double divider = static_cast<double>(1 << (i + 1));
    double angle = PI / divider;
    h(qubits[i]);
    for (auto j = i+1; j < qubit_count; j++) {
      cr1(angle, qubits[i], qubits[j]);
    }
  }

  for (auto i = 0; i < qubit_count/2; i++) {
    swap(qubits[i], qubits[qubit_count-i-1]);
  }

  mz(qubits);
}

int main(int argc, char *argv[]) {
  auto qubit_count = 1 < argc ? atoi(argv[1]) : 8;
  auto result = cudaq::sample(10000, kernel, qubit_count);
  result.dump();
}
