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
	paul@horus:~/git/satisfiability$ ./satisfy
	> w & ~w
	w
	=
	F: false
	T: false
	Formula is not satisfiable
	paul@horus:~/git/satisfiability$ ./satisfy
	> x & y z
	Error: extraneous input / missing operator
	: x & y z
	:       ^
	paul@horus:~/git/satisfiability$ ./satisfy
	> i | j &
	Error: missing factor
	: i | j &
	:        ^
	paul@horus:~/git/satisfiability$ ./satisfy
	> &s
	Error: missing factor
	: &s
	: ^
	paul@horus:~/git/satisfiability$ 

Single letters only may be used as variable names.

This program is an exercise in expression evaluation generally, and the
construction of parse trees specifically.
