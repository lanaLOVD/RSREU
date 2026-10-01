#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct FreeBlock {
    int start;
    int size;
    FreeBlock(int s, int sz) : start(s), size(sz) {}
    
    bool operator<(const FreeBlock& other) const {
        if (start != other.start) return start < other.start;
        return size < other.size;
    }
};

struct AllocatedBlock {
    int start;
    int size;
    AllocatedBlock(int s, int sz) : start(s), size(sz) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    
    // Свободные блоки, отсортированные по начальному адресу
    set<FreeBlock> freeBlocks;
    freeBlocks.insert(FreeBlock(1, N));
    
    // Занятые блоки: номер запроса -> блок
    map<int, AllocatedBlock> allocatedBlocks;
    
    vector<int> results;
    
    for (int i = 1; i <= M; i++) {
        int request;
        cin >> request;
        
        if (request > 0) {
            int K = request;
            bool found = false;
            
            // Ищем первый подходящий блок
            for (auto it = freeBlocks.begin(); it != freeBlocks.end(); it++) {
                if (it->size >= K) {
                    // Нашли подходящий блок
                    FreeBlock block = *it;
                    freeBlocks.erase(it);
                    
                    // Выделяем память
                    allocatedBlocks[i] = AllocatedBlock(block.start, K);
                    results.push_back(block.start);
                    
                    // Если остался хвост, добавляем его обратно
                    if (block.size > K) {
                        freeBlocks.insert(FreeBlock(block.start + K, block.size - K));
                    }
                    
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                results.push_back(-1);
            }
            
        } else {
            int T = -request;
            
            auto it = allocatedBlocks.find(T);
            if (it != allocatedBlocks.end()) {
                AllocatedBlock block = it->second;
                allocatedBlocks.erase(it);
                
                // Освобождаем блок
                FreeBlock freedBlock(block.start, block.size);
                auto inserted = freeBlocks.insert(freedBlock);
                auto newIt = inserted.first;
                
                // Объединяем с левым соседом
                if (newIt != freeBlocks.begin()) {
                    auto leftIt = newIt;
                    leftIt--;
                    if (leftIt->start + leftIt->size == newIt->start) {
                        FreeBlock merged(leftIt->start, leftIt->size + newIt->size);
                        freeBlocks.erase(leftIt);
                        freeBlocks.erase(newIt);
                        newIt = freeBlocks.insert(merged).first;
                    }
                }
                
                // Объединяем с правым соседом
                auto rightIt = newIt;
                rightIt++;
                if (rightIt != freeBlocks.end() && newIt->start + newIt->size == rightIt->start) {
                    FreeBlock merged(newIt->start, newIt->size + rightIt->size);
                    freeBlocks.erase(newIt);
                    freeBlocks.erase(rightIt);
                    freeBlocks.insert(merged);
                }
            }
        }
    }
    
    for (int res : results) {
        cout << res << "\n";
    }
    
    return 0;
}
