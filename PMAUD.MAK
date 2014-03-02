############################
# PMAUD/audt v1.1 makefile #
#                          #
#   --by ryan c. gordon.   #
############################

all : pmaud.exe audt.exe

audt.exe : mciplay.c mciplay.h audt.c audt.def pmaud.rc
	gcc audt.c mciplay.c audt.def -Zomf -Zmtd -O2 -s -los2me -o audt.exe
	rc pmaud.rc audt.exe

pmaud.exe : mciplay.c mciplay.h pmaud.c pmaud.def pmaud.rc
	gcc pmaud.c mciplay.c pmaud.def -Zomf -Zmtd -Zmt -O2 -s -los2me
	rc pmaud.rc pmaud.exe

# end of PMAUD.MAK
