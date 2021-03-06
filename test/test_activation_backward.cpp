#include "test_activation_backward.hpp"

TEST(activation_backward, func_test_naive_activation) {
  activation_params_t test_case(1, 1, 224, 244);
  Memory<float> dataSrc(test_case.n * test_case.channels * test_case.height *
                        test_case.width);
  Memory<float> dataGrad(test_case.n * test_case.channels * test_case.height *
                         test_case.width);
  Memory<float> dataDst(test_case.n * test_case.channels * test_case.height *
                        test_case.width);
  populateMemoryRandom(dataSrc);
  populateMemoryRandom(dataGrad);

  int ip_size[4] = {test_case.n, test_case.channels, test_case.height, test_case.width};
  int op_size[4] =  {test_case.n, test_case.channels, test_case.height, test_case.width};

  std::string str_ip_size  = convert_to_string((int*)ip_size,4);
  std::string str_k_size  = "NIL";
  std::string str_op_size  = convert_to_string((int*)op_size,4);

  high_resolution_timer_t timer;
    std::vector<double> time_vector(benchmark_iterations);
    for(int i = 0; i < benchmark_iterations; i++){
      timer.restart();
      compute_hipdnn_activation_backward(test_case, dataSrc.gpu(), dataGrad.gpu(),
                                     dataDst.gpu());
      hipDeviceSynchronize();
      std::uint64_t time_elapsed = timer.elapsed_nanoseconds();
      time_vector[i] = (double)time_elapsed / 1000;
    }
    double avg_time = std::accumulate(time_vector.begin() + 10, time_vector.end(), 0.0) / (benchmark_iterations - 10);
    std::cout << "Average Time: " << avg_time << std::endl;
    std::string strt = "./result_unittest.csv";
    std::string testname = "activation_backward:func_test_naive_activation";
    float* temp = dataDst.getDataFromGPU();
    std::string str  = convert_to_string((float*)temp,(int)dataDst.get_num_elements());
    write_to_csv(strt, str, testname, avg_time, str_ip_size, str_k_size, str_op_size);

}
