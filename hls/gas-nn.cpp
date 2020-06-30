#include "gas-nn.h"

x_data_t sigmoid(x_data_t x);

x_data_t sigmoid(x_data_t x){
	return 1/(1+hls::expf(-x)); //Sigmoid
}

void gas_nn(x_data_t in[D_in], 
             w_data_t w01[D_in][H1],  b_data_t b01[H1],
             w_data_t w12[H1][H2],    b_data_t b12[H2],
             w_data_t w23[H2][D_out], b_data_t b23[D_out],
             x_data_t out[D_out]){
#pragma HLS INTERFACE s_axilite port=out
#pragma HLS INTERFACE s_axilite port=b01
#pragma HLS INTERFACE s_axilite port=b23
#pragma HLS INTERFACE s_axilite port=b12
#pragma HLS INTERFACE s_axilite port=w23
#pragma HLS INTERFACE s_axilite port=in
#pragma HLS INTERFACE s_axilite port=w01
#pragma HLS INTERFACE s_axilite port=w12
#pragma HLS INTERFACE ap_ctrl_none port=return
    
    int i,j;

    x_data_t tmp, inter1[H1], inter2[H2];

    Layer01Ext: for(i=0;i<H1;i++){
        tmp = b01[i];
        Layer01Int: for(j=0;j<D_in;j++){
            tmp += w01[j][i]*in[j];
        }
        inter1[i] = sigmoid(tmp);
    }

    Layer12Ext: for(i=0;i<H2;i++){
        tmp = b12[i];
        Layer12Int: for(j=0;j<H1;j++){
            tmp += w12[j][i]*inter1[j];
        }
        inter2[i] = sigmoid(tmp);
    }

    Layer23Ext: for(i=0;i<D_out;i++){
        tmp = b23[i];
        Layer23Int: for(j=0;j<H2;j++){
            tmp += w23[j][i]*inter2[j];
        }
        out[i] = sigmoid(tmp);
    }
}
