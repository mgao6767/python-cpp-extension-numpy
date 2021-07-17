#include <vector>

class ExampleClass
{
public:
    ExampleClass(){};
    ~ExampleClass(){};
    void multiply(std::vector<double> &arr, double k)
    {
        for (auto &element : arr)
            element *= k;
    }
};