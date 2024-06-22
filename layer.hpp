#ifndef Layer_H
#define Layer_H

#include "neuron.hpp"
#include <fstream>

template <typename T, T (*func)(T WS)>
class Layer
{
private:

    std::vector<Neuron<T, func>> neurons;
    size_t num_neurons, num_weights;

public:
    Layer()=default;
    Layer(size_t num_neurons, size_t num_weights);
    ~Layer()=default;

    T getWeightedValue(size_t neuron_index, size_t weight_index);
    void updateNeuron(size_t neuron_index, T upd);
    void showResults() const;
    void setLayer(const char* weight_file, const char* bias_file);
    void setInput(const char* in_file);

    size_t getNeurons() const {return num_neurons;};
};

template <typename T, T (*func)(T WS)>
Layer<T, func>::Layer(size_t num_neurons, size_t num_weights)
: num_neurons(num_neurons), num_weights(num_weights)
{
    //if (neurons) delete[] neurons;
    //neurons = new Neuron<T, func>[num_neurons];
    neurons.resize(num_neurons);

    for(size_t i =0; i<num_neurons;++i)
    {
        neurons[i].setNeuron(num_weights);
    }
};



template <typename T, T (*func)(T WS)>
T Layer<T, func>::getWeightedValue(size_t neuron_index, size_t weight_index)
{
    return neurons[neuron_index].getWValue(weight_index);
}

template <typename T, T (*func)(T WS)>
void Layer<T, func>::updateNeuron(size_t neuron_index, T upd)
{
    neurons[neuron_index].updateValues(upd);
}

template <typename T, T (*func)(T WS)>
void Layer<T, func>::showResults() const
{
    for (size_t i =0; i < num_neurons; ++i)
    {
        std::cout << neurons[i].getValue() << std::endl;
    }
}

template <typename T, T (*func)(T WS)>
void Layer<T, func>::setLayer(const char* weight_file, const char* bias_file) 
{
    if (weight_file != 0)
    {
        std::fstream in_weight(weight_file, std::ios_base::in);
        double weight;
        
        for (size_t neuron_index = 0; neuron_index < num_neurons; ++neuron_index)
        {
            for (size_t weight_index = 0; weight_index < num_weights; ++weight_index)
            {
                in_weight.read(reinterpret_cast<char*>(&weight), 8);
                neurons[neuron_index].setWeight(weight, weight_index);
            }
        }
        
        /*
       
       for (size_t weight_index = 0; weight_index < Num_weights; ++weight_index )
        {
            for (size_t neuron_index = 0; neuron_index < Num_neurons; ++neuron_index)
            {
                //in_weight >> weight;
                //std::cout << weight;
                in_weight.read(reinterpret_cast<char*>(&weight), 8);
                //std::cout << weight;
                //in_weight.read(&weight, 8);
                neurons[neuron_index].setWeight(weight, weight_index);
            }
        }
        */
        
        
        in_weight.close();
    }
    if (bias_file !=0)
    {
        std::ifstream in_bias(bias_file);
        T bias=0;
        
        for (size_t neuron_index = 0; neuron_index < num_neurons; ++neuron_index)
        {
            in_bias.read(reinterpret_cast<char*>(&bias), 8);
            neurons[neuron_index].setBias(bias);
        }
        in_bias.close();
    }
}

template <typename T, T (*func)(T WS)>
void Layer<T, func>::setInput(const char* in_file) 
{
    std::ifstream in(in_file);
    std::ofstream out("out.pgm");
    out << "P5" << '\n' << "#djkfhadf"<< '\n'<< "28 28"<< '\n' << "255" << std::endl;
    in.seekg(16);

    unsigned char c;
    for (size_t i=0; i<num_neurons; ++i)
    {
        in>>c;
        out << c;
        neurons[i].setV((T)c/255);
    }

    //in.seekg(16);
    /*

    for (size_t i = 0; i < 28; ++i)
    {
        for ( size_t j = 0; j < 28; ++j)
        {
            in>>c;
            neurons[i+28*j].setV(1.0/255);

        }
    }
    */

    in.close();
    out.close();

}
#endif //Layer_H