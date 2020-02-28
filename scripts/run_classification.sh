#!/bin/sh

cd /usr/share/tensorflow-lite/demos

echo -e "-----------------------------------------------------------------"
echo -e "Running classification using mobilenet_v1_1.0_224.tflite model..."
echo -e "-----------------------------------------------------------------"

# Run tflite_classification binary with the tensorflow lite model, the input image, and the label file specified.
# Classification label is overlayed with the input image. Exit the application after 60 seconds.
./tflite_classification -m ./mobilenet_v1_1.0_224.tflite -i ../examples/grace_hopper.bmp -l ../examples/labels.txt -p 1 & pid=$!
{ sleep 2; kill $pid; }

echo -e
echo -e "--------------------------------------------------------------------------------------------"
echo -e "Running classification using the TIDL compiled model mobilenet_v1_1.0_224_tidl_am5.tflite..."
echo -e "--------------------------------------------------------------------------------------------"
# Run classification with the TIDL compiled tensorflow lite model
# (e.g., mobilenet_v1_1.0_224_tidl_am5.tflite generated from run_tidl_compiler.sh)
# TIDL API uses subgraph0.cfg created from run_tidl_compiler.sh to identify the TIDL network files,
# as well as the boundary conversion parameters between TIDL and Arm
# Classification label is overlayed with the input image. Right click the image display window to exit.
cd /usr/share/tensorflow-lite/demos
./tflite_classification -m /usr/share/ti/tidl/utils/test/testvecs/config/tflite_models/mobilenet_v1_1.0_224_tidl_am5.tflite \
                        -i ../examples/grace_hopper.bmp -l ../examples/labels.txt -p 1
