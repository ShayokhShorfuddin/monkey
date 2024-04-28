#include "lex.cpp"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

// Test for nextToken()
void testNextToken() {
    std::string source = R"(
        let five = 5;
        let ten = 10;
        let add = fn(x, y) {x + y;};
        let result = add(five, ten);

        !-/*5;
        5 < 10 > 5;
        
        if (5 < 10) {
            return true;
        } else {
            return false;
        }

        10 == 10;
        10 != 9;
    )";

    std::vector<std::pair<std::string, TokenType>> generatedTokens;
    std::pair<std::string, TokenType> tests[] = {
        {"let", LET},
        {"five", IDENT},
        {"=", ASSIGN},
        {"5", INT},
        {";", SEMICOLON},
        {"let", LET},
        {"ten", IDENT},
        {"=", ASSIGN},
        {"10", INT},
        {";", SEMICOLON},
        {"let", LET},
        {"add", IDENT},
        {"=", ASSIGN},
        {"fn", FUNCTION},
        {"(", LPAREN},
        {"x", IDENT},
        {",", COMMA},
        {"y", IDENT},
        {")", RPAREN},
        {"{", LBRACE},
        {"x", IDENT},
        {"+", PLUS},
        {"y", IDENT},
        {";", SEMICOLON},
        {"}", RBRACE},
        {";", SEMICOLON},
        {"let", LET},
        {"result", IDENT},
        {"=", ASSIGN},
        {"add", IDENT},
        {"(", LPAREN},
        {"five", IDENT},
        {",", COMMA},
        {"ten", IDENT},
        {")", RPAREN},
        {";", SEMICOLON},

        {"!", BANG},
		{"-", MINUS},
		{"/", SLASH},
		{"*", ASTERISK},
		{"5", INT},
		{";", SEMICOLON},
		{"5", INT},
		{"<", LT},
		{"10", INT},
		{">", GT},
		{"5", INT},
        {";", SEMICOLON},

        {"if", IF},
        {"(", LPAREN},
		{"5", INT},
		{"<", LT},
		{"10", INT},
		{")", RPAREN},
		{"{", LBRACE},
		{"return", RETURN},
		{"true", TRUE},
		{";", SEMICOLON},
		{"}", RBRACE},
		{"else", ELSE},
		{"{", LBRACE},
		{"return", RETURN},
		{"false", FALSE},
		{";", SEMICOLON},
        {"}", RBRACE},
        
        {"10", INT},
		{"==", EQ},
		{"10", INT},
		{";", SEMICOLON},
		{"10", INT},
		{"!=", NOT_EQ},
		{"9", INT},
		{";", SEMICOLON},
		
        {"", EOf}
    };

    Lexer lexer(source);
    Token token = lexer.nextToken();
    generatedTokens.push_back({token.text, token.type});

    // Gathering the tokens
    while (token.type != EOf) {
        token = lexer.nextToken();
        generatedTokens.push_back({token.text, token.type});
    }
    
    // Testing if expected amount of tokens were generated
    const int numberOfTests = sizeof(tests) / sizeof(tests[0]);
    const int generatedTokensLength = generatedTokens.size();

    if (numberOfTests != generatedTokensLength) {
        std::cout << "numberOfTests != generatedTokensLength" << std::endl;
        std::cout << "numberOfTests: " << numberOfTests << std::endl;
        std::cout << "generatedTokensLength: " << generatedTokensLength << std::endl;
    }


    // Iterating over the tokens to verify it's contents
    for (int i = 0; i < numberOfTests; i++) {

        // Verifying token text
        if (generatedTokens[i].first != tests[i].first) {
            std::cout << "tests[" << i << "] - Text wrong. Expected = " << tests[i].first << ", got = " << generatedTokens[i].first << std::endl;
        }

        // Verifying token type
        if (generatedTokens[i].second != tests[i].second) {
            std::cout << "tests[" << i << "] - TokenType wrong. Expected = " << tests[i].second << ", got = " << generatedTokens[i].second << std::endl;
        }
    }
}

int main() {
    testNextToken();
    std::cout << "Testing Complete\n";
    return 0;
}
