#!/bin/sh
# =======================================================================================================
# Run tidl import tool to convert the original tensorflow lite model (e.g., mobilenet_v1_1.0_224.tflite)
# to TIDL netowrk. The converted TIDL network are stored into tidl_net*.bin and tidl_param_*.bin files
# (e.g., tidl_net_tflite_mobilenet_v1_1.0_224.bin, and tidl_param_tflite_mobilenet_v1_1.0_224.bin).
# The TIDL supported subgraph are grouped as single custom operator (tidl-am5-custom-op) in tensorflow lite
# format, and re-written into a new tensorflow lite model (e.g.,mobilenet_v1_1.0_224_tidl_am5.tflite)
# =======================================================================================================
# 1. Prepare the input: tensorflow lite model
cd /usr/share/ti/tidl/utils
mkdir -p ./test/testvecs/config/tflite_models
mkdir -p ./test/testvecs/config/tidl_models/tflite/
cp /usr/share/tensorflow-lite/demos/mobilenet_v1_1.0_224.tflite ./test/testvecs/config/tflite_models

#2. Run tidl_model_import.out
tidl_model_import.out ./test/testvecs/config/import/tflite/tidl_import_mobileNetv1.txt

#3. Check the output and create subgraph0.cfg for TIDL offload at run-time

# TIDL *.bin files are generated at /usr/share/ti/tidl/utils/test/testvecs/config/tidl_models/tflite
# *tidl_am5.tflite model is generated at /usr/share/ti/tidl/utils/test/testvecs/config/tflite_models
ls -l /usr/share/ti/tidl/utils/test/testvecs/config/tidl_models/tflite
ls -l /usr/share/ti/tidl/utils/test/testvecs/config/tflite_models

echo "Creating subgraph0.cfg at /usr/share/tensorflow-lite/demos..."
echo "subgraph0.cfg will be used by TIDL API for the run-time offload"
subgraph0_cfg_path=/usr/share/tensorflow-lite/demos/subgraph0.cfg
# Specify TIDL network files
echo "netBinFile      = "/usr/share/ti/tidl/utils/test/testvecs/config/tidl_models/tflite/tidl_net_tflite_mobilenet_v1_1.0_224.bin"" > $subgraph0_cfg_path
echo "paramsBinFile   = "/usr/share/ti/tidl/utils/test/testvecs/config/tidl_models/tflite/tidl_param_tflite_mobilenet_v1_1.0_224.bin"" >> $subgraph0_cfg_path
# Sepcify the boundary conversion parameters, see details at https://downloads.ti.com/mctools/esd/docs/tidl-api/api.html
# The input is in NHWC format and ranges [-1,1]
echo "inConvType = 0" >> $subgraph0_cfg_path
echo "inIsSigned = 1" >> $subgraph0_cfg_path
echo "inScaleF2Q = 128" >> $subgraph0_cfg_path
echo "inIsNCHW = 0" >> $subgraph0_cfg_path
# The output is in NHWC format and ranges [0,1]
echo "outConvType = 0" >> $subgraph0_cfg_path
echo "outIsSigned = 0" >> $subgraph0_cfg_path
echo "outScaleF2Q = 255.0" >> $subgraph0_cfg_path
echo "outIsNCHW = 0" >> $subgraph0_cfg_path
echo "subgraph0.cfg:"
cat $subgraph0_cfg_path
