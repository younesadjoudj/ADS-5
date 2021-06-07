// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
  struct ITEM {
     T data;
     ITEM* prev;
     ITEM* next;
  };
  ITEM* head;
  ITEM* tail;
  TPQueue::ITEM* create(const T& data, ITEM*prev) {
     ITEM* item = new ITEM;
     item->next = nullptr;
     item->prev = prev;
     item->data = data;
     return item;
  }

 public:
  TPQueue() :tail(nullptr), head(nullptr) {}
  ~TPQueue() {
    while (head)
      pop();
  }

  void push(const T& data) {
    if (tail && head) {
      ITEM* current = tail;
      while (current && data.prior > (current->data).prior) {
        current = current->prev;
      }
      if (current) {
        ITEM* temp = current->next;
        current->next = create(data, current);
        current = current->next;
        current->next = temp;
        if (temp)
          temp->prev = current;
        else
          tail = current;
      } else {
        current = create(data, nullptr);
        current->next = head;
        head->prev = current;
        head = current;
      }
    } else {
      head = create(data, nullptr);
      tail = head;
    }
  }

  T pop() {
      assert(head);
      ITEM* temp = head->next;
      T data = head->data;
      if (temp)
        temp->prev = nullptr;
      delete head;
      head = temp;
      return data;
  }
};

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
