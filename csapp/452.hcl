################ Fetch Stage     ###################################

bool instr_valid = icode in 
	{ INOP, IHALT, IRRMOVQ, IIRMOVQ, IRMMOVQ, IMRMOVQ,
	       IOPQ, IIADDQ, IJXX, ICALL, IRET, IPUSHQ, IPOPQ };
CHANGE 1: added IIADDQ as a valid icode

# Does fetched instruction require a regid byte?
bool need_regids =
	icode in { IRRMOVQ, IOPQ, IIADDQ, IPUSHQ, IPOPQ, 
		     IIRMOVQ, IRMMOVQ, IMRMOVQ };
CHANGE 2: IADDQ needs regids

# Does fetched instruction require a constant word?
bool need_valC =
	icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ, IIADDQ, IJXX, ICALL };
CHANGE 3: IADDQ needs constant

################ Decode Stage    ###################################

## What register should be used as the B source?
word srcB = [
	icode in { IOPQ, IIADDQ, IRMMOVQ, IMRMOVQ  } : rB;
	icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
	1 : RNONE;  # Don't need register
];
CHANGE 4: IADDQ needs rB register

## What register should be used as the E destination?
word dstE = [
	icode in { IRRMOVQ } && Cnd : rB;
	icode in { IIRMOVQ, IOPQ, IIADDQ} : rB;
	icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
	1 : RNONE;  # Don't write any register
];
CHANGE 5: IADDQ writes back to rB

################ Execute Stage   ###################################

## Select input A to ALU
word aluA = [
	icode in { IRRMOVQ, IOPQ } : valA;
	icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ, IIADDQ } : valC;
	icode in { ICALL, IPUSHQ } : -8;
	icode in { IRET, IPOPQ } : 8;
	# Other instructions don't need ALU
];
CHANGE 6: IADDQ needs valC in the ALU

## Select input B to ALU
word aluB = [
	icode in { IRMMOVQ, IMRMOVQ, IOPQ, IIADDQ, ICALL, 
		      IPUSHQ, IRET, IPOPQ } : valB;
	icode in { IRRMOVQ, IIRMOVQ } : 0;
	# Other instructions don't need ALU
];
CHANGE 7: IADDQ needs aluB in the ALU

## Should the condition codes be updated?
bool set_cc = icode in { IOPQ, IIADDQ };
CHANGE 8: IADDQ sets CC
