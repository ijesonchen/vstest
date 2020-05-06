#include <chrono>
#include <string>
#include <vector>
#include <iostream>

// for debug only
class Ticker {
public:
    struct TagCost {
        std::string tag;
        uint64_t    cost;

        TagCost(uint64_t c, std::string& t) { cost = c; tag = t; };
    };
    Ticker() { start = std::chrono::high_resolution_clock::now(); }

    // cost in us
    int64_t TockNoRecord() { 
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        start = end;
        return elapsed.count();
    }
    int64_t Tock(std::string tag) { 
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        costs.push_back(TagCost(elapsed.count(), tag));

        start = end;
        return elapsed.count();
    }
    void Reset(void) { start = std::chrono::high_resolution_clock::now(); costs.clear(); }
    void Print(void) {
        for (auto& c : costs) {
            std::cout << "==> " << c.tag << " COST " << c.cost << " us";
        }
    }
    std::vector<TagCost> GetCosts(void) { return costs; }
private:
    std::chrono::high_resolution_clock::time_point start;
    std::vector<TagCost> costs;
};