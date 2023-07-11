#pragma once
#include "interpolation_method.h"
class Spline_Interpolation: public Interpolation_Method
{
public:
void Execute() const override;
};