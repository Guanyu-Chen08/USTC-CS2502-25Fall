#include "walk.h"

namespace DATA_STRUCTURE {

void walk::print_para() {
    std::cout << steps << std::endl;
    for (int i = 0; i < gold_num; i++) {
        std::cout << *(gold + 2 * i) << " " << *(gold + 2 * i + 1) << " " << *(gold_value + i) << std::endl;
    }
}

int walk::compute_distance(int i, int x, int y) {
    // TODO
    int dx = abs((x - gold[2 * i]));
    int dy = abs((y - gold[2 * i + 1]));
    return dx / 2 + dx % 2 + dy / 2 + dy % 2;
}

int walk::get_value() {
    int max_value = 0;
    // TODO
    q.clear();
    element initial;
    initial.steps = steps;
    initial.value = 0;
    initial.x = 0;
    initial.y = 0;
    q.push(initial);

    while (!q.empty())
    {
        struct element current_state = q.top();
        if (current_state.value > max_value) max_value = current_state.value;
        q.pop();

        for (int i = 0; i < gold_num; i++)
        {
            if (!current_state.get_gold.find(i) && compute_distance(i, current_state.x, current_state.y) <= current_state.steps)
            {
                struct element attempt;
                attempt.steps = current_state.steps - compute_distance(i, current_state.x, current_state.y);
                attempt.value = current_state.value + gold_value[i];
                attempt.x = gold[2 * i];
                attempt.y = gold[2 * i + 1];
                attempt.get_gold = current_state.get_gold;
                attempt.get_gold.insert(i);
                q.push(attempt);
            }
        }
    }
    
    return max_value;
}

}