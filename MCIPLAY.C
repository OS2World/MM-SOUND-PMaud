/*
 * These routines setup and playback audiofiles.
 *
 *  Written by Ryan C. Gordon, 1996. Feel free to use this code, but please
 *   drop me an email (mailto:warped42@ix.netcom.com), so I can see if these
 *   are doing anyone any good.
 */

#define INCL_OS2MM
#include <os2.h>
#include <os2me.h>
#include "mciplay.h"

void mciplay(MCIPLAYARGS *micp)
/*
 * The mainline. Accepts multiple filenames on the command line, and plays
 *   the files in the specified order.
 *
 *    params : *pmaudargs == argument structure.
 *   returns : errorlevel 0 if successfull, errorlevel 1 otherwise.
 */
{
	MCI_OPEN_PARMS    mop;		/* for MCI_OPEN message.      */
	MCI_PLAY_PARMS    mpp;		/* for MCI_PLAY message.      */
	MCI_GENERIC_PARMS mgp;		/* for MCI_CLOSE message.     */
	int looper;					/* for-loop control variable. */

	for (looper = 1; looper < micp->ARGC ; looper++)
	{
		/* Open audio device (the sound card) */
		mop.hwndCallback = (HWND) NULL;
		mop.usDeviceID = (USHORT) NULL;
		mop.pszDeviceType = (PSZ) NULL;
		mop.pszElementName = (PSZ) micp->ARGV[looper];

		if (mciSendCommand(0,
						   MCI_OPEN,
						   MCI_WAIT | MCI_OPEN_SHAREABLE | MCI_OPEN_ELEMENT,
						   (PVOID) &mop,
						   0) == MCIERR_SUCCESS)
		{

			/* Play the sound.  */
			mpp.hwndCallback = (HWND) NULL;
			mpp.ulFrom = 0;
			mpp.ulTo = 0;
			mciSendCommand(mop.usDeviceID, MCI_PLAY, MCI_WAIT, (PVOID)&mpp, 0);
	
			/* Close the file and device. */
			mgp.hwndCallback = (HWND) NULL;
			mciSendCommand(mop.usDeviceID, MCI_CLOSE, MCI_WAIT,
						  (PVOID) &mgp, 0);
		} /* if */

	} /* for */

} /* mciplay */

/* end of mciplay.c */
