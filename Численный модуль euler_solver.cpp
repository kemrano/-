#include "euler_solver.h"
#include <stdexcept>

EulerSolver::EulerSolver(std::function<double(double, double)> ode, double step)
    : differential_equation(ode), step_size(step) {
    if (step <= 0) {
        throw std::invalid_argument("Step size must be positive");
    }
}

std::vector<std::pair<double, double>> EulerSolver::solve(double x0, double y0, double xend) {
    if (xend <= x0) {
        throw std::invalid_argument("xend must be greater than x0");
    }

    std::vector<std::pair<double, double>> solution;
    solution.reserve(static_cast<size_t>((xend - x0) / step_size) + 1);

    double x = x0;
    double y = y0;
    solution.emplace_back(x, y);

    while (x < xend) {
        double derivative = differential_equation(x, y);
        y += step_size * derivative; // y_{n+1} = y_n + h * f(x_n, y_n)
        x += step_size;

        // Для последнего шага корректируем, чтобы точно попасть в xend
        if (x > xend) {
            double last_step = xend - (x - step_size);
            y = solution.back().second + last_step * derivative;
            x = xend;
        }

        solution.emplace_back(x, y);
    }

    return solution;
}

void EulerSolver::setStep(double new_step) {
    if (new_step <= 0) {
        throw std::invalid_argument("Step size must be positive");
    }
    step_size = new_step;
}

double EulerSolver::getStep() const {
    return step_size;
}
