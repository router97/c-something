################ Fetch Stage     ###################################

## What address should instruction be fetched at
word f_pc = [
	# Mispredicted branch.
	M_icode == IJXX && !M_Cnd && M_ifun != UNCOND : M_valA;				# CHANGE 1
	# Completion of RET instruction
	W_icode == IRET : W_valM;
	# Default: Use predicted value of PC
	1 : F_predPC;
];

# Predict next value of PC
word f_predPC = [
	# BNT: This is where you'll change the branch prediction rule
	(f_icode == IJXX && f_ifun == UNCOND) || f_icode == ICALL : f_valC	# CHANGE 2
	1 : f_valP;
];

################ Execute Stage #####################################

## Generate valA in execute stage
word e_valA = [
	E_icode == IJXX && E_ifun != UNCOND: E_valC 						# CHANGE 3
	1: E_valA
]

################ Pipeline Register Control #########################

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd && E_ifun != UNCOND) ||					# CHANGE 4
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVQ, IPOPQ } && E_dstM in { d_srcA, d_srcB }) &&
	  IRET in { D_icode, E_icode, M_icode };

# Should I stall or inject a bubble into Pipeline Register E?
# At most one of these can be true.
bool E_stall = 0;
bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd && E_ifun != UNCOND) ||					# CHANGE 5
	# Conditions for a load/use hazard
	E_icode in { IMRMOVQ, IPOPQ } &&
	 E_dstM in { d_srcA, d_srcB};
