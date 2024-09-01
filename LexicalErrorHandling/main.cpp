//
//  main.cpp
//  LexicalErrorHandling
//
//  Created by Assier Anteneh Alemu on 15/08/2024.
//

#include <iostream>
#include <cctype>
#include <string>

// Enum to define different token types
enum class TokenType {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    UNKNOWN,
    END
};

// Class to represent a Token
class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType t, std::string v) : type(t), value(v) {}
};

// Class for the Lexical Analyzer
class LexicalAnalyzer {
private:
    std::string input;
    size_t index;

    // Function to skip whitespace
    void skipWhitespace() {
        while (index < input.length() && std::isspace(input[index])) {
            index++;
        }
    }

    // Function to handle identifiers
    Token handleIdentifier() {
        std::string value;
        while (index < input.length() && (std::isalnum(input[index]) || input[index] == '_')) {
            value += input[index++];
        }
        return Token(TokenType::IDENTIFIER, value);
    }

    // Function to handle numbers
    Token handleNumber() {
        std::string value;
        while (index < input.length() && std::isdigit(input[index])) {
            value += input[index++];
        }
        return Token(TokenType::NUMBER, value);
    }

    // Function to handle operators
    Token handleOperator() {
        std::string value(1, input[index++]);
        return Token(TokenType::OPERATOR, value);
    }

public:
    LexicalAnalyzer(const std::string& str) : input(str), index(0) {}

    // Function to get the next token
    Token nextToken() {
        skipWhitespace();

        if (index >= input.length()) {
            return Token(TokenType::END, "");
        }

        char currentChar = input[index];
        if (std::isalpha(currentChar) || currentChar == '_') {
            return handleIdentifier();
        }
        if (std::isdigit(currentChar)) {
            return handleNumber();
        }
        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '=') {
            return handleOperator();
        }
        
        // Handle unknown characters
        std::cerr << "Error: Unknown character '" << currentChar << "' at position " << index << std::endl;
        index++;
        return Token(TokenType::UNKNOWN, std::string(1, currentChar));
    }
};

int main() {
    std::string input;
    std::cout << "Enter the input string: ";
    std::getline(std::cin, input);

    LexicalAnalyzer lexer(input);

    Token token = lexer.nextToken();
    while (token.type != TokenType::END) {
        switch (token.type) {
            case TokenType::IDENTIFIER:
                std::cout << "Identifier: " << token.value << std::endl;
                break;
            case TokenType::NUMBER:
                std::cout << "Number: " << token.value << std::endl;
                break;
            case TokenType::OPERATOR:
                std::cout << "Operator: " << token.value << std::endl;
                break;
            case TokenType::UNKNOWN:
                std::cerr << "Lexical error: Invalid token '" << token.value << "'" << std::endl;
                break;
            default:
                break;
        }
        token = lexer.nextToken();
    }

    return 0;
}

