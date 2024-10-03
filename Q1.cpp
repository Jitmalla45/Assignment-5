#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Expr {
private:
    string expression;

    int performOperation(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }

    int evaluateExpression() {
        stack<int> values;     
        stack<char> operators; 
        
        for (int i = 0; i < expression.length(); i++) {
            char ch = expression[i];

            if (isdigit(ch)) {
                values.push(ch - '0');
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                // Perform operations for * and / first, then push other operators
                while (!operators.empty() && (operators.top() == '*' || operators.top() == '/')) {
                    int b = values.top(); values.pop();
                    int a = values.top(); values.pop();
                    char op = operators.top(); operators.pop();
                    values.push(performOperation(a, b, op));
                }
                operators.push(ch);
            }
        }

        while (!operators.empty()) {
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            char op = operators.top(); operators.pop();
            values.push(performOperation(a, b, op));
        }

        return values.top();
    }

public:
    Expr(const char* expr) : expression(expr) {}
    int eval() {
        return evaluateExpression();
    }
    void print() {
        cout << "Expression: " << expression << endl;
    }
};

int main() {

    
    // Expr x("8/4+3*4-3");
    // std::cout << "x = " << x.eval() << "\n";
    // x.print();
    // return 0;

    string userExpression;
    cout << "Enter an arithmetic expression: ";
    cin >> userExpression;
    Expr x(userExpression.c_str());
    cout << "x = " << x.eval() << "\n";
    x.print();
    
    return 0;
}
