#include "parser.h"

// =======================
// Constructor Functions
// =======================
Parser::Parser(Lexer& lex, ofstream& outFile, bool print)
    : lexer(lex), fout(outFile), printRules(print)
{
    currentToken = lexer.nextToken();

    if (currentToken.type != "EOF")
    {
        fout << "Token: " << currentToken.type
             << "          Lexeme: " << currentToken.lexeme << endl;
    }
}


// =======================
// Helper Functions
// =======================

void Parser::advance()
{
    currentToken = lexer.nextToken();

    if (currentToken.type != "EOF")
    {
        fout << "Token: " << currentToken.type
             << "          Lexeme: " << currentToken.lexeme << endl;
    }
}

void Parser::error(const string& message)
{
    fout << "Syntax Error: " << message
         << " | Found token: " << currentToken.type
         << " | Lexeme: " << currentToken.lexeme << endl;
}

void Parser::match(const string& expectedLexeme)
{
    if (currentToken.lexeme == expectedLexeme)
    {
        advance();
    }
    else
    {
        error("Expected lexeme '" + expectedLexeme + "'");
    }
}

void Parser::matchType(const string& expectedType)
{
    if (currentToken.type == expectedType)
    {
        advance();
    }
    else
    {
        error("Expected token type '" + expectedType + "'");
    }
}

void Parser::printProduction(const string& rule)
{
    if (printRules)
    {
        fout << rule << endl;
    }
}


// =======================
// Grammar Functions
// =======================

void Parser::parse()
{
    Rat26S();
}

void Parser::Rat26S()
{
    printProduction("<Rat26S> -> @ <Opt Function Definitions> @ <Opt Declaration List> @ <Statement List> @");

    match("@");
    OptFunctionDefinitions();

    match("@");
    OptDeclarationList();

    match("@");
    StatementList();

    match("@");
}

void Parser::OptFunctionDefinitions() {}
void Parser::FunctionDefinitions() {}
void Parser::Function() {}
void Parser::OptParameterList() {}
void Parser::ParameterList() {}
void Parser::Parameter() {}
void Parser::Qualifier() {}
void Parser::Body() {}
void Parser::OptDeclarationList() {}
void Parser::DeclarationList() {}
void Parser::Declaration() {}
void Parser::IDs() {}
void Parser::StatementList() {}
void Parser::Statement() {}
void Parser::Compound() {}
void Parser::Assign() {}
void Parser::If() {}
void Parser::Return() {}
void Parser::Print() {}
void Parser::Scan() {}
void Parser::While() {}
void Parser::Condition() {}
void Parser::Relop() {}
void Parser::Expression() {}
void Parser::ExpressionPrime() {}
void Parser::Term() {}
void Parser::TermPrime() {}
void Parser::Factor() {}
void Parser::Primary() {}
void Parser::Empty() {}
