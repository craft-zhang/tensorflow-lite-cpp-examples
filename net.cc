/* ======================================================================== */
TEST(CONVOLUTION_NHWC_QC8, conv_0) {
  ConvolutionOperatorTester()
    .input_size(230, 230)
    .kernel_size(7, 7)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(2)
    .subsampling_height(2)
    .group_input_channels(3)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_1) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_2) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_3) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_4) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_5) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_6) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_7) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_8) {
  ConvolutionOperatorTester()
    .input_size(56, 56)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_9) {
  ConvolutionOperatorTester()
    .input_size(58, 58)
    .kernel_size(3, 3)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(2)
    .subsampling_height(2)
    .group_input_channels(64)
    .group_output_channels(64)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_10) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(64)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_11) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_12) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_13) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_14) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_15) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_16) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_17) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_18) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_19) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_20) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_21) {
  ConvolutionOperatorTester()
    .input_size(28, 28)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_22) {
  ConvolutionOperatorTester()
    .input_size(30, 30)
    .kernel_size(3, 3)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(2)
    .subsampling_height(2)
    .group_input_channels(128)
    .group_output_channels(128)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_23) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(128)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_24) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_25) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_26) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_27) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_28) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_29) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_30) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_31) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_32) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_33) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_34) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_35) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_36) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_37) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_38) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_39) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_40) {
  ConvolutionOperatorTester()
    .input_size(14, 14)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_41) {
  ConvolutionOperatorTester()
    .input_size(16, 16)
    .kernel_size(3, 3)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(2)
    .subsampling_height(2)
    .group_input_channels(256)
    .group_output_channels(256)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_42) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(256)
    .group_output_channels(1024)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_43) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_44) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_45) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(2048)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_46) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(1024)
    .group_output_channels(2048)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_47) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(2048)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_48) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_49) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(2048)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_50) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(2048)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_51) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(3, 3)
    .padding_left(1)
    .padding_right(1)
    .padding_top(1)
    .padding_bottom(1)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(512)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_52) {
  ConvolutionOperatorTester()
    .input_size(7, 7)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(512)
    .group_output_channels(2048)
    .iterations(1)
    .TestNHWCxQC8();
}

TEST(CONVOLUTION_NHWC_QC8, conv_53) {
  ConvolutionOperatorTester()
    .input_size(1, 1)
    .kernel_size(1, 1)
    .padding_left(0)
    .padding_right(0)
    .padding_top(0)
    .padding_bottom(0)
    .subsampling_width(1)
    .subsampling_height(1)
    .group_input_channels(2048)
    .group_output_channels(1001)
    .iterations(1)
    .TestNHWCxQC8();
}

