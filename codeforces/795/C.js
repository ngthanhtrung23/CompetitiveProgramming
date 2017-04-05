var n = +readline();
var s = "";

if (n % 2 == 0) {
  for(i = 0; i < n/2; i++) {
    s += '1';
  }
} else {
  s += '7';
  n -= 3;
  for(i = 0; i < n/2; i++) s += '1';
}
print(s);