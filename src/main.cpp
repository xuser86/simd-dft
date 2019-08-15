#include <cstdio>
#include <cinttypes>

using namespace std;

extern "C" {
    uint64_t asm_say_hi();
}

int main() {
    printf("%ld\n", asm_say_hi());
    return 0;
}
