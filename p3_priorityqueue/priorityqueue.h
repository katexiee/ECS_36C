#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <utility>
#include "json.hpp"
using json = nlohmann::json;

typedef double Key;
typedef std::pair<int, int> Value;
typedef std::pair<Key, Value> KeyValuePair; 

class PriorityQueue {
  public:
    PriorityQueue(std::size_t max_nodes);
    void insert(Key k, int a, int b);
    void insert(Key k, int a, int b, int fifty);//for part 3

    void insert(KeyValuePair kv);
    void insert(KeyValuePair kv, int fifty);//for part 3

    KeyValuePair min();
    KeyValuePair getNode(int i);
    void removeMin();
    void removeMin(int fifty);
    bool isEmpty() const;
    size_t size() const;
    void init();
    nlohmann::json JSON(size_t numOpe) const;   
    void removeNode(size_t i);

  private:
    void heapifyUp(size_t i);
    void heapifyUp(size_t i, int a);//for part 3
    void heapifyDown(size_t i);
    void heapifyDown(size_t i, int fifty);
    Key getKey(size_t i);

    std::vector<KeyValuePair> nodes_;
    size_t max_size_;
    size_t size_;

    const static size_t ROOT = 1;
};  // class PriorityQueue

#endif  // _PRIORITYQUEUE_H_