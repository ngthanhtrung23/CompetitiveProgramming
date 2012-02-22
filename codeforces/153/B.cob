       IDENTIFICATION DIVISION.
       PROGRAM-ID. SOLUTION.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01 A        PIC 9(10)   VALUE ZEROES.
       01 B        PIC 9(10)   VALUE ZEROES.
       01 STR      PIC X(100).
       01 RES      PIC X(100).
	   01 F        PIC 9(1).
       01 T        PIC 9(10).

       PROCEDURE DIVISION.
         ACCEPT STR
         MOVE STR TO A
         MOVE '' TO STR
         perform UNTIL A IS EQUAL TO ZERO
            DIVIDE 2 INTO A GIVING B REMAINDER F
            MOVE B TO A
            string F   DELIMITED BY SPACE
                   STR DELIMITED BY SIZE into STR
         end-perform.
         MOVE LENGTH OF STR TO T
         SUBTRACT 1 FROM T
         display STR(2:T)
         STOP RUN.
