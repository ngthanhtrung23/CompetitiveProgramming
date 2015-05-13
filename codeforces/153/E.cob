       IDENTIFICATION DIVISION.
       PROGRAM-ID. SOLUTION.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01 STR      PIC X(20).
       01 RES      PIC 9(30).
       01 N        PIC 9(10).
       01 I        PIC 9(10).
       01 J        PIC 9(10).
       01 DX       PIC S9(10)V9(16).
       01 DY       PIC S9(10)V9(16).
       01 R        PIC S9(10)V9(16).
       01 A.
            05 U   PIC S9(10)V9(16) OCCURS 55 TIMES.
            05 V   pic S9(10)V9(16) OCCURS 55 TIMES.

       PROCEDURE DIVISION.
         ACCEPT STR
         MOVE STR TO N
         MOVE ZERO TO I
         perform N times
           ADD 1 TO I
           ACCEPT STR
           MOVE STR TO U(I)
           ACCEPT STR
           MOVE STR TO V(I)
         end-perform.
         
         MOVE ZERO TO I
         MOVE ZERO TO RES
         perform N times
           ADD 1 TO I
           MOVE ZERO TO J
           perform N times
             ADD 1 TO J
             MOVE U(I) TO DX
             SUBTRACT U(J) FROM DX
             MOVE V(I) TO DY
             SUBTRACT V(J) FROM DY
             
             MULTIPLY DX BY DX
             MULTIPLY DY BY DY
             ADD DX TO DY
             IF DY > RES
               MOVE DY TO RES
             END-IF
           end-perform
         end-perform
         COMPUTE R = RES **.5
         DISPLAY R
         STOP RUN.