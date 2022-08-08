#!/bin/bash

pushd /root/tflite/classification

echo -e "-----------------------------------------------------------------"
echo -e "Running classification using mobilenet_v1_1.0_224.tflite model..."
echo -e "-----------------------------------------------------------------"

# Run tflite_classification binary with the tensorflow lite model, the input image, and the label file specified.

set -v

./tflite_classification -m ./mobilenet_v1_1.0_224.tflite -i ./grace_hopper.bmp -l ./labels.txt -p 1 -c 2

m5 exit
