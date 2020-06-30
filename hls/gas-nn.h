//#include <cmath>
#include "hls_math.h"
#include "ap_fixed.h"

using namespace std;

#define D_in 16
#define H1 32
#define H2 12
#define D_out 2

typedef ap_fixed<12,3,AP_RND,AP_SAT> b_data_t;
typedef ap_fixed<12,3,AP_RND,AP_SAT> x_data_t;
typedef ap_fixed<12,3,AP_RND,AP_SAT> w_data_t;

void gas_nn(x_data_t in[D_in], 
              w_data_t w01[D_in][H1],  b_data_t b01[H1],
              w_data_t w12[H1][H2],    b_data_t b12[H2],
              w_data_t w23[H2][D_out], b_data_t b23[D_out],
              x_data_t out[D_out]);
