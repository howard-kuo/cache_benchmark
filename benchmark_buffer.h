#pragma once
#include <vector>
#include <chrono>
#include <random>


class BenchmarkBuffer {
    std::vector<uint32_t> idx_vec;
    std::vector<uint32_t> content;
    volatile uint32_t sum = 0;
public:
    BenchmarkBuffer(const std::vector<uint32_t>& idx_vec, uint32_t content_size) {
        this->idx_vec = idx_vec;
        content.resize(content_size);
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<uint32_t> dist(1, 100);
        for (auto & c : content) {
            c = dist(gen);
        }
    }
    uint64_t test() {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (auto idx : idx_vec) {
            sum += content[idx];
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    }
};

