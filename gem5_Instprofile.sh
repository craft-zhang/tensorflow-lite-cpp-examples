# # Invoke 两次
# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_mobilenet_v1_100_224_classification.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  MBV1Slide1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1Slide1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2Slide1209.txt

# # Invoke 两次

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1BASE1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2BASE1209.txt

# # Invoke 两次

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_mobilenet_v1_100_224_classification.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  MBV1LH1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1LH1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x14000:0x14006 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2LH1209.txt


# Invoke 一次看细节

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x1ad620,0x1acae2,0x194aa4:0x194b8a,0x194b8a:0x194cca,0x1acc20,0x1accd6,0x1adbec,0x1adcd6 -c classification/tflite_classification --options="-m classification/imagenet_mobilenet_v1_100_224_classification.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  MBV1LHDetail1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x1ad620,0x1acae2,0x194aa4:0x194b8a,0x194b8a:0x194cca,0x1acc20,0x1accd6,0x1adbec,0x1adcd6 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1LHDetail1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x1ad620,0x1acae2,0x194aa4:0x194b8a,0x194b8a:0x194cca,0x1acc20,0x1accd6,0x1adbec,0x1adcd6 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2LHDetail1209.txt


# # Invoke 一次看细节

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x1ad9f4,0x1aceb6,0x194ab0:0x194f2e,0x194f2e:0x195092,0x1acff4,0x1ad0aa,0x1adfc0,0x1ae0aa -c classification/tflite_classification --options="-m classification/imagenet_mobilenet_v1_100_224_classification.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  MBV1BASEDetail1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x1ad9f4,0x1aceb6,0x194ab0:0x194f2e,0x194f2e:0x195092,0x1acff4,0x1ad0aa,0x1adfc0,0x1ae0aa -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1BASEDetail1209.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=0x1ad9f4,0x1aceb6,0x194ab0:0x194f2e,0x194f2e:0x195092,0x1acff4,0x1ad0aa,0x1adfc0,0x1ae0aa -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2BASEDetail1209.txt


# # Invoke 一次看细节

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=194ab0:195196,194ace:194f4e,194f4e:195092,195092:195190 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1BASEDetail1209S.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=194ab0:195196,194ace:194f4e,194f4e:195092,195092:195190 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2BASEDetail1209S.txt

# Invoke 一次看细节

/home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=194aba:194dce,194aba:194b96,194b96:194cca,194cca:194dc8 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
cp m5out/stats.txt  50V1LHDetail1209S.txt

/home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=194aba:194dce,194aba:194b96,194b96:194cca,194cca:194dc8 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
cp m5out/stats.txt  50V2LHDetail1209S.txt

# # Invoke 一次看细节

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=194ab0:195196,1bc370:1bce14,194ace:194f4e,1bc3c4:1bcc54,194f4e:195092,1bcc54:1bcd3c,195092:195190,1bcd3c:1bcde6 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v1_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V1SlideDetail1209S.txt

# /home/craft/workspace/gem5/gem5/build/RISCV/gem5.opt /home/craft/workspace/gem5/gem5/configs/example/se.py  --cpu-type=AtomicSimpleCPU --caches --l1d_size=64kB --l1d_assoc=4 --l1i_size=64kB --l1i_assoc=4 --l2cache --l2_size=1MB --l2_assoc=16 --cacheline_size=64 --monitor_domain_ranges=194ab0:195196,1bc370:1bce14,194ace:194f4e,1bc3c4:1bcc54,194f4e:195092,1bcc54:1bcd3c,195092:195190,1bcd3c:1bcde6 -c classification/tflite_classification --options="-m classification/imagenet_resnet_v2_50_classification_5.tflite -i classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1"
# cp m5out/stats.txt  50V2SlideDetail1209S.txt
