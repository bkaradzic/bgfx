#define f1(i) ((i)*(i))
#define I2(f, n) f(n) + f(n+1)
#define I3(f, n) I2(f, n) + f(n+2)

void main()
{
    int f1 = 4;
    int f2 = f1;
    int f3 = f1(3);
    int f4 = I2(f1, 0);
    int f5 = I3(f1, 0);
}
