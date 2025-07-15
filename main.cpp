#include <iostream>
#include <iomanip>
#include <cmath>
#include "euler_solver.h"

using namespace std;


// Пример 1: Простое ОДУ dy/dx = x
double exampleODE1(double x, double y) {
    return x;
}

// Пример 2: dy/dx = -2x*y (линейное неоднородное)
double exampleODE2(double x, double y) {
    return -2 * x * y;
}

// Пример 3: dy/dx = sin(x) + y (нелинейное)
double exampleODE3(double x, double y) {
    return sin(x) + y;
}

int main() {
    try {
        setlocale(LC_ALL, "RU");
        // Пример 1: dy/dx = x, y(0) = 0, решение: y = x²/2
        EulerSolver solver1(exampleODE1, 0.1);
        auto solution1 = solver1.solve(0, 0, 2);

        cout << "Решение уравнения dy/dx = x, y(0) = 0 на интервале [0, 2] с шагом 0.1:\n";
        cout << setw(10) << "x" << setw(15) << "Численное y" << setw(15) << "Точное y"
            << setw(15) << "Погрешность\n";
        for (const auto& point : solution1) {
            double exact = point.first * point.first / 2;
            cout << setw(10) << point.first
                << setw(15) << point.second
                << setw(15) << exact
                << setw(15) << fabs(point.second - exact) << "\n";
        }

        // Пример 2: dy/dx = -2xy, y(0) = 1, решение: y = exp(-x²)
        EulerSolver solver2(exampleODE2, 0.05);
        auto solution2 = solver2.solve(0, 1, 1);

        cout << "\nРешение уравнения dy/dx = -2xy, y(0) = 1 на интервале [0, 1] с шагом 0.05:\n";
        cout << setw(10) << "x" << setw(15) << "Численное y" << setw(15) << "Точное y"
            <<setw(15) << "Погрешность\n";
        for (const auto& point : solution2) {
            double exact = exp(-point.first * point.first);
            cout <<setw(10) << point.first
                << setw(15) << point.second
                << setw(15) << exact
                << setw(15) << fabs(point.second - exact) << "\n";
        }

        // Пример 3 с изменением шага
        EulerSolver solver3(exampleODE3, 0.2);
        auto solution3 = solver3.solve(0, 1, 2);

       cout << "\nРешение уравнения dy/dx = sin(x) + y, y(0) = 1 на интервале [0, 2] с шагом 0.2:\n";
       cout << setw(10) << "x" << setw(15) << "Численное y\n";
        for (const auto& point : solution3) {
            cout << setw(10) << point.first
                << setw(15) << point.second << "\n";
        }

        // Меняем шаг и решаем снова
        solver3.setStep(0.05);
        auto solution3_finer = solver3.solve(0, 1, 2);

        cout << "\nТо же уравнение с шагом 0.05:\n";
        cout << setw(10) << "x" << setw(15) << "Численное y\n";
        for (const auto& point : solution3_finer) {
            cout << setw(10) << point.first
                << setw(15) << point.second << "\n";
        }

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
