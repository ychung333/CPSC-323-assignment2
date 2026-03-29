# CPSC-323-assignment2

Step 2 — Connect Your Lexer
Use your lexer() from Assignment 1
Make sure it returns:
Token
Lexeme
👉 Test:
Print tokens to confirm it works

Step 3 — Build the Parser
Choose ONE:
Recursive Descent Parser (recommended 👍)
Predictive parser (table-driven)
👉 For each grammar rule:
Write a function

Step 4 — Print Output 
For each token:
Print:
Token
Lexeme
Then print:
Production rules used
👉 Easy method:
Add print at start of each function
👉 Add a switch (boolean):
Turn printing ON/OFF

Step 5 — Error Handling
Your parser must:
Detect syntax errors
When error happens, print:
Token
Lexeme
Line number
Error message (like "Expected identifier")
👉 Behavior:
Either:
Stop program ❌
OR continue parsing ✅ 

Step 6 — Full Program Test
Test with valid input
Make sure:
Entire program parses correctly
Output format matches example
Step 7 — Output File
Save result to file:
