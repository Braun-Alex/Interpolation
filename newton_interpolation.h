#pragma once
#include "interpolation_method.h"
class Newton_Interpolation: public Interpolation_Method
{
public:
void Execute() const override;
private:
const double PI = 3.1415926536;
};