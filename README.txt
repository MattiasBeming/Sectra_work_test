### Simple Calculator ###
This task was given to me during an interview process to assess my overall 
competence-level in programming.

The command I used to compile the code is:
g++ -std=c++17 -pedantic -Wall -Wextra .\Calculator.cpp .\Expression.cpp -o Calculator


## Interpretations and Assumptions ##

My interpretation of the task is that the Calculator should be able to handle 
ordinary operations such as addition, subtraction and multiplication, but also
evaluation at print with lazy evaluation where a register itself is the value. 
Therefore I implemented tokens which stores a register-name and all operations
that are specified to that register-name.  

The Calculator stores all tokens, where every token is a value or has a list 
of operations to perform. Each operation can include another token which has it's 
own set of operations to perform. This gives tokens a recursive behaviour 
at evaluation, where chains of references are possible. 
An example could look like this:
A add B 
B add C
C add D 
D add 3

Where: print A
would give the output: 3

The solution is given by iterating over each operation A has stored and evaluating 
the result recursively. 
Note that this implementation does not handle cases where a register references 
itself somewhere in the chain of operations, for example:
A add B
B add A
or 
A add A

These cases were ambiguous in the specification. 
The recursive nature of this implementation will give infinite recursion in 
such cases. 

If the behaviour of self-referencing is desired, one could implement a history, 
to keep track of self referencing. For example by recursively pass the name of
the register that is being evaluated. And then stop the recursion after the register
encounters itself in the recursion. 



Another assumption is that the Calculator only should be able to handle integers
and not any other any other data type (value types such as integer or floating point). 
If this behaviour is desired, one could quite easily introduce template parameters,
to be able to create a Calculator of a specified type. 
For example:
Calculator<int> calc{};
or
Calculator<double> calc{};

If the Calculator should be able to handle all data-value types at the same time, 
one could create a Calculator<double> and cast all input to double. 

