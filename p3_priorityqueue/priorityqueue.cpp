#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "json.hpp"
#include "priorityqueue.h"
using json = nlohmann::json;
using namespace std;

PriorityQueue::PriorityQueue(size_t max_size) :
	nodes_(0, KeyValuePair()),
	max_size_(max_size), 
	size_(0) {
}

void PriorityQueue::insert(Key k, int a, int b) { 
	insert(make_pair(k, make_pair(a, b)));
}

void PriorityQueue::insert(Key k, int a, int b, int fifty) { 
	insert(make_pair(k, make_pair(a, b)), fifty);
}

void PriorityQueue::insert(KeyValuePair kv) {
	nodes_.push_back(kv);
  size_ = size_ + 1;
  heapifyUp(size_);
}

void PriorityQueue::insert(KeyValuePair kv, int fifty) {
	nodes_.push_back(kv);
  size_ = size_ + 1;
  heapifyUp(size_, fifty);
}


KeyValuePair PriorityQueue::min() {
	return nodes_[1];
}

KeyValuePair PriorityQueue::getNode(int i) {
  return nodes_[i];
}

void PriorityQueue::removeMin() { 
  nodes_[1] = nodes_[size_]; 
  vector<KeyValuePair>::iterator it;
  it = nodes_.end();
  nodes_.erase(it);
  size_ = size_ - 1;
  heapifyDown(1); 
}


bool PriorityQueue::isEmpty() const {
	return size_ == 0;
}

size_t PriorityQueue::size() const {
	return size_;
}

void PriorityQueue::init() {
  size_ = 0;
  Key key = 0.0;
  Value val(0, 0);
  KeyValuePair kv;
  kv.first = key;
  kv.second = val;
  nodes_.push_back(kv);
}


json PriorityQueue::JSON(size_t numOpe) const {
  json result;
  for (size_t i = 1; i <= size_; i++) {
    json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] =to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = to_string(2 * i + 1);
      }
      result[to_string(i)] = node;
  }
  result["metadata"]["maxHeapSize"] = max_size_;
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["numOperations"] = numOpe;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	for(size_t cnt = i; cnt > 1 && nodes_[cnt].first < nodes_[cnt/2].first; cnt = cnt / 2) {
    KeyValuePair tem = nodes_[cnt];
    nodes_[cnt] = nodes_[cnt/2];
    nodes_[cnt/2] = tem;
  }
}

void PriorityQueue::heapifyDown(size_t i) {
  size_t cnt = i;
  if(size_ <= 2) {
    if(size_ == 1){
      //Do nothing
    }
    else {
      if(nodes_[1] > nodes_[2]) {
        KeyValuePair tem = nodes_[1];
        nodes_[1] = nodes_[2];
        nodes_[2] = tem;
      }
      else {
        //Do nothing
      }
    }
  }
  else {
    while(cnt * 2 <= size_) {
    if(nodes_[cnt * 2].first > nodes_[cnt * 2 + 1].first) {
      if(nodes_[cnt * 2 + 1].first < nodes_[cnt].first) {
        KeyValuePair tem = nodes_[cnt];
        nodes_[cnt] = nodes_[cnt * 2 + 1];
        nodes_[cnt * 2 + 1] = tem;
        cnt = cnt * 2 + 1;
      }
      else {
        break;
      }
    }
    else if(nodes_[cnt * 2].first < nodes_[cnt * 2 + 1].first) {
      if(nodes_[cnt * 2].first < nodes_[cnt].first) {
        KeyValuePair tem = nodes_[cnt];
        nodes_[cnt] = nodes_[cnt * 2];
        nodes_[cnt * 2] = tem;
        cnt = cnt * 2;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }
}
}

void PriorityQueue::removeNode(size_t i) {
  nodes_[i] = nodes_[size_]; //replace the node with last node 
  vector<KeyValuePair>::iterator it;
  it = nodes_.end();
  nodes_.erase(it); //delete last node 
  // int fifty = 50; 
  size_ = size_ - 1;
  heapifyDown(i); 
    heapifyUp(i);
  // heapifyUp(i,fifty);
  // heapifyDown(i,fifty);
}

Key PriorityQueue::getKey(size_t i) {
	return nodes_[i].first;
  }


void PriorityQueue::removeMin(int fifty) { 
  nodes_[1] = nodes_[size_]; 
  vector<KeyValuePair>::iterator it;
  it = nodes_.end();
  nodes_.erase(it);
  size_ = size_ - 1;
  heapifyDown(1, fifty); 
} 

void PriorityQueue::heapifyUp(size_t i, int fifty) { //i is the pos 
	for(size_t cnt = i; cnt > 1 && abs(nodes_[cnt].first - fifty) < abs(nodes_[cnt/2].first - fifty); cnt = cnt / 2) { //cnt is the pos
    KeyValuePair tem = nodes_[cnt];
    nodes_[cnt] = nodes_[cnt/2];
    nodes_[cnt/2] = tem;
  }
}

void PriorityQueue::heapifyDown(size_t i, int fifty) {
  size_t cnt = i;
  if(size_ <= 2) {
    if(size_ == 1){// || size_ == 0
      //Do nothing 
    }
    else {
      if(abs(nodes_[1].first - fifty) > abs(nodes_[2].first - fifty)) { 
        KeyValuePair tem = nodes_[1];
        nodes_[1] = nodes_[2];
        nodes_[2] = tem;
      }
      else {
        //Do nothing
      }
    }
  }
    
  else {
    while(cnt * 2 <= size_) { // check if there are another row below
    if(abs(nodes_[cnt * 2].first - fifty) > abs(nodes_[cnt * 2 + 1].first - fifty)) { //left side > right side 
      if(abs(nodes_[cnt * 2 + 1].first - fifty) < abs(nodes_[cnt].first - fifty)) {
        KeyValuePair tem = nodes_[cnt];
        nodes_[cnt] = nodes_[cnt * 2 + 1];
        nodes_[cnt * 2 + 1] = tem;
        cnt = cnt * 2 + 1;
      }
      else {
        break;
      }
    }
      //abs(nodes_[cnt].first - fifty)
    else if(abs(nodes_[cnt * 2].first - fifty) < abs(nodes_[cnt * 2 + 1].first - fifty)) {
      if(abs(nodes_[cnt * 2].first - fifty) < abs(nodes_[cnt].first - fifty)) {
        KeyValuePair tem = nodes_[cnt];
        nodes_[cnt] = nodes_[cnt * 2];
        nodes_[cnt * 2] = tem;
        cnt = cnt * 2;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }
}
}