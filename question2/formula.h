#ifndef FORMULA_H
#define FORMULA_H

#include <vector>
#include <string>
#include <iostream>

bool is_numeric(char c) {
    return '0' <= c && c <= '9';
}

bool is_operator(char c) {
    return c == '+' || c == '-' || c == 'x' || c == '/' || c == '%';
}

enum TokenType {
    Start,
    Integer,
    Float,
    IntegerMoFloat,
    Add,
    Subtract,
    Divide,
    Multiply,
    Modulo,
    Error,
};

struct Token {
    std::string string;
    TokenType type;
    Token() {
        type = Start;
    }
    Token(char c, bool no_float = false) {
        string += c;
        switch(c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                type = Integer;
                if(no_float) type = IntegerMoFloat;
                break;
            case '.':
                type = Float;
                string = "0.";
                break;
            case '+':
                type = Add;
                break;
            case '-':
                type = Subtract;
                break;
            case 'x':
                type = Multiply;
                break;
            case '/':
                type = Divide;
                break;
            case '%':
                type = Modulo;
                break;
            default:
                type = Error;
                break;
        }
    }
    int length() {
        return string.length();
    }
    bool append(std::string s) {
        return append(s.at(0));
    }
    bool append(char c) {
        if((type == Integer || type == Float || type == IntegerMoFloat) && is_numeric(c)) {
            string += c;
            return true;
        }    
        if(type == Integer && c == '.') {
            string += c;
            type = Float;
            return true;
        }
        return false;        
    }
    int higher(const Token& t) {
        if((type == Multiply || type == Divide || type == Modulo) && (t.type == Integer || t.type == Float)) return true; 
        return false;
    }
    bool is_left() {
        return false;

    }
};

bool is_operator(const Token& t) {
    if(t.type == Start) return false;
    auto c = t.string.at(0);
    return c == '+' || c == '-' || c == 'x' || c == '/' || c == '%';
}

class Formula {
    private:
    std::vector<Token> tokens;

    public:
    Formula() {
        tokens.push_back(Token());
    }
    bool append(char c) {
        if(tokens.back().append(c)) return true;
        if(is_operator(c) && is_operator(tokens.back())) return false;
        if(tokens.back().type == Float && c == '.') return false;
        if(tokens.back().type == Start && (c == 'x' || c == '/' || c == '+')) return false;
        if(tokens.back().type == IntegerMoFloat && c == '.') return false;
        if(c == '%' && !(tokens.back().type == Integer || tokens.back().type == IntegerMoFloat)) return false;
        if(tokens.back().type == Modulo && is_numeric(c)) {
            tokens.push_back(Token(c, true));
            return true;
        }
        tokens.push_back(Token(c));
        return true;
    }
    std::string to_string() {
        std::string final = "";
        for(auto& t: tokens) {
            final += t.string;
        }
        return final;
    }
    int size() {
        return tokens.size() - 1;
    }
    bool all_clear() {
        while(tokens.size() > 1) tokens.pop_back();
        return true;
    }
    bool backspace() {
        auto& tail = tokens.back();
        switch(tail.type) {
            case Start:
                return false;
            case Integer:
                if(tail.length() == 1) 
                    tokens.pop_back();
                else
                    tail.string = tail.string.substr(0, tail.string.length() - 1);
                return true;
            case Float:
                if(tail.length() == 1)
                    tokens.pop_back();
                else {
                    if(tail.string.back() == '.') tail.type = Integer;
                    tail.string = tail.string.substr(0, tail.string.length() - 1);
                }
                return true;
            case Add:
            case Subtract:
            case Multiply:
            case Divide:
            case Modulo:
                tokens.pop_back();
                return true;
            default:
                return false;
        }
    }
    bool invert_sign() {
        if(size() == 0) return false;
        for(auto t = tokens.rbegin(); t != tokens.rend(); t++) {
            if(t->type == Add) {
                t->string = "-";
                t->type = Subtract;
                return true;
            }
            if(t->type == Subtract) {
                if((t + 1)->type == Start) {
                    tokens.erase(tokens.begin() + 1, tokens.begin() + 2);
                    return true;
                }
                t->string = "+";
                t->type = Add;
                return true;
            }
        }
        tokens.insert(tokens.begin()+1, Token('-'));
        return true;
    }

    void operator=(std::string text) {
        all_clear();
        for(auto c: text) {
            if(!this->append(c)) std::cerr << "formula rejected " << c << "\n";
        }
    }

    bool evaluate() {
        std::vector<Token> stack1, stack2;
        stack1.push_back(Token());
        stack2.push_back(Token());
        if((tokens.begin() + 1)->type == Subtract) stack1.push_back(Token('0'));
        for(auto t = tokens.begin() + 1; t != tokens.end(); t ++) {
            switch(t->type) {
                case Integer:
                case Float:
                    stack1.push_back(*t);
                    break;
                case Multiply:
                case Divide:
                case Modulo:
                    if(t->higher(*stack2.end())) return false;

                default:
                return false; 
            }
        }
        
        return false;
    }
};

#endif