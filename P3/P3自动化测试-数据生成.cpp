#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <set>
#include <unordered_map>
#include <vector>
#include <ctime>
typedef long long ll;
using namespace std;
unsigned int grf[32] = { 0 };
char RR[100][1000] = { "add","sub","ori","sw","lw","lui","nop","beq","jal","jr"};
int reg[] = { 0, 1, 2, 3, 31, 1, 2, 3, 31, 1, 2, 3, 31 };
int dm[3075];
#define Reg rand() % 31
#define R reg[rand() % 16]
#define I ((rand() + rand()) % 40) * 4
#define B (rand() % 650)
#define TYPE rand()%6 + 1
#define Normal rand()%7
#define AbNormal rand()%8
#define Div0 rand()%30+1
void add(int rs, int rt, int rd)
{
    printf("add $%d,$%d,$%d\n", rd, rt, rs);
    if (rd)
        grf[rd] = grf[rs] + grf[rt];
}
void sub(int rs, int rt, int rd)
{
    printf("sub $%d,$%d,$%d\n", rd, rt, rs);
    if (rd)
        grf[rd] = grf[rs] - grf[rt];
}
void ori(int rs, int rt, int imm)
{
    printf("ori $%d,$%d,%d\n", rt, rs, imm);
    if (rt)
        grf[rt] = grf[rs] | imm;
}
void lui(int rs, int rt, int imm)
{
    printf("lui $%d,%d\n", rs, imm);
    if (rs)
        grf[rs] = 1u * imm << 16;
}
void lw(int rs, int rt)
{
    int imm = I;
    sub(rs, rs, rs);
    printf("lw $%d,%d($%d)\n", rt, imm, rs);
    grf[rt] = dm[imm / 4];
}
void sw(int rs, int rt)
{
    int imm = I;
    sub(rs, rs, rs);
    printf("sw $%d,%d($%d)\n", rt, imm, rs);
    dm[imm / 4] = grf[rt];
}
int jump[1010];
void beq(int rs, int rt, int casenum,int flag)
{
    int jaddr = B;
    while (jump[jaddr])
        jaddr = B;
    if (flag == 1)
    {
        printf("beq $%d,$%d,EndTest%d\n", rs, rt, casenum);
    }
    else
    {
        printf("beq $%d,$%d,SubTest%d\n", rs, rt, casenum);
    }
    printf("nop\n");
}
void Choose(int i,int casenum,int no1,int no2,int no3,int flag)//"add","sub","ori","sw","lw","lui","nop","beq","jal","jr"
{
    int rs = Reg;
    int rt = Reg;
    int rd = Reg;
    while (rs == no1 || rs == no2 || rs == no3)
    {
        rs = Reg;
    }
    while (rt == no1 || rt == no2 || rt == no3)
    {
        rt = Reg;
    }
    while (rd == no1 || rd == no2 || rd == no3)
    {
        rd = Reg;
    }
    switch (i)
    {
    case 0:
        add(rs, rt, rd);
        break;
    case 1:
        sub(rs, rt, rd);
        break;
    case 2:
        ori(rs, rt, I);
        break;
    case 3:
        sw(rs, rt);
        break;
    case 4:
        lw(rs, rt);
        break;
    case 5:
        lui(rs, rt, I);
        break;
    case 6:
        printf("nop\n");
        break;
    case 7:
        beq(rs, rt, casenum,flag);
        break;
    default:
        break;
    }
}
int main() {
    srand(time(NULL));
    freopen("test.asm", "w", stdout);
    for (int i = 0;i <= 31;i++)
    {
        printf("ori $%d, $0, %d\n",i,I);
    }
    int T = 15;
    for (int i = 1; i <= T; i++) {
        printf("\n");
        int select = Normal;
        Choose(Normal, 0, -1, -1, -1, 0);
        Choose(Normal, 0, -1, -1, -1, 0);
        Choose(Normal, 0, -1, -1, -1, 0);
        printf("jal Test%d\n", i);
        printf("nop\n\n");
        if (i < T)
        {
            printf("Back%d:", i);
        }
        else
        {
            printf("jal End\n");
        }
    }
    printf("\n");
    for (int i = 1; i <= T; i++)
    {
        printf("Test%d:\n", i);
        int r1 = Div0;
        int r2 = Div0;
        int r3 = Div0;
        while (r1 == r2 || r2 == r3 || r1 == r3)
        {
            r1 = Div0;
            r2 = Div0;
            r3 = Div0;
        }
        int flag = Reg % 2;//判断跳转的相对位置 0 为向前 1 为向后
        if (flag == 0)
        {   
            sub(r1, r1, r1);
            sub(r2, r2, r2);
            ori(r2, r2, 10);
            sub(r3, r3, r3);
            ori(r3, r3, 1);
            printf("SubTest%d:\n", i);
            add(r3, r1, r1);
            beq(r1, r2, i, 1);
        }      
        int last_k = 0;
        for (int j = 1; j <= 20; j++)
        {
            if (j <= 7)
            {
                int select = Normal;
                Choose(select,0,r1,r2,r3,flag);
            }
            else
            {
                int select = AbNormal;
                if (select == 7)
                {
                    if (flag == 0)
                    {
                        beq(Reg, Reg, i, 0);
                        printf("nop\n");
                    }
                    else
                    {
                        beq(Reg, Reg, i, 1);
                        printf("nop\n");
                    }
                }
                else
                {
                    Choose(select, i, r1, r2, r3, flag);
                }
            }
        }
        printf("EndTest%d:\n", i);
        printf("jr $ra\n");
        printf("nop\n");
        printf("\n\n");
    }
    printf("End:\n");
    return 0;
}
