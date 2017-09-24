satisfiability
==============

This program solves the satisfiability problem of formulae in the propositional
calculus. Sample output:

	paul@horus:~/git/satisfiability$ ./satisfy
	> p & (q | ~r)
	pqr
	===
	FFF: false
	FFT: false
	FTF: false
	FTT: false
	TFF: true
	TFT: false
	TTF: true
	TTT: true
	Formula is satisfiable
	paul@horus:~/git/satisfiability$ 

Sample output with badly formed input:

	paul@horus:~/git/satisfiability$ ./satisfy
	> a & b |
	Error: missing factor
	: a & b |
	:        ^
	paul@horus:~/git/satisfiability$ 

Single letters only may be used as variable names.

This program is an exercise in expression evaluation generally, and the
construction of parse trees specifically.
