#include <cstdio>
#include <ap_int.h>

typedef ap_int<16> data_t;
typedef ap_int<32> acc_t;

const int N_TAPS = 16;
const int N_SAMPLES = 256;

// Prototype of the HLS FIR function
void fir(const data_t x[N_SAMPLES], data_t y[N_SAMPLES]);

int main() {
    data_t x[N_SAMPLES], y[N_SAMPLES];

    // Impulse input = 1 (good for showing FIR coefficients in the output)
    for (int i = 0; i < N_SAMPLES; i++) {
        x[i] = (i == 0) ? 1 : 0;
    }

    fir(x, y);

    // Print first 20 outputs for inspection
    printf("Impulse response (first 20 samples):\n");
    for (int i = 0; i < 20; i++) {
        printf("y[%d] = %d\n", i, (int)y[i]);
    }

    return 0;
}
