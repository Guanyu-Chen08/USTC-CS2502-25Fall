#pragma once

#include "list.h"

namespace DATA_STRUCTURE {

template<class data_base>
class stack : public list<data_base> {
    public:
        stack() = default;
        ~stack() = default;

        bool empty() override {
            // TODO
            return top_index == 0;
        }
        void pop() override {
            // TODO
            if (top_index > 0) top_index--;
        }
        data_base top() override {
            // TODO
            data_base tmp;
            if (top_index > 0)
            {
                tmp = list_data[top_index - 1];
                return tmp;
            }
            return data_base();
        }
        void push(data_base push_data) override {
            // TODO
            if (top_index < MAX_LINK_LIST_NUM) list_data[top_index++] = push_data;
        }
        void clear() override {
            // TODO
            top_index = 0;
        }
    private:
        int top_index = 0;
        data_base list_data[MAX_LINK_LIST_NUM];
};

}
