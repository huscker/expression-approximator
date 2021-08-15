
// Example usage

#include "src/expr.h"
#include "src/ga.h"
#include <vector>
#include <iostream>
#include <string>
#include <random>

// available opearations
void add(const float &a, const float &b, float &c)
{
    c = a + b;
}
void sub(const float &a, const float &b, float &c)
{
    c = a - b;
}
void mul(const float &a, const float &b, float &c)
{
    c = a * b;
}
void div(const float &a, const float &b, float &c)
{
    c = a / b;
}

int main()
{
    std::vector<void (*)(const float &, const float &, float &)> avops;
    std::vector<std::string> avops_symb = {"+", "-", "*", "/"};
    avops.push_back(add);
    avops.push_back(sub);
    avops.push_back(mul);
    avops.push_back(div);
    std::vector<std::pair<float, float>> train_data = {
        std::pair<float, float>(-9.183673469387756, 0.00010270256461965522),
        std::pair<float, float>(-8.775510204081632, 0.00015447006969015754),
        std::pair<float, float>(-8.36734693877551, 0.00023233112550254234),
        std::pair<float, float>(-7.959183673469388, 0.00034943825678041636),
        std::pair<float, float>(-7.551020408163265, 0.0005255735538560034),
        std::pair<float, float>(-7.142857142857142, 0.0007904903231199669),
        std::pair<float, float>(-6.73469387755102, 0.0011889391054054296),
        std::pair<float, float>(-6.326530612244898, 0.001788227072512481),
        std::pair<float, float>(-5.918367346938775, 0.002689587757966899),
        std::pair<float, float>(-5.5102040816326525, 0.004045281731274607),
        std::pair<float, float>(-5.1020408163265305, 0.006084316913218737),
        std::pair<float, float>(-4.6938775510204085, 0.00915113328554634),
        std::pair<float, float>(-4.285714285714286, 0.013763786733050402),
        std::pair<float, float>(-3.8775510204081627, 0.020701460608393295),
        std::pair<float, float>(-3.4693877551020407, 0.031136087737526377),
        std::pair<float, float>(-3.0612244897959187, 0.046830316852419576),
        std::pair<float, float>(-2.6530612244897958, 0.07043526453886609),
        std::pair<float, float>(-2.244897959183673, 0.10593834985773154),
        std::pair<float, float>(-1.8367346938775508, 0.15933686121653334),
        std::pair<float, float>(-1.4285714285714288, 0.23965103644177574),
        std::pair<float, float>(-1.020408163265305, 0.36044778859782145),
        std::pair<float, float>(-0.612244897959183, 0.5421324699199654),
        std::pair<float, float>(-0.204081632653061, 0.815395805547463),
        std::pair<float, float>(0.204081632653061, 1.2263982635139903),
        std::pair<float, float>(0.612244897959183, 1.8445676204334875),
        std::pair<float, float>(1.0204081632653068, 2.7743269112292337),
        std::pair<float, float>(1.4285714285714288, 4.172733883598097),
        std::pair<float, float>(1.8367346938775508, 6.2760116671373),
        std::pair<float, float>(2.2448979591836746, 9.439452297897203),
        std::pair<float, float>(2.6530612244897966, 14.197433722254315),
        std::pair<float, float>(3.0612244897959187, 21.353688533677584),
        std::pair<float, float>(3.4693877551020407, 32.117072910054866),
        std::pair<float, float>(3.8775510204081627, 48.30577025055688),
        std::pair<float, float>(4.2857142857142865, 72.65442420716553)
    }; // train data: (value, expected result)

    GA ga(1000, 100, 5, 10, 40, avops, avops_symb, 10, 1, 200.0, 0.5, train_data);
    std::cout << ga.get_solution() << std::endl;
    while (1)
    {
        ga.iterate();
        std::cout << ga.get_error() << " " << ga.get_solution() << std::endl;
    }
    return 0;
}
