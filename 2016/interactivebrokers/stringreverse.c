char *b = { "ab" };

void f(char *p) {
 int n = strlen(p);
 char *e = p + n - 1;
 char t;
 while(p < e) {
  t = *p++;
  *p = *e--;
  *e = t; 
 }
}
