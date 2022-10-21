Introduction
The x mononomium is the expression of the form ax^n, the product of the factor a and the nth power of x. The n-value, called the monomial degree, is a non-negative integer. A single monomome with a coefficient of 0 is a zero monomome.

The polynomial of the variable x is the sum of the individual names of the variable x. A polynomial whose monomes are all zero is a zero polynomial.

The degree of a non-zero polynomial is the maximum degree of its non-zero uniomial. We assume that the degree of the zero polynomial is -1.

The operations of sum and product are defined on polynomials.

Command
Implement a calculator that counts the sum and product of polynomials with integer coefficients.

The computer has a memory, called a battery, which stores a polynomial. The initial value of the battery is zero polynomial.

The computer executes commands to calculate the sum and product of the battery value and the polynomial, which is the argument of the command. The command writes the calculated result to the output and stores it in the battery.

Form of data
The program data is a series of command lines that end with a line that begins with a period. Each command occupies one line.

The command line for calculating the sum starts with the + sign and the command line for calculating the product starts with the * sign. Subsequent characters, until the end of the line, are the notation of the command argument.

We describe the syntax of polynomial notation with a grammar, with the initial symbol <polynomial>, in extended BNF notation:

<multinomial> ::= "0" | [ "-" ] <one-nomian> { <operation> <one-nomian> }
<operation> ::= "+" | "-"
<one-nominal> ::= "1" | <large> | [ <large> ] "x" [ "^" <large> ]
<large> ::= "1" <digit> { <digit> } | <figure 2 to 9> { <figure> }
<digit> ::= "0" | "1" | <figure 2 to 9>
<digit from 2 to 9> ::= "2" | "3" | "4" | "5" | "6" | "7" | "8" | “9”
Curly brackets represent zero or more repetitions, square brackets enclose optional parts and vertical brackets are an alternative. The help symbols are placed in square brackets and the end symbols are placed in quotation marks. In the polynomial, the ending character corresponds to a character between the quotation marks.

In addition, polynomials are arranged in descending order.

Any number of spaces can be present at the command prompt. However, a non-empty string of spaces does not occur either at the beginning of a line or directly between two digits.

Form of the result
For each command executed, the program writes one line to the output with its result. The syntax for writing the polynomial in the program result is the same as in the data. Before and after the occurrence of the final symbol "+" or "-", in the productions of the auxiliary symbol <operation>, there is one space each. Other than that, no other spaces in the program result.
