#include <cstdio>
#include <ap_int.h>

typedef ap_int<16> data_t;
typedef ap_int<32> acc_t;

const int N_TAPS = 16;
const int N_SAMPLES = 256;

void fir(const data_t x[N_SAMPLES], data_t y[N_SAMPLES]);

int main() {
    data_t x[N_SAMPLES], y[N_SAMPLES];

    for (int i = 0; i < N_SAMPLES; i++) {
        x[i] = (i == 0) ? 1 : 0;
    }

    fir(x, y);

    printf("Impulse response (first 20 samples):\n");
    for (int i = 0; i < 20; i++) {
        printf("y[%d] = %d\n", i, (int)y[i]);
    }

    return 0;
}
