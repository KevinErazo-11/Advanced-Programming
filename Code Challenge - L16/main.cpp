#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <atomic>
#include "barkeep/barkeep.h"

using namespace std::chrono_literals;
namespace bk = barkeep;

std::string parseCSVField(std::stringstream& ss) {
    std::string field;
    if (ss.peek() == '"') {
        ss.get();
        std::getline(ss, field, '"');
        if (ss.peek() == ',') ss.get();
    } else {
        std::getline(ss, field, ',');
    }
    return field;
}

int main(int argc, char** argv) {
    std::ifstream file("data/online_retail.csv");
    if (!file) {
        std::cerr << "Error: cannot open data/online_retail.csv\n";
        return 1;
    }

    // Skip header
    std::string line;
    std::getline(file, line);

    // Count total lines
    size_t total_lines = 0;
    {
        std::ifstream count_file("data/online_retail.csv");
        std::string tmp;
        std::getline(count_file, tmp);
        while (std::getline(count_file, tmp)) ++total_lines;
    }

    std::atomic<size_t> work{0};
    auto bar = bk::ProgressBar(&work, {
        .total = total_lines,
        .format = "Processing lines {8}{0:6d}/{3}  {6}{1} {7}{2:3.0f}%{11}  ({4:.1f} line/s)",
        .speed = 0.1
    });

    std::unordered_map<std::string, int> counts;
    double uk_total = 0.0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        // Parse fields
        std::string invoice, stock, desc, qty_s, date, price_s, cust, country;
        invoice  = parseCSVField(ss);
        stock    = parseCSVField(ss);
        desc     = parseCSVField(ss);
        qty_s    = parseCSVField(ss);
        date     = parseCSVField(ss);
        price_s  = parseCSVField(ss);
        cust     = parseCSVField(ss);
        country  = parseCSVField(ss);

        int qty = 0; double price = 0.0;
        try {
            qty   = std::stoi(qty_s);
            price = std::stod(price_s);
        } catch (...) {}

        counts[country]++;
        if (country == "United Kingdom") uk_total += qty * price;

        ++work;
        std::this_thread::sleep_for(5ms); // Optional: simulate delay
    }

    bar->done();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Transactions by country:\n";
    for (auto& [c, cnt] : counts)
        std::cout << "  " << c << ": " << cnt << "\n";
    std::cout << "Total UK amount: £" << uk_total << "\n";

    return 0;
}
