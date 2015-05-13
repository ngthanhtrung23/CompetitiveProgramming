        IDENTIFICATION DIVISION.
        PROGRAM-ID. SOLUTION.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 K         PIC 9(12)    VALUE ZEROES.
        01 D1        PIC 9(12)    VALUE ZEROES.
        01 D2        PIC 9(12)    VALUE ZEROES.
        01 STR       PIC X(100).
        01 RES       PIC X(100).
 
        PROCEDURE DIVISION.
          ACCEPT STR
          ACCEPT K

          STRING STR(7:4), STR(4:2), STR(1:2) INTO RES

          MOVE FUNCTION INTEGER-OF-DATE(RES) TO D1
          COMPUTE D2 = D1 + K
          MOVE FUNCTION DATE-OF-INTEGER(D2) TO RES

          STRING RES(7:2), '.', RES(5:2), '.', RES(1:4) INTO STR

          DISPLAY STR
          stop run.
