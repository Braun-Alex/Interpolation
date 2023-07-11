#include "interpolation_method.h"
Interpolation_Method::Interpolation_Method()=default;
void Interpolation_Method::Set_Interpolation_Function(std::function<double(double)>
        entered_interpolation_function)
{
    interpolation_function = std::move(entered_interpolation_function);
}
void Interpolation_Method::Set_Interval(std::pair<double, double> entered_interval)
{
    interval = std::move(entered_interval);
}
void Interpolation_Method::Set_Count_Of_Nodes(int entered_count_of_nodes)
{
    count_of_nodes = entered_count_of_nodes;
}