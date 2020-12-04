// https://vietnam-national18.kattis.com/problems/battleofpokenom

import java.io.*;
import java.math.*;
import java.util.*;

public class B {
    public static void main(String[] args) {
        (new Solver()).go();
    }
}

class Solver {
    enum Outcome {
        A_WIN, B_WIN, DRAW
    }
    static final String EFFECTIVE = "E";

    public void go() {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int ntest = sc.nextInt();
        for (int test = 0; test < ntest; test++) {
            int k = sc.nextInt();
            int stepOutcome = 0;
            for (int i = 0; i < 2*k; i++) {
                if (sc.next().equals(EFFECTIVE)) {
                    stepOutcome += two(i);
                }
            }
            Outcome matchOutcome = getMatchOutcome(stepOutcome, 2*k);

            int P = getP(stepOutcome, matchOutcome, 2*k);

            // What are the scores at P?
            int scoreA_atP = getScore(stepOutcome, P, 0);
            int scoreB_atP = getScore(stepOutcome, P, 1);
            
            // Find smallest C:
            // - Consider all mask S: suffix(S, C) == suffix(stepOutcome, C)
            //
            // Get score of A and B at P, using mask S.
            // --> the scores must be unique.
            int C = 0;
            while (C < P) {
                boolean good = true;
                for (int S = 0; S < two(P); ++S) {
                    if (suffix(S, C) == suffix(stepOutcome, C)
                            && S != suffix(stepOutcome, P)
                            && getScore(S, P, 0) == scoreA_atP
                            && getScore(S, P, 1) == scoreB_atP
                            && getP(S, matchOutcome, 2*k) == P) {
                        good = false;
                        break;
                    }
                }
                if (good) {
                    break;
                }
                ++C;
            }

            pw.println(P + " " + C);
        }
        sc.close();
        pw.close();
    }

    int getP(int stepOutcome, Outcome matchOutcome, int maxStep) {
        // Find smallest P:
        // Consider all mask S: suffix(S, P) == suffix(stepOutcome, P)
        // All outcome must equals matchOutcome.
        int P = 0;
        while (P < maxStep) {
            boolean good = true;
            for (int S = 0; S < two(maxStep); ++S) {
                if (suffix(S, P) == suffix(stepOutcome, P)
                        && getMatchOutcome(S, maxStep) != matchOutcome) {
                    good = false;
                    break;
                }
            }

            if (good) {
                // All mask S with suffix(S, P) == suffix(stepOutcome, P)
                // has same outcome
                break;
            }
            ++P;
        }
        return P;
    }

    int suffix(int S, int p) {
        return S & (two(p) - 1);
    }

    int two(int x) {
        return 1<<x;
    }

    boolean contains(int S, int x) {
        return ((S >> x) & 1) > 0;
    }

    Outcome getMatchOutcome(int stepOutcome, int maxStep) {
        int scoreA = getScore(stepOutcome, maxStep, 0);
        int scoreB = getScore(stepOutcome, maxStep, 1);
        if (scoreA > scoreB) return Outcome.A_WIN;
        if (scoreB > scoreA) return Outcome.B_WIN;
        return Outcome.DRAW;
    }

    int getScore(int stepOutcome, int maxStep, int mod2) {
        int score = 0;
        for (int i = 0; i < maxStep; i++) {
            if (contains(stepOutcome, i)) {
                if (i % 2 == mod2) ++score;
            }
        }
        return score;
    }
}
