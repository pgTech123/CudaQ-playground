# Hello World a.k.a Quantum intrication

## Goal: Test the setup

Get the code from [Nvidia Cuda-Q getting started page](https://nvidia.github.io/cuda-quantum/latest/using/quick_start.html). 
This is a good starting point to check your local configs and
make sure everything works. 

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```