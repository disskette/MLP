#ifndef Perceptron_H
#define Perceptron_H

#include "layer.hpp"
#include <thread>
#include <functional>
#include <utility>

template <class T, T (*func1)(T WS1), T (*func2)(T WS2)>
void run ( size_t neuron_index, Layer<T, func1> *prevlayer, Layer<T, func2> *layer)
{
    T sum =0;

    for(size_t weight_index =0; weight_index < prevlayer->getNeurons(); ++weight_index)
    {
        sum += prevlayer->getWeightedValue(weight_index, neuron_index);
    }
    layer->updateNeuron(neuron_index, sum);
}

struct run_wrapper
{
    template <class... Args>
    auto operator()(Args&&... args) -> decltype(run(std::forward<Args>(args)...))
    {
        return run(std::forward<Args>(args)...);
    }
};


template <class T, T (*funcL1)(T WS1), T (*funcL2)(T WS2)> //WS - weighted sum
class Perceptron
{
private:
    Layer<T, funcL2> *enterLayer;
    Layer<T, funcL1> *hiddenLayer; //tansig
    Layer<T, funcL2> *exitLayer; //purelin

    size_t first_neurons, second_neurons, third_neurons;
public:

    Perceptron()=default;
    Perceptron(size_t first_neurons, size_t second_neurons, size_t third_neurons);
    ~Perceptron()
    {
        if (enterLayer) delete enterLayer;
        if (hiddenLayer) delete hiddenLayer;
        if (exitLayer) delete exitLayer;
    };

    void setNet(const char* first_weights, const char* second_weights, const char* second_bias, const char* third_bias);
    
    //void updatehiddenLayer();
    //void updateexitLayer();
    void launch(const char* file_name);

    template <class TT, TT (*func1)(TT WS1), TT (*func2)(TT WS2)>
    void runLayer(Layer<TT, func1>* prevlayer, Layer<TT, func2>* layer)
    {
        std::vector<std::thread> threads;
        threads.resize(layer -> getNeurons());
        for (size_t  neuron_index=0; neuron_index< layer ->getNeurons(); ++neuron_index)
        {
            threads.emplace_back(run_wrapper{}, neuron_index, prevlayer, layer);
        }

        for (auto &i : threads)
        {
            if (i.joinable())
            i.join();
        }
    }

    void Learn(const char* input, const char* target, T learningRate);
    void learnLayer(T learningRate);
    
};

template <class T, T (*funcL1)(T WS1), T (*funcL2)(T WS2)>
Perceptron<T, funcL1, funcL2>::Perceptron(size_t first_neurons, size_t second_neurons, size_t third_neurons)
: first_neurons(first_neurons), second_neurons(second_neurons), third_neurons(third_neurons)
{
    enterLayer = new Layer<T, funcL2>(first_neurons, second_neurons);
    hiddenLayer = new Layer<T, funcL1>(second_neurons, third_neurons);
    exitLayer = new Layer<T, funcL2>(third_neurons, 0);

}

/*
template <class T, T (*funcL1)(T WS1), T (*funcL2)(T WS2)>
void Perceptron<T, funcL1, funcL2>::updatehiddenLayer()
{
    std::vector<std::thread> threads;
    threads.resize(second_neurons);
    for (size_t  neuron_index=0; neuron_index< second_neurons; ++neuron_index)
    {
        threads.emplace_back(run_wrapper{}, neuron_index, enterLayer, hiddenLayer);
    }

    for (auto &i : threads)
    {
        if (i.joinable())
        i.join();
    }
}



template <class T, T (*funcL1)(T WS1), T (*funcL2)(T WS2)>
void Perceptron<T, funcL1, funcL2>::updateexitLayer()
{
    std::vector<std::thread> threads;
    threads.reserve(third_neurons);
    for (size_t  neuron_index=0; neuron_index< third_neurons; ++neuron_index)
    {
        threads.emplace_back(run_wrapper{}, neuron_index, hiddenLayer, exitLayer);
    }
    
    for (auto &i : threads)
    {
        if (i.joinable())
        i.join();
    }
}
*/

template <class T, T (*funcL1)(T WS1), T (*funcL2)(T WS2)>
void Perceptron<T, funcL1, funcL2>::launch(const char* file_name)
{
    enterLayer->setInput(file_name);
    //enterLayer.showResults();
    //updatehiddenLayer();
    //updateexitLayer();
    //hiddenLayer.showResults();
    runLayer(enterLayer, hiddenLayer);
    runLayer(hiddenLayer, exitLayer);
    exitLayer->showResults();
}

template <class T, T (*funcL1)(T WS1), T (*funcL2)(T WS2)>
void Perceptron<T, funcL1, funcL2>::setNet(const char* first_weights, const char* second_weights, const char* second_bias, const char* third_bias)
{
    enterLayer->setLayer(first_weights,0);
    hiddenLayer->setLayer(second_weights,second_bias);
    exitLayer->setLayer(0, third_bias);
}

#endif //Perceptron_H