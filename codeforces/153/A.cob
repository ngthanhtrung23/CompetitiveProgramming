       IDENTIFICATION DIVISION.
       PROGRAM-ID. SOLUTION.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01 A        PIC 9(10)   VALUE ZEROES.
       01 B        PIC 9(10)   VALUE ZEROES.
       01 STR      PIC X(10).
	   01 F        PIC 9(10).

       PROCEDURE DIVISION.
         ACCEPT STR
         MOVE STR TO A
         ACCEPT STR
         MOVE STR TO B
         ADD A TO B
		 MOVE B TO STR
		 perform until STR(1:1) IS NOT EQUAL TO '0'
		   move length OF STR TO F
		   SUBTRACT 1 FROM F
		   move STR(2:F) TO STR
		 end-perform.
         DISPLAY STR
         STOP RUN.
