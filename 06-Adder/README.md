# Implement a classic adder with quantum gates

## Goal: understand the internal of complex classic/quantum circuits
* Each net is a qbit. Some nets are internal and can stay within a qpu kernel.
* On a real qpu, we would likely have to do additional operations to make sure internal states are not entangled anymore at the end of the kernel to prevent function wave collapse from qubits that are no longer in use.

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```