#ifndef LEX_H
#define LEX_H

#include <map>
#include <cctype>
#include <string>
#include <iostream>

//////// Defining the types /////////

// Operators
const std::string PLUS = "+";
const std::string MINUS = "-";
const std::string ASTERISK = "*";
const std::string SLASH = "/";
const std::string LT = "<";
const std::string GT = ">";
const std::string ASSIGN = "=";
const std::string BANG = "!";
const std::string EQ = "==";
const std::string NOT_EQ = "!=";

// Delimiters
const std::string COMMA = ",";
const std::string SEMICOLON = ";";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";

// Keywords
const std::string FUNCTION = "FUNCTION";
const std::string LET = "LET";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";
const std::string IF = "IF";
const std::string ELSE = "ELSE";
const std::string RETURN = "RETURN";

// Others
const std::string EOf = "EOF";
const std::string INT = "INT";
const std::string IDENT = "IDENT";
const std::string ILLEGAL = "ILLEGAL";

using TokenType = std::string;

struct Token
{
    std::string text;
    TokenType type;

    Token() : text(), type() {}
    Token(std::string text, TokenType type) : text(text), type(type) {}
};

std::map<std::string, TokenType> keywords = {
    {"if", IF},
    {"let", LET},
    {"else", ELSE},
    {"true", TRUE},
    {"false", FALSE},
    {"fn", FUNCTION},
    {"return", RETURN},
};

class Lexer {
public:
    char curChar;       // Current character in the string.
    int curPos = -1;    // Current position in the string.
    std::string source; // Source code to lex as a string.

    Lexer(const std::string &source) : source(source) {
        nextChar();
    };

    // Process the next character.
    void nextChar() {
        curPos += 1;

        if (curPos >= source.length()) {
            curChar = '\0'; // EOF
        }
        else {
            curChar = source[curPos];
        }
    };

    // Return the future character.
    char peek() {
        if (curPos + 1 >= source.length()) {
            return '\0';
        }

        return source[curPos + 1];
    }

    // Skip whitespace
    void skipWhitespace() {
        while (curChar == ' ' || curChar == '\t' || curChar == '\n' || curChar == '\r') {
            nextChar();
        }
    }

    // Return the next token
    Token nextToken()
    {
        Token token;
        skipWhitespace();

        // Operators
        if (curChar == '+') {
            token = Token("+", PLUS);
        } else if (curChar == '-') {
            token = Token("-", MINUS);
        } else if (curChar == '*') {
            token = Token("*", ASTERISK);
        } else if (curChar == '/') {
            token = Token("/", SLASH);
        } else if (curChar == '<') {
            token = Token("<", LT);
        } else if (curChar == '>') {
            token = Token(">", GT);
        }

        else if (curChar == '=') {
            // Checking whether this token is = or ==
            if (peek() == '=') {
                nextChar();
                token = Token("==", EQ);
            } else {
                token = Token("=", ASSIGN);
            }
        }

        else if (curChar == '!') {
            // Checking whether this token is ! or !=
            if (peek() == '=') {
                nextChar();
                token = Token("!=", NOT_EQ);
            } else {
                token = Token("!", BANG);
            }
        }

        // Delimiters
        else if (curChar == ',') {
            token = Token(",", COMMA);
        } else if (curChar == ';') {
            token = Token(";", SEMICOLON);
        } else if (curChar == '(') {
            token = Token("(", LPAREN);
        } else if (curChar == ')') {
            token = Token(")", RPAREN);
        } else if (curChar == '{') {
            token = Token("{", LBRACE);
        } else if (curChar == '}') {
            token = Token("}", RBRACE);
        } else if (curChar == '\0') {
            token = Token("", EOf);
        }

        // Alphabets
        else if (isalpha(curChar)) {
            std::string tokenText = gatherText();

            // Keyword
            if (keywords.find(tokenText) != keywords.end()) {
                token = Token(tokenText, keywords[tokenText]);
            } else { // Identifier
                token = Token(tokenText, IDENT);
            }
        }

        // Digits
        else if (isdigit(curChar)) {
            token = Token(gatherNumber(), INT);
        }

        // Illegal
        else {
            token = Token(std::string(1, curChar), ILLEGAL);
        };

        nextChar();
        return token;
    }


    // Gather the text for identifier or keyword
    std::string gatherText() {
        int startPosition = curPos;

        while (isalnum(peek())) {
            nextChar();
        }

        return source.substr(startPosition, curPos - startPosition + 1); // Get the substring.
    }

    // Gather the number
    std::string gatherNumber() {
        int startPosition = curPos;

        while (isdigit(peek())) {
            nextChar();
        }

        return source.substr(startPosition, curPos - startPosition + 1); // Get the substring.
    }
};

#endif