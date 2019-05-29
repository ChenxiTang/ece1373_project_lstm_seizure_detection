#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include "matrix_vector.h"
//#include "util/shared.h"
#include <sstream>
#include <chrono>
#include <iomanip>
#include <fstream>

//#define HW_CTRL_ADDR 0x00000000

using namespace std;

int run_state_test(float* dma_input){
  
  int num_inputs = 64;
  int num_weights = 64*64;
  int num_biases = 64;

  mv_state(dma_input, 0, sizeof(float)*(num_inputs + num_biases + num_weights));

  return 0;

}

int run_input_test(float* dma_input){
    
    int num_inputs = 64;
    int num_weights = 64*110;
    int num_biases = 64;
    
    mv_state(dma_input, 0, sizeof(float)*(num_inputs + num_biases + num_weights));
    
    return 0;
    
}

int run_output_test(float* dma_input){
    
    int num_inputs = 64;
    int num_weights = 64;
    int num_biases = 1;
    printf("here");
    mv_state(dma_input, 0, sizeof(float)*(num_inputs + num_biases + num_weights));
    
    return 0;
    
}


int main(){
	//printf("here");
    
    
    float* state = new float[64*64+64+64+64];
    float* input = new float[64*110+64+110+64];
    float* output = new float[64+1+64+1];

	//float state[64*64+64+64+64];
	//float input[64*110+64+110+64];
	//float output[64+1+64+1];

    //FILE * fp;
    //fp = fopen ("state.txt","w");
    for (int i = 0; i < 64*64+64+64; i++){
        state[i] = (float)rand() / (float)RAND_MAX;
        //fprintf(fp, "%f\n", state[i]);
    }
    //fclose (fp);
    
    //fp = fopen ("input.txt","w");
    for (int i = 0; i < 64*110+64+110; i++){
        input[i] = (float)rand() / (float)RAND_MAX;
        //fprintf(fp, "%f\n", input[i]);
    }
    //fclose (fp);
    //std::cout << "here" << std::endl;
    
    //fp = fopen ("output.txt","w");
    for (int i = 0; i < 64+1+64; i++){
        output[i] = (float)rand() / (float)RAND_MAX;
        //fprintf(fp, "%f\n", output[i]);
    }
    //fclose (fp);
    
    if(run_output_test(output))
            return 1;
    if(run_state_test(state))
        return 1;

    if(run_input_test(input))
       return 1;



    printf("here3");

    float* result_state = new float[64];
    float* result_input = new float[64];
    float* result_output = new float[1];


    int x;
    ifstream inFile;
    int i = 0;
    inFile.open("result_state.txt");
    while (inFile >> x) {
        result_state[i] = x;
        i++;
    }
    inFile.close();

    i = 0;
    inFile.open("result_input.txt");
    while (inFile >> x) {
        result_input[i] = x;
        i++;
    }
    inFile.close();

    i = 0;
    inFile.open("result_output.txt");
    while (inFile >> x) {
        result_output[i] = x;
        i++;
    }
    inFile.close();

    
    std::cout << result_output[0] << " " << output[64*1+1+64] << std::endl;



  // auto end = chrono::system_clock::now();
  // auto elapsed = end - start;

  //float avg_error = get_mean_squared_error_and_write_file(dma_input_vec, gold_outputs_vec, numBatches, batch_layer_params, imageRootDir, layer, CONV);

  //cout << "Mean Square Error " << avg_error << endl;
  //cout << "Computation took  " << chrono::duration_cast<chrono::seconds> (elapsed).count() << " seconds" << endl;
  printf("here2");
  std::cout << "DONE" << std::endl;
  return 0;
}
