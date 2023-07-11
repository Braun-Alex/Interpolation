#include "newton_interpolation.h"
void Newton_Interpolation::Execute() const
{
    std::string variant;
    std::cout<<"Choose type of nodes: with equal distance (Q) or Chebyshev roots (H):"<<'\n';
    std::cin>>variant;
    while (variant != "Q" && variant != "H")
    {
        std::cout<<"Chosen incorrect variant. Please, enter Q or H:"<<'\n';
        std::cin>>variant;
    }
    Eigen::MatrixXd matrix_of_differences = Eigen::MatrixXd::Zero(count_of_nodes,
                                                                  count_of_nodes + 1);
    Eigen::VectorXd vector_of_values = Eigen::VectorXd::Zero(count_of_nodes, 1),
            vector_of_nodes = Eigen::VectorXd::Zero(count_of_nodes, 1);
    if (variant == "Q")
    {
        double distance = (interval.second - interval.first) / (count_of_nodes - 1),
                x = interval.first;
        for (int k = 0; k < count_of_nodes; ++k)
        {
            vector_of_nodes(k) = x;
            vector_of_values(k) = interpolation_function(x);
            x += distance;
        }
    }
    else
    {
        double sum = (interval.first + interval.second) / 2,
                multiplier = (interval.second - interval.first) / 2,
                denominator = 2 * count_of_nodes;
        for (int k = 0; k < count_of_nodes; ++k)
        {
            vector_of_nodes(k) = sum + multiplier * std::cos(
                    (2 * k + 1) * PI / denominator);
            vector_of_values(k) = interpolation_function(vector_of_nodes(k));
        }
    }
    for (int i = 0; i < count_of_nodes; ++i)
    {
        matrix_of_differences(i, 0) = vector_of_nodes(i);
        matrix_of_differences(i, 1) = vector_of_values(i);
    }
    for (int i = 2; i < count_of_nodes + 1; ++i)
    {
        for (int j = 0; j < count_of_nodes - i + 1; ++j)
            matrix_of_differences(j, i) = (matrix_of_differences(j + 1, i - 1) -
                                           matrix_of_differences(j, i - 1)) /
                                          (matrix_of_differences(j + i - 1, 0) -
                                           matrix_of_differences(j, 0));
    }
    Eigen::VectorXd vector_of_coefficients = Eigen::VectorXd::Zero(count_of_nodes, 1);
    for (int i = 0; i < count_of_nodes; ++i)
        vector_of_coefficients(i) = matrix_of_differences(0, i + 1);
    std::cout<<"Computed Newton interpolation polynomial: P(x)="<<vector_of_coefficients(0);
    for (int i = 1; i < count_of_nodes; ++i)
    {
        if (vector_of_coefficients(i) < 0)
            std::cout<<vector_of_coefficients(i)<<'*';
        else std::cout<<'+'<<vector_of_coefficients(i)<<'*';
        for (int j = 0; j < i; ++j)
        {
            std::cout<<"(x";
            if (vector_of_nodes(j) < 0) std::cout<<'+'<<std::abs(vector_of_nodes(j))<<')';
            else std::cout<<'-'<<vector_of_nodes(j)<<')';
        }
    }
    std::cout<<'\n';
}