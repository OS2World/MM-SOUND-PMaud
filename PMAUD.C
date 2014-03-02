/*
 *   PMaud v1.1
 *
 * This is a presentation manager app that simply plays a .WAV, and exits.
 *   No window should ever be displayed...this eliminates the annoying .WAV
 *   editor that comes up everytime I click on a .WAV file from my desktop.
 *   It simply plays the sound, and exits, without ever using any 'screen
 *   real estate.'  Actually, this should theoretically work for any sound
 *   file type that MMOS/2 supports, and more than one in each run. (That is,
 *   if I specify foo.wav and bar.snd in the command line, they should both
 *   play. Additionally, wildcards are expanded, and all files matching the
 *   wildcard spec will be played.)
 *
 *  I wrote this to figure out how OS/2 Multimedia programming works at 4:00am.
 *  It therefore follows logically that I take no blame for any of it.  :)
 *
 *  To compile (as I did) with EMX v0.9b, you'll need to have installed the
 *   multimedia import libraries (can be found at
 *   ftp://hobbes.nmsu.edu/os2/unix/emx09b/contrib/mm4emx10.zip)
 *
 *  Written by Ryan C. Gordon, 1996. Feel free to use this source code in
 *   any way you see fit, just drop me a note so I know someone's getting use
 *   out of it.  (mailto:warped42@ix.netcom.com)
 */

#define INCL_WIN
#define INCL_DOS
#include <os2.h>
#include <stdlib.h>
#include "mciplay.h"

/* Global variables. */
HWND hwndFrame, hwndClient;
MCIPLAYARGS mcip;

void sndthread(void *dummy)
/*
 * This function calls the mciplay() function, and then ends the program with
 *  a posted WM_QUIT message.
 */
{
	mciplay(&mcip);

	WinPostMsg(hwndClient, WM_QUIT, NULL, NULL);

} /* sndthread */


MRESULT EXPENTRY AudWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
/*
 * Simple window procedure: in WM_CREATE, spin the work thread, and just
 *   defaultly handle messages until it finishes. (Without some sort of
 *   message queue-handling procedure, though, the presentation manager
 *   will 'lock up' until the work thread finishes.)
 */
{
	static TID tidSound;

	switch (msg)
	{
		case WM_CREATE:
			if (DosCreateThread (&tidSound, (PFNTHREAD) sndthread,
								 (ULONG) NULL, 0, 32768))
				WinPostMsg(hwnd, WM_QUIT, NULL, NULL);

			return(0);

	} /* switch */

	return(WinDefWindowProc(hwnd, msg, mp1, mp2));

} /* AudWndProc */


int main(int argc, char **argv)
{
	static CHAR  szClientClass [] = "PMaudClass";
	static ULONG flFrameFlags = 0;
	HAB hab;
	HMQ hmq;
	QMSG qmsg;

	_wildcard(&argc, &argv);  /* geeze...100% API calls before this... :) */

	mcip.ARGC = argc;		/* Setup for later call to mciplay()... */
	mcip.ARGV = argv;

	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab, 0);

	WinRegisterClass(hab, szClientClass, AudWndProc, 0, 0);

	hwndFrame = WinCreateStdWindow(HWND_DESKTOP,
								   0,
								   &flFrameFlags,
								   szClientClass,
								   NULL,
								   0L,
								   0,
								   0,
								   &hwndClient);

	while (WinGetMsg(hab, &qmsg, NULLHANDLE, 0, 0))
		WinDispatchMsg(hab, &qmsg);

	/* Deinitialize Presentation Manager stuff... */
	WinDestroyWindow(hwndFrame);
	WinDestroyMsgQueue(hmq);
	WinTerminate(hab);

	return(0);
} /* main */

/* end of pmaud.c */
