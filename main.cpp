#include <iostream>
#include <Vector.h>
#include <Map.h>
#include <Hash_Set.h>

#include "HashMap.h"
#include "Set.h"

int main() {
    str::String str("Hello World");
    std::cout << str << std::endl;
    Vector<int> v;
    Set<int> s;
    HashSet<int> hs;
    Mapping::HashMap<str::String, int> hm;
    Map<str::String, int> m;
    hm[str::String("Maman")] = 52;
    hm[str::String("Baba")] = 58;
    hm[str::String("Dadash")] = 22;
    hm[str::String("Peyman")] = 15;


    m[str::String("Maman")] = 52;
    m[str::String("Baba")] = 58;
    m[str::String("Dadash")] = 22;
    m[str::String("Peyman")] = 15;
    for (int i = 0; i < 10; i++) {
        v.Append(i + 1);
        s.Add(i + 1);
        hs.Add(i + 1);
    }
    for (const auto& i : s) {
        std::cout << i << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    for (const auto& i : v) {
        std::cout << i << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    for (const auto& i : hs) {
        std::cout << i << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    for (const auto& [fst, snd] : hm) {
        std::cout << fst << ", " << snd << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    for (const auto& [fst, snd] : m) {
        std::cout << fst << ", " << snd << std::endl;
    }
    return 0;
}
