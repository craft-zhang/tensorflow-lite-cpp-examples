PHONY: all

all: classification
LIBS = -lstdc++ -ltensorflow-lite -lpthread -lm -lz -ldl -lrt

LIBS += -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_core

INCLUDES := -I.

CXXFLAGS += --std=c++11

CXX := $(CC_PREFIX)${TARGET_TOOLCHAIN_PREFIX}g++

classification: classification.cc model_utils.cc utils.cc
	$(CXX) classification.cc model_utils.cc utils.cc -o tflite_classification $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(INCLUDES)

clean:
	rm -rf classification
