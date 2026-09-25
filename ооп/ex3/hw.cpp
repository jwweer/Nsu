#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <random>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using T1 = int;
using T2 = double;
const int M = 8;
const int N = 20;

T2 extended_modified(T1 a, T1 b) {
    return static_cast<T2>(a) + static_cast<T2>(b) / 10.0;
}

int main() {
    std::mt19937 gen(42);
    std::uniform_int_distribution<T1> dist(-N, N);

    std::array<T1, M> arr;
    std::vector<T1> vec(M);
    std::list<T1> lst(M);
    std::deque<T1> deq(M);

    for (int i = 0; i < M; ++i) arr[i] = dist(gen);
    for (auto it = vec.begin(); it != vec.end(); ++it) *it = dist(gen);
    for (auto& x : lst) x = dist(gen);
    for (auto& x : deq) x = dist(gen);

    T1 secondArg = dist(gen);

    std::vector<T2> res_arr(M);
    std::list<T2>   res_vec(M);
    std::deque<T2>  res_lst(M);
    std::array<T2, M> res_deq;

    for (int i = 0; i < M; ++i)
        res_arr[i] = extended_modified(arr[i], secondArg);

    {
        auto itRes = res_vec.begin();
        for (auto it = vec.begin(); it != vec.end(); ++it, ++itRes)
            *itRes = extended_modified(*it, secondArg);
    }

    {
        auto itRes = res_lst.begin();
        for (const auto& x : lst) {
            *itRes = extended_modified(x, secondArg);
            ++itRes;
        }
    }

    for (int i = 0; i < M; ++i)
        res_deq[i] = extended_modified(deq[i], secondArg);

    std::vector<std::string> rows;
    rows.push_back("| array | vector | list | deque | res_arr | res_vec | res_lst | res_deq |");

    auto it_arr = arr.begin();  auto it_vec = vec.begin();
    auto it_lst = lst.begin();  auto it_deq = deq.begin();
    auto it_ra  = res_arr.begin(); auto it_rv = res_vec.begin();
    auto it_rl  = res_lst.begin(); auto it_rd = res_deq.begin();

    for (int i = 0; i < M; ++i) {
        std::ostringstream oss;
        oss << "| " << *it_arr << " | " << *it_vec << " | " << *it_lst
            << " | " << *it_deq << " | " << std::fixed << std::setprecision(2)
            << *it_ra << " | " << *it_rv << " | " << *it_rl
            << " | " << *it_rd << " |";
        rows.push_back(oss.str());
        ++it_arr; ++it_vec; ++it_lst; ++it_deq;
        ++it_ra;  ++it_rv;  ++it_rl;  ++it_rd;
    }

    std::ofstream out("table.md");
    out << rows[0] << "\n";
    out << "|---|---|---|---|---|---|---|---|\n";
    for (size_t i = 1; i < rows.size(); ++i)
        out << rows[i] << "\n";
    out.close();

    return 0;
}