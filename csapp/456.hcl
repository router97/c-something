# FORWARD

## Taken		M_Cnd && M_valE > M_valA		<- ERROR
## Not taken	!M_Cnd && M_valE > M_valA		<- PREDICTED

# BACKWARD

## Taken		M_Cnd && M_valE < M_valA		<- PREDICTED
## Not taken	!M_Cnd && M_valE < M_valA		<- ERROR

################ Fetch Stage     ###################################

## What address should instruction be fetched at
word f_pc = [
	M_icode == IJXX && M_ifun != UNCOND && M_Cnd && M_valE > M_valA: M_valE;
	M_icode == IJXX && M_ifun != UNCOND && !M_Cnd && M_valE < M_valA: M_valA;
	# Completion of RET instruction
	W_icode == IRET : W_valM;
	# Default: Use predicted value of PC
	1 : F_predPC;
];

# Predict next value of PC
word f_predPC = [
	# BBTFNT: This is where you'll change the branch prediction rule
	(f_icode == IJXX && f_ifun == UNCOND) || f_icode == ICALL  : f_valC;
	f_icode == IJXX && f_valC < f_valP: f_valC;
	1 : f_valP;
];

################ Execute Stage #####################################

# BBTFNT: When some branches are predicted as not-taken, you need some
# way to get valC into pipeline register M, so that
# you can correct for a mispredicted branch.

## Select input A to ALU
word aluA = [
	E_icode in { IRRMOVQ, IOPQ } : E_valA;
	E_icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ } : E_valC;
	E_icode in { ICALL, IPUSHQ } : -8;
	E_icode in { IRET, IPOPQ } : 8;
	E_icode in { IJXX } : E_valC;
	# Other instructions don't need ALU
];

## Select input B to ALU
word aluB = [
	E_icode in { IRMMOVQ, IMRMOVQ, IOPQ, ICALL, 
		     IPUSHQ, IRET, IPOPQ } : E_valB;
	E_icode in { IRRMOVQ, IIRMOVQ } : 0;
	E_icode in { IJXX } : 0;
	# Other instructions don't need ALU
];

################ Pipeline Register Control #########################

# FORWARD

## Taken		M_Cnd && M_valE > M_valA		<- ERROR
## Not taken	!M_Cnd && M_valE > M_valA		<- PREDICTED

# BACKWARD

## Taken		M_Cnd && M_valE < M_valA		<- PREDICTED
## Not taken	!M_Cnd && M_valE < M_valA		<- ERROR

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && E_ifun != UNCOND && e_Cnd && E_valC > E_valA ||
	E_icode == IJXX && E_ifun != UNCOND && !e_Cnd && E_valC < E_valA) ||
	# BBTFNT: This condition will change
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVQ, IPOPQ } && E_dstM in { d_srcA, d_srcB }) &&
	  IRET in { D_icode, E_icode, M_icode };

bool E_stall = 0;
bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && E_ifun != UNCOND && e_Cnd && E_valC > E_valA ||
	E_icode == IJXX && E_ifun != UNCOND && !e_Cnd && E_valC < E_valA) ||
	# BBTFNT: This condition will change
	# Conditions for a load/use hazard
	E_icode in { IMRMOVQ, IPOPQ } &&
	 E_dstM in { d_srcA, d_srcB};
