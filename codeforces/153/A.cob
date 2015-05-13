        IDENTIFICATION DIVISION.
        PROGRAM-ID. SOLUTION.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 A         PIC 9(6)    VALUE ZEROES.
        01 B         PIC 9(6)    VALUE ZEROES.
        01 X1        PIC 9(1)    VALUE ZEROES.
        01 X2        PIC 9(2)    VALUE ZEROES.
        01 X3        PIC 9(3)    VALUE ZEROES.
        01 X4        PIC 9(4)    VALUE ZEROES.
        01 X5        PIC 9(5)    VALUE ZEROES.
        01 STR       PIC X(10).
 
        PROCEDURE DIVISION.
          ACCEPT STR
          MOVE STR TO A
          ACCEPT STR
          MOVE STR TO B
          ADD A TO B

          IF B < 10
            MOVE B TO X1
            DISPLAY X1
          ELSE
            IF B < 100
              MOVE B TO X2
              DISPLAY X2
            ELSE
              IF B < 1000
                MOVE B TO X3
                DISPLAY X3
              ELSE
                IF B < 10000
                  MOVE B TO X4
                  DISPLAY X4
                ELSE
                  IF B < 100000
                    MOVE B TO X5
                    DISPLAY X5
                  ELSE
                    DISPLAY B
                  END-IF
                END-IF
              END-IF
            END-IF
          END-IF
          STOP RUN.
