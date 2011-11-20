int main() {
    string s = Stdio.stdin->gets();
    int a;
    int b, c;
    sscanf(s, "%d%d%d", a, b, c);
    if (a == c || b >= 4) write("YES");
    else write("NO");
}
