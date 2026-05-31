int cursor = 0;
char color = 0x07;

void putInMemory(int segment, int address, char character);
int getChar();

void printChar(char c)
{
    putInMemory(0xB800, cursor * 2, c);
    putInMemory(0xB800, cursor * 2 + 1, color);
    cursor++;
}

void printString(char* str)
{
    int i = 0;

    while (str[i] != 0)
    {
        printChar(str[i]);
        i++;
    }
}

void newline()
{
    int r = cursor;

    while (r >= 80)
        r = r - 80;

    cursor = cursor + (80 - r);
}

void clearScreen()
{
    int i;

    for (i = 0; i < 2000; i++)
    {
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, color);
    }

    cursor = 0;
}

void readString(char* buf)
{
    int i = 0;
    char c;

    while (1)
    {
        c = getChar();

        if (c == 13)
        {
            buf[i] = 0;
            return;
        }

        if (c == 8)
        {
            if (i > 0)
            {
                i--;
                cursor--;
                printChar(' ');
                cursor--;
            }
        }
        else
        {
            buf[i] = c;
            i++;
            printChar(c);
        }
    }
}

int strcmp(char* a, char* b)
{
    int i = 0;

    while (a[i] != 0 && b[i] != 0)
    {
        if (a[i] != b[i])
            return 0;

        i++;
    }

    if (a[i] == 0 && b[i] == 0)
        return 1;

    return 0;
}

int startsWith(char* str, char* prefix)
{
    int i = 0;

    while (prefix[i] != 0)
    {
        if (str[i] != prefix[i])
            return 0;

        i++;
    }

    return 1;
}

int atoi(char* str)
{
    int n = 0;
    int i = 0;

    while (str[i] != 0)
    {
        n = n * 10;
        n = n + (str[i] - '0');
        i++;
    }

    return n;
}

void intToString(int n, char* buf)
{
    int i = 0;
    int count;

    if (n == 0)
    {
        buf[0] = '0';
        buf[1] = 0;
        return;
    }

    count = 0;
    while (n >= 10000)
    {
        n = n - 10000;
        count++;
    }
    if (count > 0)
        buf[i++] = count + '0';

    count = 0;
    while (n >= 1000)
    {
        n = n - 1000;
        count++;
    }
    if (count > 0 || i > 0)
        buf[i++] = count + '0';

    count = 0;
    while (n >= 100)
    {
        n = n - 100;
        count++;
    }
    if (count > 0 || i > 0)
        buf[i++] = count + '0';

    count = 0;
    while (n >= 10)
    {
        n = n - 10;
        count++;
    }
    if (count > 0 || i > 0)
        buf[i++] = count + '0';

    buf[i++] = n + '0';
    buf[i] = 0;
}

int factorial(int n)
{
    int i;
    int result = 1;

    for (i = 2; i <= n; i++)
        result = result * i;

    return result;
}

char* nextToken(char* str)
{
    while (*str != 0 && *str != ' ')
        str++;

    if (*str == 0)
        return str;

    *str = 0;
    return str + 1;
}

void main()
{
    char cmd[64];

    clearScreen();

    printString("Welcome");
    newline();

    printString("type help");
    newline();
    newline();

    while (1)
    {
        printString("> ");

        readString(cmd);

        newline();

        if (strcmp(cmd, "check"))
        {
            printString("ok");
        }
        else if (strcmp(cmd, "help"))
        {
            printString("check add sub fac season triangle clear about");
        }
        else if (strcmp(cmd, "about"))
        {
            printString("Assistant's Last Gift");
        }
        else if (strcmp(cmd, "clear"))
        {
            clearScreen();
        }
        else if (startsWith(cmd, "add "))
        {
            char* p;
            char* q;
            int a;
            int b;
            char out[16];

            p = cmd + 4;
            q = nextToken(p);

            a = atoi(p);
            b = atoi(q);

            intToString(a + b, out);
            printString(out);
        }
        else if (startsWith(cmd, "sub "))
        {
            char* p;
            char* q;
            int a;
            int b;
            char out[16];

            p = cmd + 4;
            q = nextToken(p);

            a = atoi(p);
            b = atoi(q);

            intToString(a - b, out);
            printString(out);
        }
        else if (startsWith(cmd, "fac "))
        {
            int n;
            char out[16];

            n = atoi(cmd + 4);

            if (n > 8)
            {
                printString("know your limit little bro.");
            }
            else
            {
                intToString(factorial(n), out);
                printString(out);
            }
        }
        else if (startsWith(cmd, "season "))
        {
            char* s;

            s = cmd + 7;

            if (strcmp(s, "winter"))
                color = 0x09;
            else if (strcmp(s, "spring"))
                color = 0x0A;
            else if (strcmp(s, "summer"))
                color = 0x0E;
            else if (strcmp(s, "fall"))
                color = 0x0C;
            else if (strcmp(s, "radiant"))
                color = 0x0D;
        }
        else if (startsWith(cmd, "triangle "))
        {
            int n;
            int i;
            int j;

            n = atoi(cmd + 9);

            for (i = 1; i <= n; i++)
            {
                for (j = 0; j < i; j++)
                    printChar('X');

                newline();
            }
        }

        newline();
    }
}
