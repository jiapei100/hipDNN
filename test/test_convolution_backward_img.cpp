/* #include "test_convolution_backward_img.hpp"

TEST(convolution_bwd_img, func_check_backward_conv_img) {
    Desc inputDesc(1, 3, 224, 224);
    Desc filterDesc(21, 3, 3, 3);
    int pad[2] = {0, 0};    // zero padding
    int stride[2] = {1, 1}; // stride 1
    Desc outputDesc =
        calculateConv2DOutputDesc(inputDesc, filterDesc, pad, stride);
    Memory<float> srcData = createMemory<float>(inputDesc);
    Memory<float> dstDataCPU = createMemory<float>(outputDesc);
    Memory<float> dstDataGPU = createMemory<float>(outputDesc);
    Memory<float> filterData = createMemory<float>(filterDesc);
    populateMemoryRandom<float>(srcData);
    populateMemoryRandom<float>(filterData);
    test_convolution_sizes_t testConvolutionSizes(
        inputDesc.N, 1, inputDesc.C, inputDesc.H, inputDesc.W, outputDesc.C,
        outputDesc.H, outputDesc.W, filterDesc.H, filterDesc.W, pad[0], pad[1],
        stride[0], stride[1], 1, 1);
high_resolution_timer_t timer;
    compute_hipdnn_conv_fwd<float>(testConvolutionSizes, srcData.gpu(),
                                   filterData.gpu(), NULL, dstDataGPU.gpu());
  std::uint64_t time_elapsed = timer.elapsed_nanoseconds();
  std::cout << "time taken: " << (time_elapsed / 1000.0) << " ms"<< std::endl;

    std::string strt = "./result_unittest.csv";
    std::string testname = "convolution_bwd_img:func_check_backward_conv_img";
    float* temp = dstDataGPU.getDataFromGPU();
    std::string str  = convert_to_string((float*)temp,(int)dstDataGPU.get_num_elements());
    write_to_csv(strt, str, testname);
}

*/
