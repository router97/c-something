################ Execute Stage #####################################

## Generate valA in execute stage
## LB: With load forwarding, want to insert valM 
##   from memory stage when appropriate
## Here it is set to the default used in the normal pipeline
word e_valA = [
	(E_srcA == M_dstM) && (E_icode in { IRMMOVQ, IPUSHQ }): m_valM;
	1 : E_valA;  # Use valA from stage pipe register
];

################ Pipeline Register Control #########################

# Should I stall or inject a bubble into Pipeline Register F?
# At most one of these can be true.
bool F_bubble = 0;
bool F_stall =
	# Conditions for a load/use hazard
	## Set this to the new load/use condition
	(
	(E_icode in { IMRMOVQ, IPOPQ } && E_dstM in { d_srcA, d_srcB }) &&
	!(E_dstM == d_srcA && D_icode in { IRMMOVQ, IPUSHQ })
	)
	||
	# Stalling at fetch while ret passes through pipeline
	IRET in { D_icode, E_icode, M_icode };

# Should I stall or inject a bubble into Pipeline Register D?
# At most one of these can be true.
bool D_stall = 
	# Conditions for a load/use hazard
	## Set this to the new load/use condition
	(
	(E_icode in { IMRMOVQ, IPOPQ } && E_dstM in { d_srcA, d_srcB }) &&
	!(E_dstM == d_srcA && D_icode in { IRMMOVQ, IPUSHQ })
	); 

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(
	(E_icode in { IMRMOVQ, IPOPQ } && E_dstM in { d_srcA, d_srcB }) &&
	!(E_dstM == d_srcA && D_icode in { IRMMOVQ, IPUSHQ })
	) &&
	  IRET in { D_icode, E_icode, M_icode };

# Should I stall or inject a bubble into Pipeline Register E?
# At most one of these can be true.
bool E_stall = 0;
bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Conditions for a load/use hazard
	## Set this to the new load/use condition
	(
	(E_icode in { IMRMOVQ, IPOPQ } && E_dstM in { d_srcA, d_srcB }) &&
	!(E_dstM == d_srcA && D_icode in { IRMMOVQ, IPUSHQ })
	);
