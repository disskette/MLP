#ifndef Neuron_H
#define Neuron_H

#include <cstddef>
#include <iostream>
#include <vector>

template <typename T, T (*func)(T WS), T (*der)(T WS2)>
class Neuron
{
private:
    T bias;
    T weighted_sum;
    T totalVal; //value which passes to the next layer
    T localGrad;
    T err;
    
    std::vector<T> weights;
    size_t num_weights;

    
public:
    Neuron();
    ~Neuron() = default;
    //Neuron(size_t num_weights);

    void setNeuron(size_t num_weights);

    inline T getWValue(size_t weight_index) const {return totalVal*weights[weight_index];};
    inline T getValue() const {return totalVal;};


    void updateValues(T value); 

    void setV(T V){totalVal = V;};
    void setWeight(T w, size_t weight_index) {weights[weight_index] = w;};
    void setBias(T b){bias = b;};
    T calculateGrad(bool exit);
};


template <typename T, T (*func)(T WS), T (*der)(T WS2)>
Neuron<T, func>::Neuron()
: bias(0), weighted_sum(0), totalVal(0), num_weights(0)
{
    //std::cout<< "!!!" << std::endl;
};



template <typename T, T (*func)(T WS), T (*der)(T WS2)>
void Neuron<T, func, der>::setNeuron(size_t num_weights)
{
    this->num_weights = num_weights;
    weights.resize(num_weights,1);
    /*
    for (size_t weight_index=0; weight_index < num_weights; ++weight_index)
    {
        weights[weight_index] = 1;
    }
    */
};

template <typename T, T (*func)(T WS), T (*der)(T WS2)>
void Neuron<T, func,der>::updateValues(T value) 
{
    weighted_sum = value;
    totalVal = func(weighted_sum+bias);
}

template <typename T, T (*func)(T WS), T (*der)(T WS2)>
T Neuron<T, func, der>::calculateGrad(bool exit) 
{
    if (exit) //exit_layer
    {
        localGrad = der()
    }
}


#endif //Neuron_H