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

* Software Version: PYNQ image 2.5.1

* Brief description of project: This project presents the design, implementation and usage of a quantized neural network implemented over the PYNQ's FPGA to perform sensorial fusion, concretely the combination of 16 gas sensors to estimate the concentration level of to gases on the atmosphere.

* Link to project repository: https://github.com/eneriz-daniel/sensorialfusionQNNs

## Archive description

* The [Virtualization notebook](Virtualization.ipynb) contains all the steps to process the raw data taken from [Fonollosa et al. 'Reservoir Computing compensates slow response of chemosensor arrays exposed to fast varying gas concentrations in continuous monitoring'; Sensors and Actuators B, 2015](https://archive.ics.uci.edu/ml/datasets/gas+sensor+array+under+dynamic+gas+mixtures) and to train the model using PyTorch in two stages, quantizing the parameters in the second one.

* The [/filtered-data](/filtered-data) folder contains a .txt file with the data normalized and filtered as it is done on the Virtualization notebook.

* The [/hls](/hls) folder contains the Vivado HLS C/C++ sources for the neurakl network description ([gas-nn.cpp](/hls/gas-nn.cpp) and [gas-nn.h](/hls/gas-nn.h)) and the [test bench](/hls/gas-nn-tb.cpp). There are also there the [file containing the quantized parameters trained on PyTorch](/hls/eth-ch4-params-quant.txt), [the file to test the HLS implementation](/hls/ethylene_methane_quant_0-100000.txt). Additionally, the [exported IP .zip file](/hls/xilinx_com_hls_gas_nn_1_0.zip) it is also there.

* In the [/vivado](/vivado) folder you can find the [Vivado project file](/vivado/gas_nn.xpr), the [Vivado generated bitstream](/vivado/gas_nn.bit), the [exported block design file](/vivado/gas_nn.tcl), the [block design file](/vivado/design_1.bd) and the [.hwh](/vivado/gas_nn.hwh) file.

* The [Usage notebook](Usage.ipynb) contains the custom driver to control the neural network from Python and how to use it. In this notebook are used to files, aviables in the [/usage-test](/usage-test) folder: the [parameters in .npz format](/usage-test/eth-ch4-params-quant.npz) and the [filtered data time series](/usage-test/ethylene_methane.txt).

* Finally, there is the [Project report](Project-report.pdf), with the explanation and results of this project.



## Instructions to build and test the project

![Raw data](/img/see-raw-data.png)

The [Virtualization notebook](Virtualization.ipynb) guides you to get the quantized neural network parameters, the only thing you may need is the HLS simulation of the model using fixed-point data types, for that you can use the next step and then get back to the second training stage.

![Quantized PyTorch prediction results](/img/see-quant-results.png)

In order to implement the HLS version of the network, you must create a Vivado HLS project using the [gas-nn.cpp](/hls/gas-nn-cpp) as a source file, defining its `gas_nn` function as the top-level function. For the test bench file, just add the [gas-nn-tb.cpp](/hls/gas-nn-tb.cpp) as the test bench source. Finally, select the PYNQZ2 board file as you FPGA.

There you can try to simulate and synthetize on your own. The final exported design we have used has its directives in the source file as `#pragmas`.

![HLS prediction results](/img/time-series-HLS-6350-8350.png)

Once you have exported your IP, you have to create a Vivado project and create a block design. In the Vivado settings there is the IP repositories locations, there you can add the [neural network HLS exported IP](/hls/xilinx_com_hls_gas_nn_1_0.zip). The using the block autoconnection feature, you can connect the ZYNQ processing system and the gas_nn block like this:

![Vivado IP integrator screenshot](/img/vivado.PNG)

Then you are ready generate the [bitstream](/vivado/gas_nn.bit). 

To use the customized overlay on PYNQ it is necessary to upload it to the overlay folder. For that you can use the Windows File Explorer, connecting to the PYNQ's file system. In the directory `\\pynq\xilinx\pynq\overlays\gas_nn` you must add the [bitstream](gas_nn.bit), the [.tcl](gas_nn.tcl) and the [.hwh](gas_nn.hwh) files

![PYNQ's file system](/img/pynq-fs.PNG)

Finally, the [Usage notebook](Usage.ipynb) shows you how to use the driver, the only thing you may need to customize yours is the HLS generated file with the port information and it is in your HLS project directory `.../[HLSproyect]/[solutionX]/impl/misc/drivers/[ip_block_name]/src/x[ip_block_name]_hw.h`

Then you can load the [trained parameters](/usage-test/eth-ch4-params-quant.npz) and predict the [time series](/usage-test/ethylene_methane.txt).

![PYNQ's predictions](/img/time-series-FPGA-12-3-6350-8350.png)

Link to YouTube Video(s):
