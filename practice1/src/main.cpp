#include <iostream>

extern "C" int sum(int a, int b);
extern "C" int compare_numbers(int a, int b);

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << sum(a, b) << std::endl;
    std::cout << compare_numbers(a, b) << std::endl;
    return 0;
}
