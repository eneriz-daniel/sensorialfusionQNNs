#include "gas-nn.h"
#include <stdio.h>
#include <iostream>

int main(){

    x_data_t out[D_out], in[D_in];
    w_data_t w01[D_in][H1],  w12[H1][H2], w23[H2][D_out];
    b_data_t b01[H1], b12[H2], b23[D_out];

    int i, j, k;
    float t, out_real[D_out], out_py[D_out], tmp;

    cout << "Program start\nReading parameters...";

    FILE *fparam;
    fparam = fopen("C:/Users/eneri/OneDrive/Universidad/Master/TFM/OpenHarwareXilinx/hls/eth-ch4-params-quant.txt","r");
    if(fparam == NULL){
        cout << "Error openning the parameters' file" << endl;
        return 0;
    }

    //Reading w01
    for(i=0;i<H1;i++){
        for(j=0;j<D_in;j++){
            fscanf(fparam,"%f ",&tmp);
            w01[j][i] = tmp;
        }
        fscanf(fparam,"\n");
    }

    //Reading b01
    for(i=0;i<H1;i++){
        fscanf(fparam,"%f\n",&tmp);
        b01[i] = tmp;
    }

    //Reading w12
    for(i=0;i<H2;i++){
        for(j=0;j<H1;j++){
            fscanf(fparam,"%f ",&tmp);
            w12[j][i] = tmp;
        }
        fscanf(fparam,"\n");
    }

    //Reading b12
    for(i=0;i<H2;i++){
        fscanf(fparam,"%f\n",&tmp);
        b12[i] = tmp;
    }

    //Reading w23
    for(i=0;i<D_out;i++){
        for(j=0;j<H2;j++){
            fscanf(fparam,"%f ",&tmp);
            w23[j][i] = tmp;
        }
        fscanf(fparam,"\n");
    }

    //Reading b23
    for(i=0;i<D_out;i++){
        fscanf(fparam,"%f\n",&tmp);
        b23[i] = tmp;
    }

    fclose(fparam);


    cout << "OK\nOpening test file...";

    FILE *fin;
    fin = fopen("C:/Users/eneri/OneDrive/Universidad/Master/TFM/OpenHarwareXilinx/hls/ethylene_methane_quant_0-100000.txt", "r");
    if(fin == NULL){
        cout << "Error openning test file" << endl;
        return 0;
    }

    fscanf(fin,"# Time(s) CH4r(norm) Ethr(norm) CH4p(norm) Ethp(norm) filtered sensor readings (16 channels)\n");

    cout << "OK\nOpening output file...";

    FILE *fout;
    fout = fopen("out_ethylene_methane.txt", "w");
    if(fout == NULL){
        cout << "Error opening the output file" << endl;
        return 0;
    }

    fprintf(fout, "Temp(s) CH4real Ethreal CH4py Ethpy CH4pp Ethcpp\n");

    cout << "OK\nStarting the test\n";

    k=1;

    while(k<200){
        cout << "\tLine " << k << "...";

        fscanf(fin, "%f %f %f %f %f ", &t,
                                       &out_real[0],
                                       &out_real[1],
                                       &out_py[0],
                                       &out_py[1]);
        for(i=0;i<D_in;i++){
        	fscanf(fin,"%f ", &tmp);
        	in[i] = tmp;
        }
        fscanf(fin, "\n");


        gas_nn(in, w01, b01, w12, b12, w23, b23, out);

        fprintf(fout, "%f %f %f %f %f %f %f\n", t,
                                                out_real[0],
                                                out_real[1],
                                                out_py[0],
                                                out_py[1],
                                                (float)out[0],
                                                (float)out[1]);

        
        cout << "OK\n";
        k++;
    }

    return 0; //We know we should use a golden output file to validate the
              //desing but we doesn't have a golden output until we simulate
              //it on Vivado HLS. We are validationg our desing comparing its
              //outputs with the PyTorch performance.
}

