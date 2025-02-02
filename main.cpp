
#include <benchmark_buffer.h>
#include <iostream>
#include <vector>
#include <random> 


using namespace std;

vector<uint32_t> getIdxVecUnif(uint32_t test_size, uint32_t buffer_size) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<uint32_t> dist(0, buffer_size);
    vector<uint32_t> idx_vec;
    for (size_t i = 0; i < test_size; i++) {
        idx_vec.push_back(dist(gen));
    }
    return idx_vec;
}
vector<uint32_t> getIdxVecRandStep(uint32_t test_size, uint32_t buffer_size, uint32_t step_size) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<uint32_t> dist(0, buffer_size);
    vector<uint32_t> idx_vec;
    for (size_t i = 0; i < test_size; i++) {
        if (i % 8 == 0) {
            idx_vec.push_back(dist(gen));
        } else {
            uint32_t val = (idx_vec.back() + step_size) % buffer_size;
            idx_vec.push_back(val);
        }
    }
    return idx_vec;
}



int main() {
    cout << "benchmark start:" << endl;
    const size_t unit = 1;
    const size_t test_count = 100 * 10000;
    const size_t max_buffer_size = unit * 100;
    double base = 10;
    for (size_t i = 1; i < 10000; i++) {
        base *= 1.1;
        const size_t buffer_size = unit * int(base);
        // auto idx_vec = getIdxVecUnif(test_count, buffer_size);
        auto idx_vec = getIdxVecRandStep(test_count, max_buffer_size, i);
        auto buf = BenchmarkBuffer(idx_vec, buffer_size);
        cout << "   Test: " << i << "-" << unit * 4 << "B" << ", time=" << buf.test() << " (us per 1 million access)" << endl;
        i++;
    }
    
    return 0;
}