# N Qbit QFT

## Goal: Implement a N bit QFT

### Sub-goals:
* Output the classic input as a bitstring
* Make a generic kernel for preparing the input
* Make a generic kernel for QFT that can be reused later - [Quantum kernels doc](https://nvidia.github.io/cuda-quantum/latest/specification/cudaq/kernels.html)
* Make a quantum program that is made of many kernels.

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```