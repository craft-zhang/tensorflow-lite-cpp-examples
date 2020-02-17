PHONY: all

all: classification segmentation
LIBS = -lstdc++ -ltensorflow-lite -lpthread -lm -lz -ldl -lrt

LIBS += -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_core

INCLUDES := -I.

CXXFLAGS += --std=c++11

CXX := $(CC_PREFIX)${TARGET_TOOLCHAIN_PREFIX}g++

COMMON_SRC = model_utils.cc utils.cc

ifeq ($(TIDL_ACC), yes)
  COMMON_SRC += tidl_op.cc
endif

classification: classification.cc $(COMMON_SRC)
	$(CXX) classification.cc $(COMMON_SRC) -o tflite_classification $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(INCLUDES)

segmentation: segmentation.cc $(COMMON_SRC)
	$(CXX) segmentation.cc $(COMMON_SRC) -o tflite_segmentation $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(INCLUDES)

clean:
	rm -rf classification segmentation
