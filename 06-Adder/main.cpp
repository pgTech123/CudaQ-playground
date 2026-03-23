#include <iostream>
#include <cudaq.h>

__qpu__ void _NOT(cudaq::qubit& a, cudaq::qubit& out) {
    x(out);
    cx(a, out);
}

__qpu__ void _AND(cudaq::qubit& a, cudaq::qubit& b, cudaq::qubit& out) {
	x<cudaq::ctrl>(a, b, out);
}

__qpu__ void _NAND(cudaq::qubit& a, cudaq::qubit& b, cudaq::qubit& out) {
	x(out);
	x<cudaq::ctrl>(a, b, out);
}

__qpu__ void _NOR(cudaq::qubit& a, cudaq::qubit& b, cudaq::qubit& out) {
	x(a);
	x(b);
	x<cudaq::ctrl>(a, b, out);
}

__qpu__ void _OR(cudaq::qubit& a, cudaq::qubit& b, cudaq::qubit& out) {
	x(a);
	x(b);
	x<cudaq::ctrl>(a, b, out);
	x(out);
}

__qpu__ void _XOR(cudaq::qubit& a, cudaq::qubit& b, cudaq::qubit& out) {
    cx(a, out);
    cx(b, out);
}

__qpu__ void _SINGLE_BIT_ADDER(cudaq::qubit& a, cudaq::qubit& b,  cudaq::qubit& cin, cudaq::qubit& out, cudaq::qubit& cout) {
	cudaq::qubit aXORb;
	cudaq::qubit aANDb;
	cudaq::qubit aXORb_ANDcin;

	_XOR(a, b, aXORb);
	_AND(a, b, aANDb);
	_XOR(aXORb, cin, out);
	_AND(aXORb, cin, aXORb_ANDcin);
	_OR(aXORb_ANDcin, aANDb, cout);
}


__qpu__ void SINGLE_BIT_ADDER_CIRCUIT(bool a, bool b, bool cin) {
	cudaq::qvector qubits(5);
	if (a) {
		x(qubits[0]);
	}
	if (b) {
		x(qubits[1]);
	}
	if (cin) {
		x(qubits[2]);
	}
	_SINGLE_BIT_ADDER(qubits[0], qubits[1], qubits[2], qubits[3], qubits[4]);
	mz(qubits);
}




int main(int argc, char *argv[]) {
	// Run the quantum QFT than iQFT
	bool classicInputs[8][3] = {
		{0, 0, 0},
		{0, 1, 0},
		{1, 0, 0},
		{1, 1, 0},
		{0, 0, 1},
		{0, 1, 1},
		{1, 0, 1},
		{1, 1, 1},
	};

	// NAND
	std::cout << "SINGLE BIT ADDER" << std::endl;
	for (int i = 0; i < 8; ++i) {
		bool a = classicInputs[i][0];
		bool b = classicInputs[i][1];
		bool cin = classicInputs[i][2];

		auto result = cudaq::sample(1000, SINGLE_BIT_ADDER_CIRCUIT, a, b, cin);

 		std::cout << classicInputs[i][0] << classicInputs[i][1] << classicInputs[i][2] << " -> " << result.most_probable() << "\n";
	}
}
