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

void Parser::OptFunctionDefinitions() {
    if (currentToken.lexeme == "function") {
        FunctionDefinitions();
    } else {
        Empty();
    }
}
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
void Parser::IDs() {
    printProduction("<IDs> -> identifier <More IDs>");
    matchType("identifier");
    while (currentToken.lexeme == ",") {
        match(",");
        matchType("identifier");
    }
}
void Parser::StatementList() {
    printProduction("<Statement List> -> <Statement> <Statement List> | <Empty>");
    while (currentToken.lexeme != "@" && currentToken.lexeme != "}") {
        Statement();
    }
}
void Parser::Statement() {
    printProduction("<Statement> -> <Assign> | <If> | <While> | <Return> | <Scan> | <Compound>");
    if (currentToken.lexeme == "{") {
        Compound();
    } else if (currentToken.type == "identifier") {
        Assign();
    } else if (currentToken.lexeme == "if") {
        If();
    } else if (currentToken.lexeme == "while") {
        While();
    } else if (currentToken.lexeme == "return") {
        Return();
    } else if (currentToken.lexeme == "write") {
        Print();
    } else if (currentToken.lexeme == "read") {
        Scan();
    } else {
        Empty();
    }
}
void Parser::Compound() {
    printProduction("<Compound> -> { <Statement List> }");
    match("{");
    StatementList();
    match("}");
}
void Parser::Assign()
{
    printProduction("<Assign> -> <Identifier> = <Expression> ;");
    matchType("identifier");
    match("=");

    Expression();
    match(";");
}
void Parser::If() {
    printProduction("<If> -> if ( <Condition> ) <Statement> <Else Part>");
    match("if");
    match("(");
    Condition();
    match(")");
    Statement();

    if (currentToken.lexeme == "otherwise") {
        match("otherwise");
        Statement();
    }
}
void Parser::Return() {
    printProduction("<Return> -> return <Expression> ;");
    match("return");
    Expression();
    match(";");
}
void Parser::Print() {
    printProduction("<Print> -> write ( <Expression> ) ;");
    match("write");
    match("(");
    Expression();
    match(")");
    match(";");
}
void Parser::Scan() {
    printProduction("<Scan> -> read ( <IDs> ) ;");
    match("read");
    match("(");
    IDs();
    match(")");
    match(";");
}
void Parser::While() {
    printProduction("<While> -> while ( <Condition> ) <Statement>");
    match("while");
    match("(");
    Condition();
    match(")");
    Statement();
}
void Parser::Condition() {
    printProduction("<Condition> -> <Expression> <Relop> <Expression>");
    Expression();
    Relop();
    Expression();
}
void Parser::Relop() {
    printProduction("<Relop> -> == | != | > | < | >= | <=");
    if (currentToken.lexeme == "==" || currentToken.lexeme == "!=" ||
        currentToken.lexeme == ">" || currentToken.lexeme == "<" ||
        currentToken.lexeme == ">=" || currentToken.lexeme == "<=") {
            advance();
        } else {
            error("Expected relational operator");
        }
}
void Parser::Expression() {
    printProduction("<Expression> -> <Term> <ExpressionPrime>");
    Term();
    ExpressionPrime();
}
void Parser::ExpressionPrime() {
    if (currentToken.lexeme == "+") {
        printProduction("<ExpressionPrime> -> + <Term> <ExpressionPrime>");
        match("+");
        Term();
        ExpressionPrime();
    } else if (currentToken.lexeme == "-") {
        printProduction("<ExpressionPrime> -> - <Term> <ExpressionPrime>");
        match("-");
        Term();
        ExpressionPrime();
    } else {
        printProduction("<ExpressionPrime> -> <Empty>");
        Empty();
    }
}
void Parser::Term() {
    printProduction("<Term> -> <Factor> <TermPrime>");
    Factor();
    TermPrime();
}
void Parser::TermPrime() {
    if (currentToken.lexeme == "*") {
        printProduction("<TermPrime> -> * <Factor> <TermPrime>");
        match("*");
        Factor();
        TermPrime();
    } else if (currentToken.lexeme == "/") {
        printProduction("<TermPrime> -> / <Factor> <TermPrime>");
        match("/");
        Factor();
        TermPrime();
    } else {
        printProduction("<TermPrime> -> <Empty>");
        Empty();
    }
}
void Parser::Factor() {
    printProduction("<Factor> -> <Primary> <FactorPrime>");
    Primary();
    FactorPrime();
}
void Parser::FactorPrime() {
    if (currentToken.lexeme == "^") {
        printProduction("<FactorPrime> -> ^ <Primary> <FactorPrime>");
        match("^");
        Primary();
        FactorPrime();
    } else {
        printProduction("<FactorPrime> -> <Empty>");
        Empty();
    }
}
void Parser::Primary() {
    if (currentToken.lexeme == "(") {
        printProduction("<Primary> -> ( <Expression> )");
        match("(");
        Expression();
        match(")");
    } else if (currentToken.type == "identifier") {
        printProduction("<Primary> -> identifier");
        matchType("identifier");
    } else if (currentToken.type == "number") {
        printProduction("<Primary> -> number");
        matchType("number");
    } else {
        error("Expected primary (identifier, number, or parentheses)");
    }
}
void Parser::Empty() {
    printProduction("<Empty>");
}
