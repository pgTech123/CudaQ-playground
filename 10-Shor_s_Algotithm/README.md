# N Qbit iQFT

## Goal: Implement Shor's algorithm for an Integer of N bits

### Sub-goals:
* Understand precisely how [Shor's Algorithm](https://greencompute.uk/References/QuantumComputing/Shor%20(1994)%20-%20algorithms%20for%20QC,%20discrete%20logarithms%20and%20factoring.pdf) works.
* Implement it (without any performance optimization in mind at this point)

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```