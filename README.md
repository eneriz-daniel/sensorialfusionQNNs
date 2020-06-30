# Sensorial fusion via QNNs

## Project info
* Team number: xohw20_215

* Project name: Sensorial fusion via QNNs

* Date: 30/06/2020

* Version of uploaded archive: 1.0

* University name: University of Zaragoza

* Supervisor name: Nicolas Medrano

* Supervisor e-mail: nmedrano@unizar.es

* Participant(s): Daniel Enériz Orta

* Email: eneriz.daniel@gmail.com

* Board used: PYNQ-Z2

* Software Version: 2.5.1

* Brief description of project: This project presents the design, implementation and usage of a quantized neural network implemented over the PYNQ's FPGA to perform sensorial fusion, concretely the combination of 16 gas sensors to estimate the concentration level of to gases on the atmosphere.

* Link to project repository: https://github.com/eneriz-daniel/sensorialfusionQNNs

## Archive description

* The [Virtualization notebook](Virtualization.ipynb) contains all the steps to process the raw data taken from [Fonollosa et al. 'Reservoir Computing compensates slow response of chemosensor arrays exposed to fast varying gas concentrations in continuous monitoring'; Sensors and Actuators B, 2015](https://archive.ics.uci.edu/ml/datasets/gas+sensor+array+under+dynamic+gas+mixtures) and to train the model using PyTorch in two stages, quantizing the parameters in the second one.

* The [/filtered-data](/filtered-data) folder contains a .txt file with the data normalized and filtered as it is done on the Virtualization notebook.

* The /hls folder contains the Vivado HLS C/C++ sources for the neurakl network description ([gas_nn.cpp](/hls/gas-nn.cpp) and [gas_nn.h](/hls/gas-nn.h)) and the [test bench](/hls/gas-nn-tb.cpp). There are also there the [file containing the quantized parameters trained on PyTorch](/hls/eth-ch4-params-quant.txt), [the file to test the HLS implementation](/hls/ethylene_methane_quant_0-100000.txt). Additionally, the [exported IP .zip file](/hls/xilinx_com_hls_gas_nn_1_0.zip) it is also there



Instructions to build and test project

Step 1:
...

Link to YouTube Video(s):
