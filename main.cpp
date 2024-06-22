#include "perceptron.hpp"

#include <cmath>

template <typename T>
T tansig(T n)
{
    T ret = (2/(1+std::exp(-2*n))) -1;
    return ret;
}

template <typename T>
T purelin(T n)
{
    return n;
}

int main()
{
    Perceptron<double, tanh, purelin> kotik(784, 200, 10);
    kotik.setNet("net_train_weight1.bin", "net_train_weight2.bin","net_train_bias1.bin", "net_train_bias2.bin");
    kotik.launch("train-images.idx3-ubyte");

    return 0;
}