rm -f out.png && tflite_detection -m \
yolov5s_ultralytics_640_quantized.tflite -i bus.jpg -l \
labels.txt -c 1 -b 0 -s 255 -t 1 -v 5

rm -f out.png && tflite_detection -m \
yolov5s_ultralytics_640_quantized.tflite -i bus.jpg -l \
labels.txt -c 1 -b 0 -s 255 -t 4 -v 5

rm -f out.png && tflite_detection -m \
ssd_mobilenet_v2_2.tflite -i bus.jpg -l \
coco.txt -c 1 -b 0 -s 255 -t 1 -v ssd

rm -f out.png && tflite_detection -m \
ssd_mobilenet_v2_2.tflite -i bus.jpg -l \
coco.txt -c 1 -b 0 -s 255 -t 4 -v ssd