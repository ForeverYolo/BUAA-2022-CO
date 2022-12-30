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
char RR[100][1000] = { "add","sub","ori","lui","sw","lw","nop","beq","jal","jr" };
int reg[] = { 0, 1, 2, 3, 31, 1, 2, 3, 31, 1, 2, 3, 31 };
int dm[3075];
#define Reg rand() % 5
#define R reg[rand() % 16]
#define I ((rand() + rand()) % 40) * 4
#define B (rand() % 650)
#define TYPE rand()%6 + 1
#define Normal rand()%8
#define AbNormal rand()%9
#define Delayinstr rand()%6
#define Div0 rand()%26+5
void Choose(int i, int casenum, int no1, int no2, int no3, int flag);
void add(int rs, int rt, int rd)
{
    printf("addu $%d,$%d,$%d\n", rd, rt, rs);
    if (rd)
        grf[rd] = grf[rs] + grf[rt];
}
void sub(int rs, int rt, int rd)
{
    printf("subu $%d,$%d,$%d\n", rd, rt, rs);
    if (rd)
        grf[rd] = grf[rs] - grf[rt];
}
void ori(int rs, int rt, int imm,int op)
{
	int flag = op % 2;
	int immi = 0 - imm;
	if(flag==0) 
	{
    	printf("ori $%d,$%d,%d\n", rt, rs, imm);
    	if (rt)
        	grf[rt] = grf[rs] | imm;		
	}
	else
	{
		printf("ori $%d,$%d,%d\n", rt, rs, immi);
		if (rt)
        	grf[rt] = grf[rs] | imm;
	}
}
void lui(int rs, int rt, int imm,int op)
{
	int flag = op % 2;
	int immi = 0 - imm;
	if(flag==0) 
	{
    	printf("lui $%d,%d\n", rs, imm);
    	if (rs)
       		grf[rs] =  imm << 16;
    }
    else
    {
    	printf("lui $%d,%d\n", rs, immi);
    	if (rs)
       		grf[rs] =  imm << 16;    	
	}
}
void lw(int rs, int rt)
{
	int flag = Reg % 2;
	if(flag==0)
	{
		int imm = I;
    	sub(rs, rs, rs);
    	printf("lw $%d,%d($%d)\n", rt, imm, rs);
    	grf[rt] = dm[imm / 4];
	}
	else
	{
		if(rs==0)
		{
			rs++;
		} 
		int imm1 = I;
		int imm2 = I;
		if(imm1<imm2)
		{
			int temp = imm1;
			imm1 = imm2;
			imm2 = temp;
		}
		sub(rs,rs,rs);
		ori(rs,rs,imm1,0);
		int imm3 = 0 - imm2;
		printf("lw $%d,%d($%d)\n", rt, imm3, rs);
    	grf[rt] = dm[(imm3+imm1) / 4];
	}
}
void sw(int rs, int rt)
{
	int flag = Reg % 2;
	if(flag==0)
	{
    	int imm = I;
    	sub(rs, rs, rs);
    	printf("sw $%d,%d($%d)\n", rt, imm, rs);
    	dm[imm / 4] = grf[rt];		
	}
	else
	{
		if(rs==0)
		{
			rs++;
		} 
		int imm1 = I;
		int imm2 = I;
		if(imm1<imm2)
		{
			int temp = imm1;
			imm1 = imm2;
			imm2 = temp;
		}
		sub(rs,rs,rs);
		ori(rs,rs,imm1,0);
		int imm3 = 0 - imm2;
		printf("sw $%d,%d($%d)\n", rt, imm3, rs);
    	dm[(imm3+imm1) / 4] = grf[rt];
	}

}
void lw_z(int rs, int rt)
{
    int imm = I;
    printf("lw $%d,%d($0)\n", rt, imm);
    grf[rt] = dm[imm / 4];
}
void sw_z(int rs, int rt)
{
    int imm = I;
    printf("sw $%d,%d($0)\n", rt, imm);
    dm[imm / 4] = grf[rt];
}
void beq(int rs, int rt, int casenum, int flag)
{
    if (flag == 1)
    {
        printf("beq $%d,$%d,EndTest%d\n", rs, rt, casenum);
    }
    else
    {
        printf("beq $%d,$%d,SubTest%d\n", rs, rt, casenum);
    }
}
void Choose(int i, int casenum, int no1, int no2, int no3, int flag)//"add","sub","ori","sw","lw","lui","nop","beq","jal","jr"
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
        ori(rs, rt, I, 0);
        break;
    case 3:
        lui(rs, rt, I, 0);
        break;
    case 4:
        sw_z(rs, rt);
        break;
    case 5:
        lw_z(rs, rt);
        break;
    case 6:
        sw(rs, rt);
        break;
    case 7:
        lw(rs, rt);
        break;
    case 8:
        beq(rs, rt, casenum, flag);
        break;
    case 9:
        printf("nop\n");
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
        printf("ori $%d, $0, %d\n", i, I);
    }
    int T = 15;
    for (int i = 1; i <= T; i++) {
        printf("\n");
        int select = Normal;
        Choose(Normal, 0, -1, -1, -1, 0);
        Choose(Normal, 0, -1, -1, -1, 0);
        Choose(Normal, 0, -1, -1, -1, 0);
        printf("jal Test%d\n", i);
        Choose(Delayinstr, 0, -1, -1, -1, 0);
        if (i < T)
        {
            printf("Back%d:", i);
        }
        else
        {
            printf("jal End\n");
            Choose(Delayinstr, 0, -1, -1, -1, 0);
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
            ori(r2, r2, 10,0);
            sub(r3, r3, r3);
            ori(r3, r3, 1,0);
            printf("SubTest%d:\n", i);
            add(r3, r1, r1);
            beq(r1, r2, i, 1);
            Choose(Delayinstr, 0, r1, r2, r3, flag);
        }
        int last_k = 0;
        for (int j = 1; j <= 25; j++)
        {
            if (j <= 7)
            {
                int select = Normal;
                Choose(select, 0, r1, r2, r3, flag);
            }
            else
            {
                int select = AbNormal;
                if (select == 8)
                {
                    if (flag == 0)
                    {
                        beq(Reg, Reg, i, 0);
                        Choose(Delayinstr, 0, r1, r2, r3, flag);
                    }
                    else
                    {
                        beq(Reg, Reg, i, 1);
                        Choose(Delayinstr, 0, r1, r2, r3, flag);
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
        Choose(Delayinstr, 0, -1, -1, -1, 0);
        printf("\n\n");
    }
    printf("End:\n");
    return 0;
}

