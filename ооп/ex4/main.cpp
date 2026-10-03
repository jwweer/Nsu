#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <iterator>

std::vector<int> readVectorFromFile(const std::string& filename) {
    std::vector<int> vec;
    std::ifstream file(filename);
    int value;
    while (file >> value) vec.push_back(value);
    return vec;
}

std::map<int, int> countFrequenciesFor(const std::vector<int>& vec) {
    std::map<int, int> freq;
    for (int x : vec) freq[x]++;
    return freq;
}

std::map<int, int> countFrequenciesAlgorithm(const std::vector<int>& vec) {
    std::map<int, int> freq;
    std::for_each(vec.begin(), vec.end(), [&freq](int x) { freq[x]++; });
    return freq;
}

void printFrequencies(const std::map<int, int>& freq) {
    for (const auto& [value, count] : freq)
        std::cout << value << " " << count << "\n";
}

int main() {
    std::string file1 = "data1.txt";
    std::string file2 = "data2.txt";

    std::vector<int> vecA = readVectorFromFile(file1);
    std::vector<int> vecB = readVectorFromFile(file2);

    if (vecA.empty() && vecB.empty()) {
        vecA = {5, 3, 5, 7, 5, 3, 5, 9, 5, 3, 5, 7, 5, 3, 5, 1, 5, 3, 5, 7};
        vecB = {3, 3, 5, 5, 5, 7, 7, 2, 2, 2, 8, 8};
    }

    std::vector<int>& first  = (vecA.size() >= vecB.size()) ? vecA : vecB;
    std::vector<int>& second = (vecA.size() >= vecB.size()) ? vecB : vecA;

    std::cout << "2. Количество: " << first.size() << " " << second.size() << "\n";

    auto freqFirstFor  = countFrequenciesFor(first);
    auto freqFirstAlg  = countFrequenciesAlgorithm(first);
    auto freqSecondFor = countFrequenciesFor(second);
    auto freqSecondAlg = countFrequenciesAlgorithm(second);

    std::cout << "3. Частоты (1-й for):\n";
    printFrequencies(freqFirstFor);
    std::cout << "3. Частоты (1-й alg):\n";
    printFrequencies(freqFirstAlg);
    std::cout << "3. Частоты (2-й for):\n";
    printFrequencies(freqSecondFor);
    std::cout << "3. Частоты (2-й alg):\n";
    printFrequencies(freqSecondAlg);

    int sumFirst1  = std::accumulate(first.begin(), first.end(), 0);
    int sumSecond1 = std::accumulate(second.begin(), second.end(), 0);
    int sumFirst2 = 0;
    std::for_each(first.begin(), first.end(), [&sumFirst2](int x) { sumFirst2 += x; });
    int sumSecond2 = 0;
    std::for_each(second.begin(), second.end(), [&sumSecond2](int x) { sumSecond2 += x; });

    std::cout << "4. Сумма 1-й: " << sumFirst1 << " " << sumFirst2 << "\n";
    std::cout << "4. Сумма 2-й: " << sumSecond1 << " " << sumSecond2 << "\n";

    auto sumFirst10 = [](const std::vector<int>& v) {
        std::size_t n = std::min<std::size_t>(10, v.size());
        return std::accumulate(v.begin(), v.begin() + n, 0);
    };
    std::cout << "5. Сумма первых 10: " << sumFirst10(first) << " " << sumFirst10(second) << "\n";

    long long productFirst = std::accumulate(
        first.begin(), first.end(), 1LL,
        [](long long acc, int x) { return acc * x; });
    long long productSecond = std::accumulate(
        second.begin(), second.end(), 1LL,
        [](long long acc, int x) { return acc * x; });
    std::cout << "4.II.1. Произведение: " << productFirst << " " << productSecond << "\n";

    std::set<int> secondDuplicates;
    for (const auto& [value, count] : freqSecondFor)
        if (count >= 2) secondDuplicates.insert(value);

    std::set<int> firstFrequent;
    for (const auto& [value, count] : freqFirstFor)
        if (count > 3) firstFrequent.insert(value);

    std::cout << "4.II.2. 2-й >=2: ";
    for (int v : secondDuplicates) std::cout << v << " ";
    std::cout << "\n4.II.2. 1-й >3: ";
    for (int v : firstFrequent) std::cout << v << " ";
    std::cout << "\n";

    std::vector<int> result;
    std::set_intersection(
        secondDuplicates.begin(), secondDuplicates.end(),
        firstFrequent.begin(), firstFrequent.end(),
        std::back_inserter(result));

    std::cout << "4.II.3a:\n";
    for (int value : result) {
        int countInFirst = 0, countInSecond = 0;
        for (int x : first)  if (x == value) countInFirst++;
        for (int x : second) if (x == value) countInSecond++;
        std::cout << value << ": " << countInFirst << " " << countInSecond << "\n";
    }

    std::cout << "4.II.3b:\n";
    for (int value : result) {
        int countInFirst = static_cast<int>(std::count_if(
            first.begin(), first.end(),
            [value](int x) { return x == value; }));
        int countInSecond = static_cast<int>(std::count_if(
            second.begin(), second.end(),
            [value](int x) { return x == value; }));
        std::cout << value << ": " << countInFirst << " " << countInSecond << "\n";
    }

    return 0;
}