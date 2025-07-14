#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isalpha, isdigit, isalnum, isspace

// --- Token Types ---
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_UNKNOWN // For characters not recognized
} TokenType;

// --- Token Structure ---
typedef struct {
    TokenType type;
    char *lexeme; // The actual string value of the token
    int line;
    int column;
} Token;

// --- Global Lexer State ---
static char *input_buffer; // The source code string
static int current_pos = 0; // Current reading position in the buffer
static int current_line = 1;
static int current_column = 1;

// --- Function Prototypes ---
void init_lexer(const char *source_code);
void free_lexer();
char peek_char();
char advance_char();
void skip_whitespace();
Token *get_next_token();
void free_token(Token *token);
void print_token(const Token *token);

// --- Keyword Lookup Table ---
// A simple way to check if an identifier is actually a keyword
typedef struct {
    const char *name;
    TokenType type;
} Keyword;

static Keyword keywords[] = {
    {"int", TOKEN_KEYWORD_INT},
    {"if", TOKEN_KEYWORD_IF},
    {"else", TOKEN_KEYWORD_ELSE},
    {NULL, TOKEN_UNKNOWN} // Sentinel
};

// --- Lexer Initialization ---
void init_lexer(const char *source_code) {
    if (source_code == NULL) {
        fprintf(stderr, "Error: Source code cannot be NULL.\n");
        exit(EXIT_FAILURE);
    }
    // Duplicate the string to have a mutable buffer
    input_buffer = strdup(source_code);
    if (input_buffer == NULL) {
        perror("Failed to allocate input buffer");
        exit(EXIT_FAILURE);
    }
    current_pos = 0;
    current_line = 1;
    current_column = 1;
}

// --- Lexer Cleanup ---
void free_lexer() {
    if (input_buffer) {
        free(input_buffer);
        input_buffer = NULL;
    }
}

// --- Peek at the next character without advancing ---
char peek_char() {
    if (input_buffer[current_pos] == '\0') {
        return '\0'; // EOF
    }
    return input_buffer[current_pos];
}

// --- Advance to the next character and return the current one ---
char advance_char() {
    char c = peek_char();
    if (c != '\0') {
        current_pos++;
        if (c == '\n') {
            current_line++;
            current_column = 1;
        } else {
            current_column++;
        }
    }
    return c;
}

// --- Skip whitespace characters ---
void skip_whitespace() {
    while (isspace(peek_char())) {
        advance_char();
    }
}

