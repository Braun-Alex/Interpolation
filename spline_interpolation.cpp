#include "spline_interpolation.h"
void Spline_Interpolation::Execute() const
{
    int system_size = count_of_nodes - 2;
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(system_size, system_size);
    Eigen::VectorXd vector_of_values = Eigen::VectorXd::Zero(count_of_nodes, 1),
            vector_of_nodes = Eigen::VectorXd::Zero(count_of_nodes, 1),
            y = Eigen::VectorXd::Zero(system_size, 1),
            m = Eigen::VectorXd::Zero(system_size, 1),
            M = Eigen::VectorXd::Zero(count_of_nodes, 1),
            Y = Eigen::VectorXd::Zero(count_of_nodes, 1);
    double distance = (interval.second - interval.first) / (count_of_nodes - 1),
           x = interval.first;
    for (int k = 0; k < count_of_nodes; ++k)
    {
        vector_of_nodes(k) = x;
        vector_of_values(k) = interpolation_function(x);
        x += distance;
    }
    for (int i = 0; i < system_size - 1; ++i)
    {
        A(i, i) = 4;
        A(i, i + 1) = 1;
        A(i + 1, i) = 1;
    }
    A(system_size - 1, system_size - 1) = 4;
    for (int i = 0; i < system_size; ++i)
        y(i) = vector_of_values(i) - 2 * vector_of_values(i + 1) + vector_of_values(i + 2);
    y *= 6/std::pow(distance, 2);
    m = A.colPivHouseholderQr().solve(y);
    for (int i = 1; i < system_size; ++i)
    {
        M(i) = m(i);
        Y(i) = y(i);
    }
    std::vector<Eigen::VectorXd> coefficients;
    coefficients.reserve(count_of_nodes - 1);
    for (int i = 0; i < count_of_nodes - 1; ++i)
    {
        coefficients.emplace_back(Eigen::VectorXd::Zero(4, 1));
        coefficients[i](0) = (M(i + 1) - M(i)) / (distance * 6);
        coefficients[i](1) = M(i) / 2;
        coefficients[i](2) = (vector_of_values(i + 1) -
                vector_of_values(i)) / distance -
                (M(i + 1) - M(i)) * (distance / 6);
        coefficients[i](3) = vector_of_values(i);
    }
    std::cout<<"Computed interpolation spline is represented by system of functions "
    <<"s(x)={s(";
    int count_of_intervals = count_of_nodes - 1;
    for (int i = 0; i < count_of_intervals - 1; ++i)
        std::cout<<i + 1<<"), s(";
    std::cout<<count_of_intervals<<")}, where"<<'\n';
    for (int i = 0; i < count_of_intervals; ++i)
    {
        std::cout<<"s("<<i + 1<<")(x)="<<coefficients[i](0)<<"*(x";
        if (vector_of_nodes(i) < 0)
            std::cout<<'+'<<std::abs(vector_of_nodes(i));
        else std::cout<<'-'<<vector_of_nodes(i);
        std::cout<<")^3";
        if (coefficients[i](1) < 0) std::cout<<coefficients[i](1);
        else std::cout<<'+'<<std::abs(coefficients[i](1));
        std::cout<<"*(x";
        if (vector_of_nodes(i) < 0) std::cout<<'+'<<std::abs(vector_of_nodes(i));
        else std::cout<<'-'<<vector_of_nodes(i);
        std::cout<<")^2";
        if (coefficients[i](2) < 0) std::cout<<coefficients[i](2);
        else std::cout<<'+'<<std::abs(coefficients[i](2));
        std::cout<<"*(x";
        if (vector_of_nodes(i) < 0) std::cout<<'+'<<std::abs(vector_of_nodes(i));
        else std::cout<<'-'<<vector_of_nodes(i);
        std::cout<<')';
        if (coefficients[i](3) < 0) std::cout<<coefficients[i](3);
        else std::cout<<'+'<<std::abs(coefficients[i](3));
        std::cout<<", where "<<vector_of_nodes(i)<<"<="<<"x<="<<vector_of_nodes(i + 1)<<'\n';
    }
}