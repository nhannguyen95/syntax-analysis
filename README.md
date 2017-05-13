# syntax-analysis
Syntax analysis algorithms

This project implements some Syntax Analysis algorithm:
- Operator-precedence algorithm (testcase: inp1, inp2, inp3)
- Weak operator-precedence algorithm (testcase: inp3, inp4)
- Simple LR / LR0 (testcase: inp5, inp6, inp7)
- Canonical LR / LR1 (testcase: inp8, inp9, inp 10)

Usage:
- Operator-precedence algorithm: 
  + #include "uutientoantu.h"
  + in main() function, call: entryPoint();
- Weak operator-precedence algorithm:
  + #include "thutuyeu.h"
  + in main() function, call: entryPoint();
- Simple LR / LR0:
  + #include "simplelr.h"
  + in main() function, call: entryPoint(string s), s is the first productible character of the grammar.
- Canonical LR / LR1:
  + #include "canonical.h"
  + in main() function, call: entryPoint(string s), s is the first productible character of the grammar.
