#include <iostream>
#include <cudaq.h>

#define AND 0
#define NAND 1

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

__qpu__ void NOT_CIRCUIT(bool a) {
	cudaq::qvector qubits(2);
	if (a) {
		x(qubits[0]);
	}
	_NOT(qubits[0], qubits[1]);
	mz(qubits);
}

__qpu__ void AND_CIRCUIT(bool a, bool b) {
	cudaq::qvector qubits(3);
	if (a) {
		x(qubits[0]);
	}
	if (b) {
		x(qubits[1]);
	}
	_AND(qubits[0], qubits[1], qubits[2]);
	mz(qubits);
}

__qpu__ void NAND_CIRCUIT(bool a, bool b) {
	cudaq::qvector qubits(3);
	if (a) {
		x(qubits[0]);
	}
	if (b) {
		x(qubits[1]);
	}
	_NAND(qubits[0], qubits[1], qubits[2]);
	mz(qubits);
}

__qpu__ void NOR_CIRCUIT(bool a, bool b) {
	cudaq::qvector qubits(3);
	if (a) {
		x(qubits[0]);
	}
	if (b) {
		x(qubits[1]);
	}
	_NOR(qubits[0], qubits[1], qubits[2]);
	mz(qubits);
}

__qpu__ void OR_CIRCUIT(bool a, bool b) {
	cudaq::qvector qubits(3);
	if (a) {
		x(qubits[0]);
	}
	if (b) {
		x(qubits[1]);
	}
	_OR(qubits[0], qubits[1], qubits[2]);
	mz(qubits);
}

__qpu__ void XOR_CIRCUIT(bool a, bool b) {
	cudaq::qvector qubits(3);
	if (a) {
		x(qubits[0]);
	}
	if (b) {
		x(qubits[1]);
	}
	_XOR(qubits[0], qubits[1], qubits[2]);
	mz(qubits);
}

int main(int argc, char *argv[]) {
	// Run the quantum QFT than iQFT
	bool classicInputs[4][2] = {
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1},
	};

	// NAND
	std::cout << "NAND" << std::endl;
	for (int i = 0; i < 4; ++i) {
		bool a = classicInputs[i][0];
		bool b = classicInputs[i][1];

		auto result = cudaq::sample(1000, NAND_CIRCUIT, a, b);

 		std::cout << classicInputs[i][0] << classicInputs[i][1] << " -> " << result.most_probable() << "\n"; // prints: `00`
	}

	// AND
	std::cout << "AND" << std::endl;
	for (int i = 0; i < 4; ++i) {
		bool a = classicInputs[i][0];
		bool b = classicInputs[i][1];

		auto result = cudaq::sample(1000, AND_CIRCUIT, a, b);

 		std::cout << classicInputs[i][0] << classicInputs[i][1] << " -> " << result.most_probable() << "\n"; // prints: `00`
	}

	// NOR
	std::cout << "NOR" << std::endl;
	for (int i = 0; i < 4; ++i) {
		bool a = classicInputs[i][0];
		bool b = classicInputs[i][1];

		auto result = cudaq::sample(1000, NOR_CIRCUIT, a, b);

 		std::cout << classicInputs[i][0] << classicInputs[i][1] << " -> " << result.most_probable() << "\n"; // prints: `00`
	}

	// OR
	std::cout << "OR" << std::endl;
	for (int i = 0; i < 4; ++i) {
		bool a = classicInputs[i][0];
		bool b = classicInputs[i][1];

		auto result = cudaq::sample(1000, OR_CIRCUIT, a, b);

 		std::cout << classicInputs[i][0] << classicInputs[i][1] << " -> " << result.most_probable() << "\n"; // prints: `00`
	}

	// OR
	std::cout << "XOR" << std::endl;
	for (int i = 0; i < 4; ++i) {
		bool a = classicInputs[i][0];
		bool b = classicInputs[i][1];

		auto result = cudaq::sample(1000, XOR_CIRCUIT, a, b);

 		std::cout << classicInputs[i][0] << classicInputs[i][1] << " -> " << result.most_probable() << "\n"; // prints: `00`
	}

	// NOT
	std::cout << "NOT" << std::endl;
	for (int i = 0; i < 2; ++i) {
		bool a = classicInputs[i][1];

		auto result = cudaq::sample(1000, NOT_CIRCUIT, a);

 		std::cout << classicInputs[i][1] << " -> " << result.most_probable() << "\n"; // prints: `00`
	}
}
