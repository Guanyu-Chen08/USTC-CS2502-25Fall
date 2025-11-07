#include "calculator.h"
#include <stdexcept>

namespace DATA_STRUCTURE {

std::string calculator::get_expr() {
    return expr;
}

bool calculator::legal() {
    int bracket = 0;
    // TODO
    bool last_is_operator = true;
    int i;
    
    for (i = 0; i < expr.length(); i++)
    {
        char c = expr[i];

        if (c == ' ') continue;

        else if (c == '(')
        {
            bracket++;
            if (!last_is_operator) return false;
            last_is_operator = true;
        }

        else if (c == ')')
        {
            bracket--;
            if (bracket < 0 || last_is_operator) return false;
            last_is_operator = false;
        }

        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            if (last_is_operator && i > 0)
            {
                if (c == '-' && i > 0 && expr[i-1] == '(')
                {
                    last_is_operator = true;
                    continue;
                }
                return false;
            }
            last_is_operator = true;
        }

        else if (isdigit(c) || c == '.')
        {
            last_is_operator = false;

            if (c == '.')
            {
                bool has_digit_before = (i > 0 && isdigit(expr[i-1]));
                bool has_digit_after = (i + 1 < expr.length() && isdigit(expr[i+1]));
                
                if (!has_digit_before && !has_digit_after)
                {
                    return false;
                }
            }
        }

        else return false;
    }

    if (last_is_operator) return false;

    return bracket == 0;
}

int calculator::priority_regular(char c) {
    // TODO
    if (c == '+' || c == '-') return 1;

    if (c == '*' || c == '/') return 2;

    if (c == '^') return 3;

    return 0;
}

int calculator::priority(char c1, char c2) {
    // TODO
    int p1 = priority_regular(c1);
    int p2 = priority_regular(c2); 
    
    if (c1 == '(' || c2 == '^') return 0;
    
    return p1 >= p2 ? 1 : 0;
}

struct calculator::element calculator::read_num() {
    int num = 0, expo = 0, flag = 0;
    // TODO
    double num2 = 0;

    while (expr[expr_index] == ' ') expr_index++;

    while (expr_index < expr.length() && isdigit(expr[expr_index]) || expr[expr_index] == '.')
    {
        while (expr_index < expr.length() && isdigit(expr[expr_index]))
        {
            num = num * 10 + (expr[expr_index] - '0');
            expr_index++;
        }
        if (expr_index < expr.length() && expr[expr_index] == '.')
        {
            flag = 1;
            expr_index++;
            num2 = (double)num;
            double weight = 0.1;
            while (expr_index < expr.length() && isdigit(expr[expr_index]))
            {
                num2 += (expr[expr_index] - '0') * weight;
                weight *= 0.1;
                expr_index++;
            }
        }
    }
    
    if (flag) return {flag, 0, num2};

    return {flag, num, 0.0};
}

struct calculator::element calculator::operate(struct calculator::element element1, char c, struct calculator::element element2) {
    // TODO
    double val1 = (element1.flag == 0) ? element1.num_int : element1.num_double;
    double val2 = (element2.flag == 0) ? element2.num_int : element2.num_double;
    double result = 0.0;
    
    switch(c)
    {
        case '+':
            result = val1 + val2;
            break;
        case '-':
            result = val1 - val2;
            break;
        case '*':
            result = val1 * val2;
            break;
        case '/':
            if (val2 == 0) throw std::invalid_argument("Error: Divided by zero");
            result = val1 / val2;
            break;
        case '^':
            if (val1 == 0 && val2 <= 0) throw std::invalid_argument("Error: Zero to a negative exponent is undefined");
            result = pow(val1, val2);
            break;
    }
    
    if (result == floor(result) || result == ceil(result)) return {0, (int)result, 0.0};
    return {1, 0, result};
}

struct calculator::element calculator::get_ans() {
    // TODO
    num.clear();
    op.clear();
    expr_index = 0;
    bool expect_number = true; //区分减号和负号

    while (expr_index < expr.length())
    {
        if (expr[expr_index] == ' ')
        {
            expr_index++;
            continue;
        }

        if (isdigit(expr[expr_index]) || expr[expr_index] == '.')
        {
            num.push(read_num());
            expect_number = false;
        }

        else if (expr[expr_index] == '-' && expect_number)
        {
            num.push({0, 0, 0.0});
            op.push('-');
            expect_number = true;
            expr_index++;
        }

        else if (expr[expr_index] == '(')
        {
            op.push(expr[expr_index]);
            expect_number = true;
            expr_index++;
        }

        else if (expr[expr_index] == ')')
        {
            while (op.top() != '(')
            {
                char current_operator = op.top();
                op.pop();
                element element2 = num.top();
                num.pop();
                element element1 = num.top();
                num.pop();

                num.push(operate(element1, current_operator, element2));
            }
            op.pop();
            expect_number = false;
            expr_index++;
        }

        else if (expr[expr_index] == '+' || expr[expr_index] == '-' || expr[expr_index] == '*' || expr[expr_index] == '/' || expr[expr_index] == '^')
        {
            while (priority(op.top(), expr[expr_index]))
            {
                char current_operator = op.top();
                op.pop();
                element element2 = num.top();
                num.pop();
                element element1 = num.top();
                num.pop();

                num.push(operate(element1, current_operator, element2));
            }
            op.push(expr[expr_index]);
            expect_number = true;
            expr_index++;
        }
    }

    while (!op.empty())
    {
        char current_operator = op.top();
        op.pop();
        element element2 = num.top();
        num.pop();
        element element1 = num.top();
        num.pop();

        num.push(operate(element1, current_operator, element2));
    }
    return num.empty() ? element{0, 0, 0.0} : num.top();
}

}