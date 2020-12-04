import java.io.*;
import java.math.*;
import java.util.*;

public class L {
    public static void main(String[] args) throws Exception {
        (new Solution()).run();
    }
}

class Solution {
    static final String VAR = "var";
    static final String PRINT = "print";
    static final int LIMIT = 10_000;

    Map<String, String> vars = new TreeMap<>();

    public void run() throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            String line = in.readLine();
            if (line.equals("end.")) break;

            if (line.startsWith(VAR)) {
                // Remove "VAR " and ";"
                line = line.substring(VAR.length() + 1, line.length() - 1);
                int equalSign = line.indexOf('=');
                assert(equalSign >= 1 && equalSign + 1 < line.length());
                assert(line.charAt(equalSign - 1) == ' ');
                assert(line.charAt(equalSign + 1) == ' ');

                String varName = line.substring(0, equalSign - 1);
                String value = line.substring(equalSign + 2);

                vars.put(varName, parseExpr(value));
                // out.println("var: " + varName + " = " + value);
            } else {
                assert(line.startsWith(PRINT));
                // Remove "PRINT " and ";"
                line = line.substring(PRINT.length() + 1, line.length() - 1);
                out.println(parseExpr(line));
            }
        }

        in.close();
        out.close();
    }

    String parseExpr(String expr) throws Exception {
        int l = expr.length();

        // Find matching braces.
        int[] match = new int[l];
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < l; i++) {
            char c = expr.charAt(i);
            if (c == '{') {
                st.push(i);
            } else if (c == '}') {
                assert(!st.empty());
                int j = st.peek(); st.pop();
                match[i] = j;
                match[j] = i;
            }
        }
        assert(st.isEmpty());

        LimitStringBuilder res = new LimitStringBuilder(LIMIT);
        recursiveParseExpr(expr, 0, l-1, match, res);
        return res.toString();
    }

    void recursiveParseExpr(String expr, int left, int right, int[] match, LimitStringBuilder res) throws Exception {
        if (left > right) throw new Exception();
        if (expr.charAt(left) == '"') {
            assert(expr.charAt(right) == '"');
            res.append(expr.substring(left + 1, right));
            return;
        }
        if (expr.charAt(left) == '`') {
            assert(expr.charAt(right) == '`');
            int i = left + 1;
            while (i < right) {
                if (expr.charAt(i) == '$' && i+1 < right && expr.charAt(i + 1) == '{') {
                    assert(expr.charAt(i + 1) == '{');
                    assert(match[i + 1] < right);
                    recursiveParseExpr(expr, i + 2, match[i + 1] - 1, match, res);
                    i = match[i+1] + 1;
                } else {
                    res.append(expr.charAt(i));
                    ++i;
                }
            }
            return;
        }
        res.append(vars.get(expr.substring(left, right + 1)));
    }
}

class LimitStringBuilder {
    public LimitStringBuilder(int maxCapacity) {
        sb = new StringBuilder(maxCapacity);
        this.maxCapacity = maxCapacity;
    }
    public String toString() {
        return sb.toString();
    }
    public void append(String s) {
        if (sb.length() + s.length() > maxCapacity) return;
        sb.append(s);
    }
    public void append(char c) {
        if (sb.length() == maxCapacity) return;
        sb.append(c);
    }

    private StringBuilder sb;
    private int maxCapacity;
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

}
