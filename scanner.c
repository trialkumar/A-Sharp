#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct{
    const char* start;
    const char* current;
    int line;
}Scanner;

Scanner scanner;

void initScanner(const char* source){
    scanner.start = source;
    scanner.current = source;
    scanner.line =1;
}

static bool isAtEnd(){
    return *scanner.current == '\0';
}

static char advance(){
    scanner.current++;
    return scanner.current[-1];
}

static char peek (){
    return *scanner.current;
}

static char peekNext(){
    if(isAtEnd) return '\0';
    return scanner.current[1];
}

static Token makeToken(TokenType type){
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

// Create an error token to tell the compiler something went wrong
static Token errorToken(const char* message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;
  return token;
}

//skip the whitespaces and comments
static void skipWhitespace(){
    for(;;){
        char c= peek();
        switch (c){
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            case '/':
                if(peekNext() == '/'){
                    while(peek()!='\n'&& !isAtEnd()) advance();
                } else{
                    return;
                }
                break;
            default:
                return;

        }
    }
}

static Token number(){
    while(peek() >= '0' && peek()<='9') advance();

    if (peek() == '.' && (peekNext() >= '0' && peekNext() <= '9')){
        advance();
        while(peek() >= '0' && peek() <= '9') advance();
    }
    return makeToken(TOKEN_NUMBER);
}

//The Main Scan Function

Token scanToken(){
    skipWhitespace();
    scanner.start = scanner.current;

    if(isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    //Check for Numbers;
    if(c>= '0' && c<='9') return number();

    switch(c){
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case '-': return makeToken(TOKEN_MINUS);
        case '+': return makeToken(TOKEN_PLUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);
    }
    return errorToken("Unexpected Character.");
}