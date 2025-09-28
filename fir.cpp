#include <ap_int.h>

typedef ap_int<16> data_t;   // 16-bit signed input/output
typedef ap_int<32> acc_t;    // wider accumulator

const int N_TAPS = 16;
const int N_SAMPLES = 256;

static const data_t COEFFS[N_TAPS] = {
    1,  2,  0, -3,  0,  4, -5,  0,
    1, -2,  0, -3,  0,  4, -5,  0
};

// Top-level FIR filter
void fir(const data_t x[N_SAMPLES], data_t y[N_SAMPLES]) {
#pragma HLS INTERFACE mode=ap_ctrl_hs port=return
#pragma HLS INTERFACE mode=ap_memory port=x
#pragma HLS INTERFACE mode=ap_memory port=y

    data_t shift_reg[N_TAPS] = {0};

main_loop:
    for (int n = 0; n < N_SAMPLES; n++) {
#pragma HLS PIPELINE II=1   // you can remove or change this later for optimization experiments
        // shift register
        for (int t = N_TAPS - 1; t > 0; t--) {
            shift_reg[t] = shift_reg[t - 1];
        }
        shift_reg[0] = x[n];

        // multiply-accumulate
        acc_t acc = 0;
        for (int t = 0; t < N_TAPS; t++) {
            acc += (acc_t)shift_reg[t] * (acc_t)COEFFS[t];
        }

        // truncate back to 16-bit output
        y[n] = (data_t)acc;
    }
}
