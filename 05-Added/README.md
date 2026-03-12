# N Qbit Adder

## Goal: Implement a N bit Adder

https://quantumcomputing.stackexchange.com/questions/16760/understanding-the-quantum-circuit-for-the-quantum-adder-toffoli-gate


### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```