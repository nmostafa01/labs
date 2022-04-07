

#include <string>
#include "calculator.h"
#include "expressionstream.h"
#include "lifo.h"
#include <iostream>
#include <stack>


namespace lab4 {
    void calculator::parse_to_infix(std::string &input_expression) {
        lab1::expressionstream parser(input_expression);
        std::string token = parser.get_next_token();
        while (token != "\0") { //loop untill we get null char. i.e. enbd oif the string
            infix_expression.enqueue(token);
            token = parser.get_next_token();
        }
    }

    void calculator::convert_to_postfix(lab3::fifo infix_expressionn) {
        lab3::lifo st = lab3::lifo();
        std::string result;
        std::string current_token;
        lab3::lifo op_stack;

        while(!infix_expressionn.is_empty()) {//while there are tokens to be read:
            current_token = infix_expressionn.front();
            infix_expressionn.front();//read a token.
            /*
             * IMPORTANT: Remember to refer to our algorithm of infix to postfix conversion using Stack.
             *  The below steps replicates the same Functionality
             */
            if (is_number(current_token)) postfix_expression.enqueue(current_token);//if the token is a number, then push it to the output queue.
            else if (is_operator(current_token)) {//if the token is an operator, then:
                while (!op_stack.is_empty() && operator_priority(op_stack.top()) >= operator_priority(current_token)
                       &&
                       op_stack.top() != "(") {     //while ((there is an operator at the top of the operator stack with
                    //greater precedence) or (the operator at the top of the operator stack has
                    //equal precedence and
                    //the operator is left associative)) and
                    //(the operator at the top of the stack is not a left bracket):
                    postfix_expression.enqueue(
                            op_stack.top()); //pop operators from the operator stack, onto the output queue.
                    op_stack.pop();
                }
                op_stack.push(current_token);
            }//push the read operator onto the operator stack.
            else if(current_token == "(")//if the token is a left bracket (i.e. "("), then:
                op_stack.push(current_token);//push it onto the operator stack.
            else if (current_token == ")") {//if the token is a right bracket (i.e. ")"), then:
                while (op_stack.top() !=
                       "(") { //while the operator at the top of the operator stack is not a left bracket:
                    postfix_expression.enqueue(op_stack.top());
                    op_stack.pop(); //pop operators from the operator stack onto the output queue.
                }
                op_stack.pop();//pop the left bracket from the stack.
            }
            infix_expressionn.dequeue();
        }
        while(!op_stack.is_empty()) {    //while there are still operator tokens on the stack:
            if (op_stack.top() ==
                "(") { throw "mismatched parenthesis"; }///* if the operator token on the top of the stack is a bracket, then
            //there are mismatched parentheses. */
            postfix_expression.enqueue(op_stack.top());//pop the operator onto the output queue.
            op_stack.pop();
        }
        //exit.
    }

    calculator::calculator() {

    }

    calculator::calculator(std::string &input_expression) {
        parse_to_infix(input_expression); // this is working fine
       convert_to_postfix(infix_expression); // this is issue
    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) {
        // This is just like regular instream operation
        // something like std::cin >> num
        // the RHS to the operator is a Calculator object.
        // we clear the  queues of infix and postfix first in RHS object,
        // we use calculator methods to parse to infix and post fiix after that;
        // so in other words, if we pass expression as string after << ,
        // an object of type Calculator class is generated automatically.

        std::istreambuf_iterator<char> eos;
        std::string input_expression(std::istreambuf_iterator<char>(stream), eos);

        RHS.clear_expressions();

        RHS.parse_to_infix(input_expression);
        RHS.convert_to_postfix(RHS.infix_expression);
        return stream;
    }

    int lab4::calculator::calculate() {
        lab3::lifo op_stack;
        lab3::fifo eq_queue(postfix_expression);
        int lhs,rhs;
        /*
         *
         * Again, remember our discussion form the class on how to use postfix expression to calculate the arithmatic expression.
         * In case of doubt, refer to the link below for detailed explaination
         * https://www.geeksforgeeks.org/stack-set-4-evaluation-postfix-expression/
         */
        while(!eq_queue.is_empty()){  // we have to iterate the postfix queue till it's empty
            while(is_number(eq_queue.front())){ // as long as the fron of the postfix queue is a number, push it to the stack.
                op_stack.push(eq_queue.front());
                eq_queue.dequeue();
            }
            // in case of operator, pop the two numbers from the stack; the first popped one is rhs and the next popped number is lhs
            // res = lhs (operatot) rhs
            // once the calculation is complete, push the result back to the stack again.
            rhs = stoi(op_stack.top());
            op_stack.pop();
            lhs = stoi(op_stack.top());
            op_stack.pop();
            op_stack.push(std::to_string(calc_binary_operation(lhs,rhs,eq_queue.front())));
            eq_queue.dequeue();
        }
        return stoi(op_stack.top());

    }

    std::ostream &operator<<(std::ostream &stream, calculator &RHS) {
        //Infix: 1,+,2,+,3
        //Postfix: 1,2,+,3,+
        lab3::fifo infix_copy = RHS.infix_expression;
        lab3::fifo postfix_copy = RHS.postfix_expression;
        stream << "Infix: " << infix_copy.front();
        // we have to append commas at the end of the each token in respective formats.
        // keep on appending commas and next token untill the infix copy queue is empty.
        for(infix_copy.dequeue(); !infix_copy.is_empty(); infix_copy.dequeue()) stream << "," << infix_copy.front();
        stream << "\nPostfix: " << postfix_copy.front();
        // the similar steps discussed above are followed here.
        for(postfix_copy.dequeue(); !postfix_copy.is_empty(); postfix_copy.dequeue()) stream << "," << postfix_copy.front();
        return stream;
    }


    // AUXILIARY FUNCTIONS
    bool calculator::is_number(std::string input_string){
        std::string::iterator location = input_string.begin();
        if(*location >= '0' && *location <= '9') return true;
        if(*location != '-')return false;
        return(*++location >='0' && *location <= '9');
    }

    bool calculator::is_operator(std::string input_string){
        if(input_string == "+" ||input_string == "-" || input_string == "*" || input_string == "/" || input_string == "^"){
            return true;
        }
        else return false;
    }

    int calculator::get_number(std::string input_string){
        return std::stoi( input_string );
    }

    std::string get_operator(std::string input_string);

    int calculator::operator_priority(std::string operator_in){
        if(operator_in == "^")
            return 3;
        else if(operator_in == "/" || operator_in=="*")
            return 2;
        else if(operator_in == "+" || operator_in == "-")
            return 1;
        else
            return -1;

    }
    int calculator::calc_binary_operation(int lhs, int rhs, std::string op) {
        std::string::iterator op_iter = op.begin();
        switch (*op_iter){
            case '^': return lhs ^ rhs;
            case '*': return lhs * rhs;
            case '/': return lhs / rhs;
            case '+': return lhs + rhs;
            case '-': return lhs - rhs;
            default: throw "unknown operator";
        }
    }
    void calculator::clear_expressions() {
        while(!infix_expression.is_empty()) infix_expression.dequeue();
        while(!postfix_expression.is_empty()) postfix_expression.dequeue();
    }
}