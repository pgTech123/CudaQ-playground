# 4 Qbit QFT

## Goal: Implement a 4 bit QFT

### Sub-goals: 
* Prepare a classical input value to for a quantum program
* Output the most likely answer to the problem
* Familiarize with quantum operations - [Quantum operations](https://nvidia.github.io/cuda-quantum/latest/api/default_ops.html)

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```