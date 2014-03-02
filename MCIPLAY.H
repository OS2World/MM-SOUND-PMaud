/* Header for mciplay.h */

/*
 * Note that ARGC and ARGV work precisely like argc and argv in main()...
 *  in the case of mciplay(), struct _MCIPLAYARGS.ARGV[0] is ignored, and
 *  struct _MCIPLAYARGS.ARGC is expected to be 1 greater than the last
 *  element of _MCIPLAYARGS.ARGV. (Although the array does not have to end
 *  with a NULL value, as main()'s argv does, it might be wise to set it as
 *  such.
 */

typedef struct _MCIPLAYARGS
{
	int ARGC;		/* number of elements in **ARGV */
	char **ARGV;	/* Array of filenames.          */
} MCIPLAYARGS;


/* This function handles the digital audio device and plays the sounds. */
void mciplay(MCIPLAYARGS *micp);

/* end of mciplay.h */

