# Arithmetic Expression Parser in C

A menu-driven Arithmetic Expression Parser developed using C programming. The project validates arithmetic expressions, converts infix expressions into different notations, and generates expression parse trees.

## Features

- Arithmetic expression validation
- Infix to Postfix conversion
- Infix to Prefix conversion
- Inorder, Preorder and Postorder traversals
- Parse tree generation
- Operator precedence and associativity handling
- Multiple expression parsing
- File-based expression processing
- Detailed error messages
- Interactive console menu

## Technologies Used

- Programming Language: C
- Compiler: GCC
- Standard: C99
- Editor: Visual Studio Code

## Supported Operators

| Operator | Operation | Associativity |
|---|---|---|
| + | Addition | Left to Right |
| - | Subtraction | Left to Right |
| * | Multiplication | Left to Right |
| / | Division | Left to Right |
| % | Modulus | Left to Right |
| ^ | Exponentiation | Right to Left |

## Project Structure

```text
ExpressionParser/
│
├── main.c
├── stack.c
├── stack.h
├── converter.c
├── converter.h
├── validator.c
├── validator.h
├── tree.c
├── tree.h
├── tests.txt
├── build.bat
├── .gitignore
├── README.md
│
└── screenshots/
```

## How to Run

### Prerequisites

- GCC Compiler
- Visual Studio Code (optional)

### Step 1: Clone Repository

```bash
git clone YOUR_REPOSITORY_URL
```

### Step 2: Navigate to Project

```bash
cd ExpressionParser
```

### Step 3: Compile

Using the build script on Windows:

```powershell
.\build.bat
```

Alternatively, compile manually:

```bash
gcc -std=c99 -Wall main.c stack.c converter.c validator.c tree.c -o parser.exe
```

### Step 4: Execute

```powershell
.\parser.exe
```

## Application Menu

The application provides the following options:

1. Parse one expression
2. Parse multiple expressions
3. Run expressions from a file
4. Help
0. Exit

## Example

Input:

```text
3 + 4 * 2
```

Postfix:

```text
3 4 2 * +
```

Prefix:

```text
+ 3 * 4 2
```

Parse Tree:

```text
+
|-- 3
`-- *
    |-- 4
    `-- 2
```

## Error Handling

The parser detects several invalid expressions, including:

- Consecutive operators
- Missing operands
- Unmatched parentheses
- Empty parentheses
- Invalid characters
- Missing closing parentheses
- Unsupported negative numbers

## Testing

The project includes a `tests.txt` file containing valid and invalid arithmetic expressions.

The file-processing mode generates a summary containing:

- Total expressions
- Valid expressions
- Invalid expressions

## Limitations

- Unary minus and negative numbers are not supported.
- The application parses expressions but does not evaluate their numerical results.

## Future Enhancements

- Support for unary operators
- Expression evaluation
- Improved error reporting
- Graphical User Interface
- Additional mathematical functions

## Author

Khushi Sehgal

B.Tech – Computer Science and Engineering  
Cybersecurity & Privacy

## License

This project is available for educational and learning purposes.