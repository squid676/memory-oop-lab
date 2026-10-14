#include "forge/algorithms.hpp"
#include "forge/memory.hpp"
#include "forge/record_io.hpp"
#include "forge/shapes.hpp"
#include <iostream>

int main() {
    using namespace forge;
    std::cout << "== Pointers and allocation ==\n";
    Arena arena(1024);
    int* raw = arena.make<int>(42);
    std::cout << "raw pointer value: " << *raw << ", arena bytes: " << arena.bytes_used() << '\n';
    Circle* arena_circle = arena.make<Circle>(2.0);
    arena_circle->~Circle();
    Unique<int> owned(new int(99));
    std::cout << "custom Unique value: " << *owned << '\n';

    std::cout << "\n== Abstract classes and polymorphism ==\n";
    Circle circle(3.0); Rectangle rectangle(4.0, 5.0);
    Shape* shapes[] = { &circle, &rectangle };
    for (const Shape* shape : shapes) { shape->describe(std::cout); std::cout << '\n'; }

    std::cout << "\n== Template algorithms ==\n";
    int values[] = { 8, 3, 7, 1, 4, 9, 2 };
    insertion_sort(values, 7);
    std::cout << "sorted: "; for (int value : values) std::cout << value << ' ';
    std::cout << "\nindex of 7: " << binary_search(values, 7, 7) << "\nrecursive factorial(6): " << factorial(6) << '\n';

    std::cout << "\n== Binary file serialization ==\n";
    Record records[] = {{101, "Ada", 98.5}, {202, "Linus", 91.25}};
    save_records("records.bin", records, 2);
    Record restored[2];
    auto count = load_records("records.bin", restored, 2);
    for (std::uint32_t i = 0; i < count; ++i)
        std::cout << restored[i].id << ' ' << restored[i].name << ' ' << restored[i].score << '\n';
}
