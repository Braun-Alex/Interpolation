#pragma once
#include "resources.h"
class Interpolation_Method
{
public:
Interpolation_Method();
void Set_Interpolation_Function(std::function<double(double)> entered_interpolation_function);
void Set_Interval(std::pair<double, double> entered_interval);
void Set_Count_Of_Nodes(int entered_count_of_nodes);
virtual void Execute() const = 0;
protected:
std::function<double(double)> interpolation_function;
std::pair<double, double> interval;
int count_of_nodes = 0;
};