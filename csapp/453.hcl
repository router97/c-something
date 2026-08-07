################ Pipeline Register Control #########################

# Should I stall or inject a bubble into Pipeline Register F?
# At most one of these can be true.
bool F_bubble = 0;

bool F_stall =
	(
	d_srcA != RNONE && d_srcA in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM} ||
	d_srcB != RNONE && d_srcB in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM} ||
	# Stalling at fetch while ret passes through pipeline
	IRET in { D_icode, E_icode, M_icode }
	) && !(E_icode == IJXX && !e_Cnd);


# Should I stall or inject a bubble into Pipeline Register D?
# At most one of these can be true.
bool D_stall = 
	(d_srcA != RNONE && d_srcA in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM} ||
	d_srcB != RNONE && d_srcB in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM}) &&
	!(E_icode == IJXX && !e_Cnd);

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) || (
	!(d_srcA != RNONE && d_srcA in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM} ||
	d_srcB != RNONE && d_srcB in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM}) &&
	  IRET in { D_icode, E_icode, M_icode });


# Should I stall or inject a bubble into Pipeline Register E?
# At most one of these can be true.
bool E_stall = 0;

bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Modify the following to inject bubble into the execute stage
	(d_srcA != RNONE && d_srcA in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM} ||
	d_srcB != RNONE && d_srcB in {e_dstE, E_dstM, M_dstE, M_dstM, W_dstE, W_dstM});


# Should I stall or inject a bubble into Pipeline Register M?
# At most one of these can be true.
bool M_stall = 0;

# Start injecting bubbles as soon as exception passes through memory stage
bool M_bubble = m_stat in { SADR, SINS, SHLT } || W_stat in { SADR, SINS, SHLT };

# Should I stall or inject a bubble into Pipeline Register W?
bool W_stall = W_stat in { SADR, SINS, SHLT };

bool W_bubble = 0;
#/* $end pipe-all-hcl */

F STALLS IF DATA HAZARD, or return is being executed (except if it's a mispredicted branch)
F doesn't bubble
D STALLS IF DATA HAZARD (except if its a mispredicted branch)
D BUBBLE if it's a mispredicted branch, or ret is passing through (except if there's a data hazard)
E doesn't stall
E BUBBLES if it's a mispredicted branch or data hazard
M doesn't stall
M BUBBLES for exceptions
W STALLS for exceptions
W doesn't bubble
