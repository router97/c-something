################ Fetch Stage     ###################################

## Determine icode of fetched instruction
## 1W: To split ipopq into two cycles, need to be able to 
## modify value of icode,
## so that it will be IPOP2 when fetched for second time.
word f_icode = [
	imem_error : INOP;
	D_icode == IPOPQ : IPOP2;
	1: imem_icode;
];

# Is instruction valid?
bool instr_valid = f_icode in 
	{ INOP, IHALT, IRRMOVQ, IIRMOVQ, IRMMOVQ, IMRMOVQ,
	  IOPQ, IJXX, ICALL, IRET, IPUSHQ, IPOPQ, IPOP2 };

# Does fetched instruction require a regid byte?
bool need_regids =
	f_icode in { IRRMOVQ, IOPQ, IPUSHQ, IPOPQ, IPOP2
		     IIRMOVQ, IRMMOVQ, IMRMOVQ };

# Predict next value of PC
word f_predPC = [
	f_icode in { IJXX, ICALL } : f_valC;
	## 1W: Want to refetch popq one time
	f_icode == IPOPQ : f_pc;
	1 : f_valP;
];

################ Decode Stage ######################################

## W1: Strategy.  Decoding of popq rA should be treated the same
## as would iaddq $8, %rsp
## Decoding of pop2 rA treated same as mrmovq -8(%rsp), rA

## What register should be used as the A source?
word d_srcA = [
	D_icode in { IRRMOVQ, IRMMOVQ, IOPQ, IPUSHQ  } : D_rA;
	D_icode in { IRET } : RRSP;
	1 : RNONE; # Don't need register
];

## What register should be used as the B source?
word d_srcB = [
	D_icode in { IOPQ, IRMMOVQ, IMRMOVQ  } : D_rB;
	D_icode in { IPUSHQ, IPOPQ, ICALL, IRET, IPOP2 } : RRSP;
	1 : RNONE;  # Don't need register
];

## What register should be used as the M destination?
word d_dstM = [
	D_icode in { IMRMOVQ, IPOP2 } : D_rA;
	1 : RNONE;  # Don't write any register
];

################ Execute Stage #####################################

## W1: Strategy.  Decoding of popq rA should be treated the same
## as would iaddq $8, %rsp
## Decoding of pop2 rA treated same as mrmovq -8(%rsp), rA

## Select input A to ALU
word aluA = [
	E_icode in { IRRMOVQ, IOPQ } : E_valA;
	E_icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ } : E_valC;
	E_icode in { ICALL, IPUSHQ, IPOP2 } : -8;
	E_icode in { IRET, IPOPQ } : 8;
	# Other instructions don't need ALU
];

## Select input B to ALU
word aluB = [
	E_icode in { IRMMOVQ, IMRMOVQ, IOPQ, ICALL, 
		     IPUSHQ, IRET, IPOPQ, IPOP2 } : E_valB;
	E_icode in { IRRMOVQ, IIRMOVQ } : 0;
	# Other instructions don't need ALU
];

################ Memory Stage ######################################

## Select memory address
word mem_addr = [
	M_icode in { IRMMOVQ, IPUSHQ, ICALL, IMRMOVQ, IPOP2 } : M_valE;
	M_icode in { IRET } : M_valA;
	# Other instructions don't need address
];

## Set read control signal
bool mem_read = M_icode in { IMRMOVQ, IRET, IPOP2 };

################ Pipeline Register Control #########################

# Should I stall or inject a bubble into Pipeline Register F?
# At most one of these can be true.
bool F_bubble = 0;
bool F_stall =
	# Conditions for a load/use hazard
	E_icode in { IMRMOVQ, IPOP2 } &&
	 E_dstM in { d_srcA, d_srcB } ||
	# Stalling at fetch while ret passes through pipeline
	IRET in { D_icode, E_icode, M_icode };

# Should I stall or inject a bubble into Pipeline Register D?
# At most one of these can be true.
bool D_stall = 
	# Conditions for a load/use hazard
	E_icode in { IMRMOVQ, IPOP2 } &&
	 E_dstM in { d_srcA, d_srcB };

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVQ, IPOP2 } && E_dstM in { d_srcA, d_srcB }) &&
	# 1W: This condition will change
	  IRET in { D_icode, E_icode, M_icode };

# Should I stall or inject a bubble into Pipeline Register E?
# At most one of these can be true.
bool E_stall = 0;
bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Conditions for a load/use hazard
	E_icode in { IMRMOVQ, IPOP2 } &&
	 E_dstM in { d_srcA, d_srcB};
