/*
 * audT v1.1
 *
 * Text-version of PMaud. Runs well from a .CMD file.
 *
 *  Feel free to use this code, just drop me an email so I know you are getting
 *   some use out of them. (warped42@ix.netcom.com)
 *
 *   Written by Ryan C. Gordon, 1996.
 */

#include "mciplay.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	MCIPLAYARGS mcip;

	_wildcard(&argc, &argv);

	mcip.ARGC = argc;
	mcip.ARGV = argv;

	mciplay(&mcip);

	return(0);
} /* main */

/* end of audt.c */