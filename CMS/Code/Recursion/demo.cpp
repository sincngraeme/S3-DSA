#include "demo.h"

Port::count = 0;

Port::Port() {
    port_name = (char*)malloc(40*sizeof(char));
    // ...
    count++;
}

Port::Port(int baud_rate) {
    port_name = (char*)malloc(40*sizeof(char));
    baud = baud_rate;
    count++;
}

Port::~Port() {
    free(port_name);
    if (fileonep) {close();}
    count--;
}

int Port::sendData(char *data) {
    // do stuff
    return 0;
}

template <class T>
T sum(T a, T b) {
    return a + b;
}
int sum(float a, float b);