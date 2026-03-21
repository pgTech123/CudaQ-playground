# Implement classic logic with quantum gates

## Goal: implement a set of classic gates with quantum gates

https://en.wikipedia.org/wiki/Toffoli_gate

### With Nvidia GPU
```
nvq++ main.cpp -o main.x --target nvidia && ./main.x
```

### Without Nvidia GPU
```
nvq++ main.cpp -o main.x && ./main.x
```