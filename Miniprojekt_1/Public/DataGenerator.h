#ifndef DATA_GENERATOR
#define DATA_GENERATOR
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

// Funkcja do generowania losowych liczb całkowitych z zakresu [min, max]
int GenerateRandomNumber(int min, int max)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
#endif