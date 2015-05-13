        IDENTIFICATION DIVISION.
        PROGRAM-ID. SOLUTION.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 A         PIC 9(9)    VALUE ZEROES.
        01 I         PIC 9(9)    VALUE ZEROES.
        01 NEED      PIC 9(2)    VALUE ZEROES.
        01 STR       PIC X(10).
        01 RES       PIC X(30).
 
        PROCEDURE DIVISION.
          ACCEPT STR
          MOVE STR TO A

          MOVE 524288 TO I
          MOVE 0 to NEED

          PERFORM until I equal 0
            IF A >= I
              MOVE '1' TO STR
              string RES DELIMITED BY SPACE
                     STR DELIMITED BY SIZE into RES
              MOVE 1 TO NEED

              COMPUTE A = A - I
            ELSE
              IF NEED EQUAL 1
                MOVE '0' TO STR
                string RES DELIMITED BY SPACE
                       STR DELIMITED BY SIZE into RES
              END-IF
            END-IF

            COMPUTE I = I / 2
          END-PERFORM.
          DISPLAY RES
          stop run.
