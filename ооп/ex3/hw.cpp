#include <vector>
#include <array>
#include <list>
#include <deque>
#include <iostream>
#include <random>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "hypotenuse_m.h"

int main() {
    const int  M = 15;
    const long N = 50000;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long> dist(-N, N);

    std::vector<long>    vec;
    std::array<long, 15> arr{};
    std::list<long>      lst;
    std::deque<long>     deq;

    for (int i = 0; i < M; ++i) {
        long value = dist(gen);
        vec.push_back(value);
        arr[i] = value;
        lst.push_back(value);
        deq.push_back(value);
    }

    const long noise = dist(gen);

    std::vector<double>    res_vec(M);
    std::array<double, 15> res_arr{};
    std::list<double>      res_lst;
    std::deque<double>     res_deq(M);

    for (int i = 0; i < M; ++i) {
        res_vec[i] = Hypo::hypotenuse<double, long>(vec[i], noise, noise);
    }

    for (int i = 0; i < M; ++i) {
        res_arr[i] = Hypo::hypotenuse<double, long>(arr[i], noise, noise);
    }

    for (std::list<long>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        res_lst.push_back(Hypo::hypotenuse<double, long>(*it, noise, noise));
    }

    std::size_t idx = 0;
    for (const long& value : deq) {
        res_deq[idx++] = Hypo::hypotenuse<double, long>(value, noise, noise);
    }

    std::ostringstream table;
    table << "| Index | Vector | Vector -> Result | Array | Array -> Result "
             "| List | List -> Result | Deque | Deque -> Result |\n";
    table << "|---|---|---|---|---|---|---|---|---|\n";

    std::list<long>::const_iterator   itList    = lst.begin();
    std::list<double>::const_iterator itListRes = res_lst.begin();

    table << std::fixed << std::setprecision(2);
    for (int i = 0; i < M; ++i) {
        table << "| " << i
              << " | " << vec[i]
              << " | " << res_vec[i]
              << " | " << arr[i]
              << " | " << res_arr[i]
              << " | " << *itList
              << " | " << *itListRes
              << " | " << deq[i]
              << " | " << res_deq[i]
              << " |\n";

        ++itList;
        ++itListRes;
    }

    std::ofstream out("read.md");
    out << table.str();
    out.close();

    return 0;
}