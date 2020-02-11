#ifndef UTILS_H_
#define UTILS_H_

double get_us(struct timeval t);

typedef enum
{
  INPUT_Image          = 0,
  INPUT_Video          = 1,
  INPUT_Camera         = 2
} eInputType;

bool SetupInput(eInputType input_source, std::string input_path, cv::VideoCapture& cap, cv::Mat& input_image);

void SetupLiveDisplay(char *display_win);

void CollectFrames(std::vector<uint8_t> &output,
                   int input_source, cv::VideoCapture &cap, cv::Mat &in_image,
                   int width, int height, int channels);

template <class T>
void PrepareInput(T* out, std::vector<uint8_t> &input, int input_number_of_pixels,
                  bool floating_input, float input_mean, float input_std)
{
  for (int i = 0; i < input_number_of_pixels; i++) {
    if (floating_input)
      out[i] = (input[i] - input_mean) / input_std;
    else
      out[i] = (uint8_t)input[i];
  }
}

#endif  // UTILS_H_