// --- Create a new Token structure ---
Token *create_token(TokenType type, const char *lexeme, int line, int column) {
    Token *token = (Token *)malloc(sizeof(Token));
    if (token == NULL) {
        perror("Failed to allocate token");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->lexeme = strdup(lexeme); // Duplicate lexeme string
    if (token->lexeme == NULL) {
        perror("Failed to duplicate lexeme");
        free(token);
        exit(EXIT_FAILURE);
    }
    token->line = line;
    token->column = column;
    return token;
}

// --- Free a Token structure ---
void free_token(Token *token) {
    if (token) {
        if (token->lexeme) {
            free(token->lexeme);
        }
        free(token);
    }
}

// --- Get the next token from the input stream ---
Token *get_next_token() {
    skip_whitespace(); // Always skip whitespace before trying to find a token

    char c = peek_char();
    int start_pos = current_pos;
    int token_line = current_line;
    int token_column = current_column;

    // End of File
    if (c == '\0') {
        return create_token(TOKEN_EOF, "EOF", token_line, token_column);
    }

    // Numbers
    if (isdigit(c)) {
        while (isdigit(peek_char())) {
            advance_char();
        }
        // Extract the lexeme
        int length = current_pos - start_pos;
        char *lexeme = (char *)malloc(length + 1);
        if (lexeme == NULL) {
            perror("Failed to allocate lexeme for number");
            exit(EXIT_FAILURE);
        }
        strncpy(lexeme, input_buffer + start_pos, length);
        lexeme[length] = '\0';
        return create_token(TOKEN_NUMBER, lexeme, token_line, token_column);
    }

    // Identifiers and Keywords
    if (isalpha(c) || c == '_') {
        while (isalnum(peek_char()) || peek_char() == '_') {
            advance_char();
        }
        // Extract the lexeme
        int length = current_pos - start_pos;
        char *lexeme = (char *)malloc(length + 1);
        if (lexeme == NULL) {
            perror("Failed to allocate lexeme for identifier");
            exit(EXIT_FAILURE);
        }
        strncpy(lexeme, input_buffer + start_pos, length);
        lexeme[length] = '\0';

        // Check if it's a keyword
        for (int i = 0; keywords[i].name != NULL; i++) {
            if (strcmp(lexeme, keywords[i].name) == 0) {
                Token *token = create_token(keywords[i].type, lexeme, token_line, token_column);
                free(lexeme); // Free the temporary lexeme as it's duplicated in create_token
                return token;
            }
        }
        // If not a keyword, it's an identifier
        return create_token(TOKEN_IDENTIFIER, lexeme, token_line, token_column);
    }

    // Operators
    switch (c) {
        case '+': advance_char(); return create_token(TOKEN_PLUS, "+", token_line, token_column);
        case '-': advance_char(); return create_token(TOKEN_MINUS, "-", token_line, token_column);
        case '*': advance_char(); return create_token(TOKEN_MULTIPLY, "*", token_line, token_column);
        case '/': advance_char(); return create_token(TOKEN_DIVIDE, "/", token_line, token_column);
        case '=': advance_char(); return create_token(TOKEN_ASSIGN, "=", token_line, token_column);
        default:
            // Handle unknown characters
            advance_char(); // Consume the unknown character
            char unknown_lexeme[2];
            unknown_lexeme[0] = c;
            unknown_lexeme[1] = '\0';
            fprintf(stderr, "Lexical Error: Unknown character '%c' at line %d, column %d\n",
                    c, token_line, token_column);
            return create_token(TOKEN_UNKNOWN, unknown_lexeme, token_line, token_column);
    }
}

// --- Helper to print token details ---
void print_token(const Token *token) {
    if (!token) return;

    printf("Token: [Type: ");
    switch (token->type) {
        case TOKEN_EOF: printf("EOF"); break;
        case TOKEN_NUMBER: printf("NUMBER"); break;
        case TOKEN_IDENTIFIER: printf("IDENTIFIER"); break;
        case TOKEN_PLUS: printf("PLUS"); break;
        case TOKEN_MINUS: printf("MINUS"); break;
        case TOKEN_MULTIPLY: printf("MULTIPLY"); break;
        case TOKEN_DIVIDE: printf("DIVIDE"); break;
        case TOKEN_ASSIGN: printf("ASSIGN"); break;
        case TOKEN_KEYWORD_INT: printf("KEYWORD_INT"); break;
        case TOKEN_KEYWORD_IF: printf("KEYWORD_IF"); break;
        case TOKEN_KEYWORD_ELSE: printf("KEYWORD_ELSE"); break;
        case TOKEN_UNKNOWN: printf("UNKNOWN"); break;
        default: printf("UNKNOWN_TYPE"); break;
    }
    printf(", Lexeme: \"%s\"", token->lexeme);
    printf(", Line: %d, Column: %d]\n", token->line, token->column);
}

// --- Main function for testing the lexer ---
int main() {
    const char *source_code =
        "int myVar = 10 + 5;\n"
        "if (myVar > 10) {\n"
        "  else x = 20;\n"
        "}\n"
        "another_var = 1 * 2 / 3;\n"
        "// This is a comment, lexer ignores it for now\n"
        "int _test = 100;\n"
        "invalid@char"; // Example of an invalid character

    printf("Lexing the following source code:\n---\n%s\n---\n\n", source_code);

    init_lexer(source_code);

    Token *token;
    do {
        token = get_next_token();
        print_token(token);
        // In a real compiler, you'd pass this token to the parser
        free_token(token); // Free token after use to prevent memory leaks
    } while (token->type != TOKEN_EOF); // Loop until EOF token is found

    free_lexer(); // Clean up lexer resources

    return 0;
}
