#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <chrono>
#include <boost/container/flat_set.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/bloom.hpp>

#include "terms.h"

void benchmark(const auto& container, const auto& existing_terms, const auto& non_existing_terms, const std::string& name) {
    std::cout << "\n=== " << name << " ===" << std::endl;
    std::cout << "Set size: " << container.size() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (const auto& term : existing_terms) {
        if (container.contains(term)) count++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Existing terms (" << count << " found): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    count = 0;
    for (const auto& term : non_existing_terms) {
        if (container.contains(term)) count++;
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Non-existing terms (" << count << " found): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;
}

void benchmark_bloom(const auto& filter, const auto& existing_terms, const auto& non_existing_terms, const std::string& name) {
    std::cout << "\n=== " << name << " ===" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (const auto& term : existing_terms) {
        if (filter.may_contain(term)) count++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Existing terms (" << count << " found): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    count = 0;
    for (const auto& term : non_existing_terms) {
        if (filter.may_contain(term)) count++;
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Non-existing terms (" << count << " found): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;
}

int main() {
    std::set<std::string> kabe_set(kabe_terms.begin(), kabe_terms.end());
    std::unordered_set<std::string> kabe_unordered_set(kabe_terms.begin(), kabe_terms.end());
    boost::container::flat_set<std::string> kabe_flat_set(kabe_terms.begin(), kabe_terms.end());
    boost::unordered_flat_set<std::string> kabe_unordered_flat_set(kabe_terms.begin(), kabe_terms.end());

    boost::bloom::filter<std::string, 2> kabe_bloom(kabe_terms.size() * 5);
    for (const auto& term : kabe_terms) {
        kabe_bloom.insert(term);
    }

    std::vector<std::string> existing_terms(kabe_terms.begin(), kabe_terms.begin() + 1000);

    std::vector<std::string> non_existing_terms;
    for (int i = 0; i < 1000; i++) {
        non_existing_terms.push_back(kabe_terms[i] + std::to_string(99999999 + i));
    }

    benchmark(kabe_set, existing_terms, non_existing_terms, "std::set");
    benchmark(kabe_unordered_set, existing_terms, non_existing_terms, "std::unordered_set");
    benchmark(kabe_flat_set, existing_terms, non_existing_terms, "boost::container::flat_set");
    benchmark(kabe_unordered_flat_set, existing_terms, non_existing_terms, "boost::unordered_flat_set");
    benchmark_bloom(kabe_bloom, existing_terms, non_existing_terms, "boost::bloom::filter");

    return 0;
}
