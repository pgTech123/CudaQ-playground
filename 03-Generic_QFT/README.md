# N Qbit QFT

## Goal: Implement a N bit QFT

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```