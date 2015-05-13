       IDENTIFICATION DIVISION.
       PROGRAM-ID. SOLUTION.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01 STR      PIC X(20).
       01 RES      PIC X(20).
       01 A        PIC 9(10).
       01 K        PIC 9(10).
       01 F        PIC 9(10).
       01 C        PIC X(10).

       PROCEDURE DIVISION.
         ACCEPT STR
         ACCEPT RES
         MOVE RES TO K
         MOVE '' TO RES
         MOVE 1 TO A
         perform until STR(A:A) < 'A'
            MOVE STR(A:1) TO C
            perform K times
              if C is equal to 'A'
                move 'B' to C
              else if C is equal to 'B'
                move 'C' to C
              else if C is equal to 'C'
                move 'D' to C
              else if C is equal to 'D'
                move 'E' to C
              else if C is equal to 'E'
                move 'F' to C
              else if C is equal to 'F'
                move 'G' to C
              else if C is equal to 'G'
                move 'H' to C
              else if C is equal to 'H'
                move 'I' to C
              else if C is equal to 'I'
                move 'J' to C
              else if C is equal to 'J'
                move 'K' to C
              else if C is equal to 'K'
                move 'L' to C
              else if C is equal to 'L'
                move 'M' to C
              else if C is equal to 'M'
                move 'N' to C
              else if C is equal to 'N'
                move 'O' to C
              else if C is equal to 'O'
                move 'P' to C
              else if C is equal to 'P'
                move 'Q' to C
              else if C is equal to 'Q'
                move 'R' to C
              else if C is equal to 'R'
                move 'S' to C
              else if C is equal to 'S'
                move 'T' to C
              else if C is equal to 'T'
                move 'U' to C
              else if C is equal to 'U'
                move 'V' to C
              else if C is equal to 'V'
                move 'W' to C
              else if C is equal to 'W'
                move 'X' to C
              else if C is equal to 'X'
                move 'Y' to C
              else if C is equal to 'Y'
                move 'Z' to C
              else if C is equal to 'Z'
                move 'A' to C
              end-if
            end-perform
            string RES DELIMITED BY SPACE
                   C DELIMITED BY SIZE INTO RES
            ADD 1 TO A
         end-perform
         DISPLAY RES
         STOP RUN.