#include "newton_interpolation.h"
#include "spline_interpolation.h"
double Interpolation_Function(double x)
{
    return 0.5 * (std::abs(x + 1) - std::abs(x - 1)) + std::abs(x - 2);
}
void Compute(const std::pair<double, double> &interval)
{
    std::cout<<"Enter count of interpolation nodes:"<<'\n';
    int count_of_nodes;
    std::cin>>count_of_nodes;
    std::cout<<"Choose interpolation variant - with Newton polynomial (N) or cubic spline (S):"
             <<'\n';
    std::string variant;
    std::cin>>variant;
    while (variant != "N" && variant != "S")
    {
        std::cout<<"Chosen incorrect variant! Please, enter N or S:"<<'\n';
        std::cin>>variant;
    }
    std::shared_ptr<Interpolation_Method> method;
    if (variant == "N") method = std::make_shared<Newton_Interpolation>();
    else method = std::make_shared<Spline_Interpolation>();
    method->Set_Interpolation_Function(Interpolation_Function);
    method->Set_Interval(interval);
    method->Set_Count_Of_Nodes(count_of_nodes);
    method->Execute();
    std::cout<<R"(Do you want to continue computing? 'Y' means "Yes", another means "No")"<<'\n';
    std::cin>>variant;
    if (variant == "Y") Compute(interval);
}
int main()
{
const std::pair<double, double> interval = std::make_pair(-3.0, 4.0);
std::cout<<"Interpolation function: f(x)=0.5*(|x+1|-|x-1|)+|x-2|"<<'\n'
<<"Interpolation line segment: ["<<interval.first<<"; "<<interval.second<<']'<<'\n';
Compute(interval);
return 0;
}