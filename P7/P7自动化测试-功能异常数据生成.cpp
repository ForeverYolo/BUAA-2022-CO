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
int r1, r2, r3;
int dm[3075];
#define Small (rand()% 10)*4
#define Reg rand() % 5
#define R reg[rand() % 16]
#define I ((rand() + rand()) % 40) * 4
#define Ib  (((rand() + rand()) % 40) * 4 % 32) * 4
#define Lh ((rand() + rand()) % 40) * 2
#define Lb ((rand() + rand()) % 80) 
#define B (rand() % 650)
#define TYPE rand()%6 + 1
#define Normal rand()%23
#define AbNormal rand()%24
#define Delayinstr rand()%21
#define Div0 rand()%19+5
#define Stall_Jal rand()%6+25
int g = 0;
void Choose(int i, int casenum, int no1, int no2, int no3, int no4, int flag, int tag);

void add(int rs, int rt, int rd,int tag)
{
    if(tag ==0) printf("add $%d,$%d,$%d\n", rd, rt, rs);
    else printf("addu $%d,$%d,$%d\n", rd, rt, rs);
}
void And(int rs, int rt, int rd)
{
    printf("and $%d,$%d,$%d\n", rd, rt, rs);
}
void Or(int rs, int rt, int rd)
{
    printf("or $%d,$%d,$%d\n", rd, rt, rs);
}
void slt(int rs, int rt, int rd)
{
    printf("slt $%d,$%d,$%d\n", rd, rt, rs);
}
void sltu(int rs, int rt, int rd)
{
    printf("sltu $%d,$%d,$%d\n", rd, rt, rs);
}
void sub(int rs, int rt, int rd,int tag)
{
    if (tag == 0) printf("sub $%d,$%d,$%d\n", rd, rt, rs);
    else printf("subu $%d,$%d,$%d\n", rd, rt, rs);
}
void addi(int rs, int rt, int imm,int tag)
{
    if (tag == 0) printf("addi $%d,$%d,%d\n", rt, rs, imm);
    else printf("addiu $%d,$%d,%d\n", rt, rs, imm);
}
void andi(int rs, int rt, int imm)
{
    printf("andi $%d,$%d,%d\n", rt, rs, imm);
}
void ori(int rs, int rt, int imm, int op)
{
    int flag = op % 2;
    int immi = 0 - imm;
    if (flag == 0)
    {
        printf("ori $%d,$%d,%d\n", rt, rs, imm);
    }
    else
    {
        printf("ori $%d,$%d,%d\n", rt, rs, immi);
    }
}
void lui(int rs, int rt, int imm, int op)
{
    int flag = op % 2;
    int immi = 0 - imm;
    if (flag == 0)
    {
        printf("lui $%d,%d\n", rs, imm);
        if (rs)
            grf[rs] = imm << 16;
    }
    else
    {
        printf("lui $%d,%d\n", rs, immi);
        if (rs)
            grf[rs] = imm << 16;
    }
}
void mult(int rs, int rt)
{
    printf("mult $%d,$%d\n", rt, rs);
}
void multu(int rs, int rt)
{
    printf("multu $%d,$%d\n", rt, rs);
}
void Div(int rs, int rt)
{
    int rss = rs;
    int rtt = rt;
    while (rtt == 0)
    {
        rtt = Reg;
    }
    while (rss == 0)
    {
        rss = Reg;
    }
    ori(rtt, rss, I + 4, 1);
    ori(rtt, rss, I + 4, 1);
    int delay = Delayinstr;
    while (delay == 10 || delay == 11 || delay == 1)
    {
        delay = Delayinstr;
    }
    Choose(delay, 0, rss, rtt, rs, rt, 0,1);
    Choose(delay, 0, rss, rtt, rs, rt, 0,1);
    printf("div $%d,$%d\n", rtt, rss);
}
void Divu(int rs, int rt)
{
    int rss = rs;
    int rtt = rt;
    while (rtt == 0)
    {
        rtt = Reg;
    }
    while (rss == 0)
    {
        rss = Reg;
    }
    ori(rtt, rss, I + 4, 0);
    ori(rtt, rss, I + 4, 0);
    int delay = Delayinstr;
    while (delay == 10 || delay == 11 || delay == 1)
    {
        delay = Delayinstr;
    }
    Choose(delay, 0, rss, rtt, rs, rt, 0,1);
    delay = Delayinstr;
    while (delay == 10 || delay == 11 || delay == 1)
    {
        delay = Delayinstr;
    }
    Choose(delay, 0, rss, rtt, rs, rt, 0,1);
    printf("divu $%d,$%d\n", rtt, rss);
}
void mfhi(int rs)
{
    printf("mfhi $%d\n", rs);
}
void mflo(int rs)
{
    printf("mflo $%d\n", rs);
}
void mthi(int rs)
{
    printf("mthi $%d\n", rs);
}
void mtlo(int rs)
{
    printf("mtlo $%d\n", rs);
}
void lw_lh_lb(int rs, int rt)
{
    int flag = rand() % 6;
    if (flag == 0)
    {
        int imm = Ib;
        sub(rs, rs, rs,1);
        if ((Reg % 3) == 0)
        {
            printf("lw $%d,%d($%d)\n", rt, imm, rs);
        }
        else if ((Reg % 3) == 1)
        {
            printf("lb $%d,%d($%d)\n", rt, Lb, rs);
        }
        else
        {
            printf("lh $%d,%d($%d)\n", rt, Lh, rs);
        }
    }
    else if (flag == 1)
    {
        if (rs == 0)
        {
            rs++;
        }
        int imm1 = Ib;
        int imm2 = Ib;
        if (imm1 < imm2)
        {
            int temp = imm1;
            imm1 = imm2;
            imm2 = temp;
        }
        sub(rs, rs, rs,1);
        ori(rs, rs, imm1, 0);
        int imm3 = 0 - imm2;
        if ((Reg % 3) == 0)
        {
            printf("lw $%d,%d($%d)\n", rt, imm3, rs);
        }
        else if ((Reg % 3) == 1)
        {
            printf("lb $%d,%d($%d)\n", rt, imm3 + 1, rs);
        }
        else
        {
            printf("lh $%d,%d($%d)\n", rt, imm3 + 2, rs);
        }
    }
    else if (flag == 2)
    {
        int rss = rs;
        int rtt = rt;
        int imm = 1;
        while (rss == 1 || rss == 0)
        {
            rss = Reg;
        }
        while (rtt == 1 || rtt == 0)
        {
            rtt = Reg;
        }
        if (Reg % 2)
        {
            sub(Reg, Reg, rss,1);
            lui(rss, rtt, imm, 0);
            int imm_1 = 0 - (imm << 16);
            if (!Reg)
            {
                Choose(Delayinstr, 0, r1, r2, r3, rss, 0,0);
            }
            if ((Reg % 3) == 0)
            {
                printf("lw $%d,%d($%d)\n", rtt, imm_1 + I, rss);
            }
            else if ((Reg % 3) == 1)
            {
                printf("lb $%d,%d($%d)\n", rtt, imm_1 + I + 1, rss);
            }
            else
            {
                printf("lh $%d,%d($%d)\n", rtt, imm_1 + I + 2, rss);
            }
        }
        else
        {
            ori(Reg, rss, Ib, 0);
            lui(rss, rtt, 0, 0);
            if (!Reg)
            {
                Choose(Delayinstr, 0, r1, r2, r3, rss, 0,0);
            }
            if ((Reg % 3) == 0) printf("lw $%d,%d($%d)\n", rtt, I, rss);
            else if ((Reg % 3) == 1) printf("lh $%d,%d($%d)\n", rtt, I, rss);
            else printf("lb $%d,%d($%d)\n", rtt, I, rss);
        }
    }
    else if (flag == 3)
    {
        int imm = Ib;
        sub(rt, rt, rt,1);
        ori(rt, rt, 12, 0);
        if ((Reg % 3) == 0)
        {
            printf("sw $%d,0($0)\n", rt);
            printf("lw $%d,0($0)\n", rs);
            printf("lw $%d,%d($%d)\n", rt, imm, rs);
            printf("sw $%d,%d($0)\n", rt, Ib);
        }
        else if ((Reg % 3) == 1)
        {
            printf("sh $%d,0($0)\n", rt);
            printf("lh $%d,0($0)\n", rs);
            printf("lh $%d,%d($%d)\n", rt, imm, rs);
            printf("sh $%d,%d($0)\n", rt, Ib);
        }
        else
        {
            printf("sb $%d,0($0)\n", rt);
            printf("lb $%d,0($0)\n", rs);
            printf("lb $%d,%d($%d)\n", rt, imm, rs);
            printf("sb $%d,%d($0)\n", rt, Ib);
        }
    }
    else if (flag == 4)
    {
        int imm = Ib;
        sub(rt, rt, rt,1);
        ori(rt, rt, Ib, 0);
        if ((Reg % 3) == 0)
        {
            printf("sw $%d,0($0)\n", rt);
            ori(rt, rt, Ib, 0);
            printf("lw $%d,0($0)\n", rs);
            printf("sw $%d,%d($%d)\n", rt, Ib, rs);
        }
        else if ((Reg % 3) == 1)
        {
            printf("sh $%d,0($0)\n", rt);
            ori(rt, rt, Ib, 0);
            printf("lh $%d,0($0)\n", rs);
            printf("sh $%d,%d($%d)\n", rt, Ib, rs);
        }
        else
        {
            printf("sb $%d,0($0)\n", rt);
            ori(rt, rt, Ib, 0);
            printf("lb $%d,0($0)\n", rs);
            printf("sb $%d,%d($%d)\n", rt, Ib, rs);
        }
    }
    else //解决 "load <~~ mv_fr"
    {
        int base = Reg;
        int rtt = rt;
        int rss = rs;
        while (rtt == 0 || rtt == base)
        {
            rtt = Reg;
        }
        while (rss == 0 || rss == rtt || rss == base)
        {
            rss = Reg;
        }
        sub(rtt, rtt, rtt,1);
        sub(rss, rss, rss,1);
        int num_1 = rand() % 10;
        while (num_1 <= 4)
        {
            num_1 = rand() % 10;
        }
        int num = (((rand() % 10) + 1) * 4) * num_1 + 4;
        ori(0, rtt, num_1, 0);
        ori(0, rss, num, 0);
        printf("divu $%d,$%d\n", rss, rtt);
        if (Reg % 2 == 1)
        {
            printf("mfhi $%d\n", base);
        }
        else
        {
            printf("mflo $%d\n", base);
        }
        if (Reg % 3)
        {
            int rad = Delayinstr;
            while (rad == 10 || rad == 11)
            {
                rad = Delayinstr;
            }
            Choose(rad, 0, rss, rtt, base, 0, 0,1);
        }
        int random = Reg;
        if ((random % 3) == 0)
        {
            printf("lw $%d,0($%d)\n", rss, base);
        }
        else if ((random % 3) == 1)
        {
            printf("lh $%d,0($%d)\n", rss, base);
        }
        else
        {
            printf("lb $%d,0($%d)\n", rss, base);
        }
    }
}
void sw_sh_sb(int rs, int rt)
{
    int flag = Reg % 2;
    if (flag == 0)
    {
        int imm = Ib;
        sub(rs, rs, rs,1);
        if ((Reg % 3) == 0)
        {
            printf("sw $%d,%d($%d)\n", rt, imm, rs);
        }
        else if ((Reg % 3) == 1)
        {
            printf("sh $%d,%d($%d)\n", rt, imm, rs);
        }
        else
        {
            printf("sb $%d,%d($%d)\n", rt, imm, rs);
        }
    }
    else
    {
        if (rs == 0)
        {
            rs++;
        }
        int imm1 = Ib;
        int imm2 = Ib;
        if (imm1 < imm2)
        {
            int temp = imm1;
            imm1 = imm2;
            imm2 = temp;
        }
        sub(rs, rs, rs,1);
        ori(rs, rs, imm1, 0);
        int imm3 = 0 - imm2;
        if ((Reg % 3) == 0)
        {
            printf("sw $%d,%d($%d)\n", rt, imm3, rs);
        }
        else if ((Reg % 3) == 1)
        {
            printf("sh $%d,%d($%d)\n", rt, imm3, rs);
        }
        else
        {
            printf("sb $%d,%d($%d)\n", rt, imm3, rs);
        }
    }
}
void lw_lh_lb_z(int rs, int rt)
{
    int imm = Ib;
    if ((Reg % 3) == 0)  printf("lw $%d,%d($0)\n", rt, imm);
    else if ((Reg % 3) == 1) printf("lh $%d,%d($0)\n", rt, imm);
    else printf("lb $%d,%d($0)\n", rt, imm);
}
void sw_sh_sb_z(int rs, int rt)
{
    int imm = Ib;
    if ((Reg % 3) == 0)  printf("sw $%d,%d($0)\n", rt, imm);
    else if ((Reg % 3) == 1) printf("sh $%d,%d($0)\n", rt, imm);
    else printf("sb $%d,%d($0)\n", rt, imm);
}
void sw_sh_sb_jal(int rs, int rt)
{
    int imm = -12288;
    if ((Reg % 3) == 0)  printf("sw $%d,%d($%d)\n", rt, imm, rs);
    else if ((Reg % 3) == 1) printf("sh $%d,%d($%d)\n", rt, imm, rs);
    else  printf("sb $%d,%d($%d)\n", rt, imm, rs);
}
void lw_lh_lb_jal(int rs, int rt)
{
    int imm = -12288;
    if ((Reg % 3) == 0)  printf("lw $%d,%d($%d)\n", rt, imm, rs);
    else if ((Reg % 3) == 1) printf("lh $%d,%d($%d)\n", rt, imm, rs);
    else  printf("lb $%d,%d($%d)\n", rt, imm, rs);
}
void sw_sh_sb_diy(int base, int rt, int imm)
{
    if ((Reg % 3) == 0) printf("sw $%d,%d($%d)\n", rt, imm, base);
    else if ((Reg % 3) == 1) printf("sh $%d,%d($%d)\n", rt, imm, base);
    else printf("sb $%d,%d($%d)\n", rt, imm, base);
}
void lw_lh_lb_diy(int base, int rt, int imm)
{
    if ((Reg % 3) == 0) printf("lw $%d,%d($%d)\n", rt, imm, base);
    else if ((Reg % 3) == 1) printf("lh $%d,%d($%d)\n", rt, imm, base);
    else printf("lb $%d,%d($%d)\n", rt, imm, base);
}
void beq_bne(int rs, int rt, int casenum, int flag)
{
    if (flag == 1)
    {
        if ((Reg % 2) == 0) printf("beq $%d,$%d,EndTest%d\n", rs, rt, casenum);
        else  printf("bne $%d,$%d,EndTest%d\n", rs, rt, casenum);
    }
    else
    {
        if ((Reg % 2) == 0) printf("beq $%d,$%d,SubTest%d\n", rs, rt, casenum);
        else printf("bne $%d,$%d,SubTest%d\n", rs, rt, casenum);
    }
}
void beq_bne_exc(int rs, int rt, int casenum, int flag)
{
    if (flag == 1)
    {
        if ((Reg % 2) == 0) printf("beq $%d,$%d,kEndTest%d\n", rs, rt, casenum);
        else  printf("bne $%d,$%d,kEndTest%d\n", rs, rt, casenum);
    }
    else
    {
        if ((Reg % 2) == 0) printf("beq $%d,$%d,kSubTest%d\n", rs, rt, casenum);
        else printf("bne $%d,$%d,kSubTest%d\n", rs, rt, casenum);
    }
}
void mfc0(int rs)
{
    int random = rand() % 3;
    if (random == 0)
    {
        printf("mfc0 $%d $12\n", rs);
    }
    else if (random == 1)
    {
        printf("mfc0 $%d $13\n", rs);
    }
    else
    {
        printf("mfc0 $%d $14\n", rs);
    }
}
void mtc0(int rs)
{
    printf("mtc0 $%d $14\n", rs);
}
void Choose(int i, int casenum, int no1, int no2, int no3, int no4, int flag, int tag)//"add","sub","ori","sw","lw","lui","nop","beq","jal","jr"
{
    int radom = rand() % 5;
    int rs = Reg;
    int rt = Reg;
    int rd = Reg;
    while (rs == no1 || rs == no2 || rs == no3 || rs == no4)
    {
        rs = Reg;
    }
    while (rt == no1 || rt == no2 || rt == no3 || rt == no4)
    {
        rt = Reg;
    }
    while (rd == no1 || rd == no2 || rd == no3 || rd == no4)
    {
        rd = Reg;
    }
    switch (i)
    {
    case 0:
        mfc0(rs);
        break;
    case 1:
        mtc0(rs);
        break;
    case 2:
        And(rs, rt, rd);
        break;
    case 3:
        Or(rs, rt, rd);
        break;
    case 4:
        slt(rs, rt, rd);
        break;
    case 5:
        sltu(rs, rt, rd);
        break;
    case 6:
        if (rand() % 2) add(rs, rt, rd, tag);
        else addi(rs, rt, I, tag);
        break;
    case 7:
        andi(rs, rt, I);
        break;
    case 8:
        mult(rs, rt);
        break;
    case 9:
        multu(rs, rt);
        break;
    case 10:
        Div(rs, rt);
        break;
    case 11:
        Divu(rs, rt);
        break;
    case 12:
        mfhi(rs);
        break;
    case 13:
        mflo(rs);
        break;
    case 14:
        mthi(rs);
        break;
    case 15:
        mtlo(rs);
        break;
    case 16:
        sub(rs, rt, rd,tag);
        break;
    case 17:
        ori(rs, rt, I, 0);
        break;
    case 18:
        lui(rs, rt, I, 0);
        break;
    case 19:
        sw_sh_sb_z(rs, rt);
        break;
    case 20:
        lw_lh_lb_z(rs, rt);
        break;
    case 21:
        sw_sh_sb(rs, rt);
        break;
    case 22:
        lw_lh_lb(rs, rt);
        break;
    case 23:
        beq_bne(rs, rt, casenum, flag);
        break;
    case 24:
        printf("nop\n");
        break;
        //暂停特加： 
    case 25:
        ori(31, rt, I, 0);
        break;
    case 26:
        add(rs, 31, rd,tag);
        break;
    case 27:
        lw_lh_lb_jal(31, rt);
        break;
    case 28:
        sw_sh_sb_jal(31, rt);
        break;
    case 29:
        if (Reg % 2) printf("mthi $31\n");
        else printf("mtlo $31\n");
        break;
    case 30:
        if (Reg % 3 == 0) printf("mult $31,$%d\n", Reg);
        else if (Reg % 3 == 1) printf("multu $31,$%d\n", Reg);
        else if (Reg % 3 == 2) printf("divu $%d,$31\n", Reg);
        else printf("div $%d,$31\n", Reg);
        break;
    case 31:
        g = Reg % 5;
        if (g == 0)
        {
            sub(rs, rs, rs,1);
            add(rs, 31, rd,1);
            sub(31, 31, 31,1); // rd $31 rs=0  
            add(rd, 0, 31,1);
        }
        else if (g == 1)
        {
            sub(rs, rs, rs,1);
            add(rs, 31, rd,1);
            sub(31, 31, 31,1); // rd $31 rs=0  $31=0
            ori(rd, 31, 0, 0);
        }
        else if (g == 2)
        {
            int immi = I;
            sub(rt, rt, rt,1);
            printf("sw $%d,%d($%d)\n", 31, immi, rt);
            sub(31, 31, 31,1);
            printf("lw $%d,%d($%d)\n", 31, immi, rt);
        }
        else if (g == 3)
        {
            sub(rs, rs, rs,1);
            add(rs, 31, rd,1);
            add(31, 31, 31,1);
            sub(rd, 31, 31,1); // rd $31 rs=0  
        }
        else if (g == 4)
        {
            mtlo(31);
            mthi(31);
            sub(31, 31, 31,1);
            if (Reg % 2) mflo(31);
            else mfhi(31);
        }
        break;
    case 32: //异常特加
        printf("#Exc:\n");
        radom = rand() % 6;
        if (radom == 0)  //ADEL
        {
            //PC
            int Imm = 0;
            if (Reg % 2 == 0)
            {
                Imm = 28668 + rand();
            }
            else
            {
                while (((Imm % 4) == 0) && (Imm >= 16768))
                {
                    Imm = rand() % 28669;
                }
            }
            sub(rs, rs, rs,1);
            ori(rs, rs, Imm, 0);
            printf("jr $%d\n", rs);
            printf("nop\n");
        }
        else if (radom == 1) //ADEL
        {
            int random = rand() % 3;
            if (random == 0)
            {
                int Imm = rand() % 32548;
                if ((Reg % 3) == 0) printf("lw $%d,%d($0)\n", rt, Imm);
                else if ((Reg % 3) == 1) printf("lh $%d,%d($0)\n", rt, Imm);
                else printf("lb $%d,%d($0)\n", rt, Imm);
            }
            else if (random == 1)
            {
                int a = rand() % 12;
                if (a == 0)        printf("lh $%d,32512($0)\n", rt);
                else if (a == 1)   printf("lh $%d,32516($0)\n", rt);
                else if (a == 2)   printf("lh $%d,32520($0)\n", rt);
                else if (a == 3)   printf("lb $%d,32512($0)\n", rt);
                else if (a == 4)   printf("lb $%d,32516($0)\n", rt);
                else if (a == 5)   printf("lb $%d,32520($0)\n", rt);
                else if (a == 6)   printf("lh $%d,32528($0)\n", rt);
                else if (a == 7)   printf("lh $%d,32532($0)\n", rt);
                else if (a == 8)   printf("lh $%d,32536($0)\n", rt);
                else if (a == 9)   printf("lb $%d,32528($0)\n", rt);
                else if (a == 10)  printf("lb $%d,32532($0)\n", rt);
                else if (a == 11)  printf("lb $%d,32536($0)\n", rt);
            }
            else if (random == 2)
            {
                sub(rt, rt, rt,1);
                ori(rt, rt, 2147480000 + I, 0);
                int a = rand() % 3;
                if (a == 0) printf("lw $%d,%d($%d)\n", rs, 2147480000 + I, rt);
                else if (a == 1) printf("lh $%d,%d($%d)\n", rs, 2147480000 + I, rt);
                else if (a == 2) printf("lb $%d,%d($%d)\n", rs, 2147480000 + I, rt);
            }
        }
        else if (radom == 2)
        {
            int random = rand() % 3;
            if (random == 0)
            {
                int Imm = rand() % 32548;
                if ((Reg % 3) == 0) printf("sw $%d,%d($0)\n", rt, Imm);
                else if ((Reg % 3) == 1) printf("sh $%d,%d($0)\n", rt, Imm);
                else printf("sb $%d,%d($0)\n", rt, Imm);
            }
            else if (random == 1)
            {
                int a = rand() % 13;
                if (a == 0)       printf("sh $%d,32512($0)\n", rt);
                else if (a == 1)  printf("sh $%d,32516($0)\n", rt);
                else if (a == 2)  printf("sh $%d,32520($0)\n", rt);
                else if (a == 3)  printf("sb $%d,32512($0)\n", rt);
                else if (a == 4)  printf("sb $%d,32516($0)\n", rt);
                else if (a == 5)  printf("sb $%d,32520($0)\n", rt);
                else if (a == 6)  printf("sh $%d,32528($0)\n", rt);
                else if (a == 7)  printf("sh $%d,32532($0)\n", rt);
                else if (a == 8)  printf("sh $%d,32536($0)\n", rt);
                else if (a == 9)  printf("sb $%d,32528($0)\n", rt);
                else if (a == 10)  printf("sb $%d,32532($0)\n", rt);
                else if (a == 11)  printf("sb $%d,32536($0)\n", rt);
                else if (a == 11)  printf("sw $%d,32520($0)\n", rt);
                else if (a == 12)  printf("sw $%d,32536($0)\n", rt);
            }
            else if (random == 2)
            {
                sub(rt, rt, rt,1);
                ori(rt, rt, 2147480000 + I, 0);
                int a = rand() % 3;
                if (a == 0) printf("sw $%d,%d($%d)\n", rs, 2147480000 + I, rt);
                else if (a == 1) printf("sh $%d,%d($%d)\n", rs, 2147480000 + I, rt);
                else if (a == 2) printf("sb $%d,%d($%d)\n", rs, 2147480000 + I, rt);
            }
        }
        else if (radom == 3)
        {
            printf("syscall\n");
        }
        else if (radom == 4)
        {
            printf("ftrap\n");
        }
        else if (radom == 5)
        {
            while (rs == 1 || rs == 0)
            {
                rs = Reg;
            }
            while (rt == 1 || rt == 0 || rt == rs)
            {
                rt = Reg;
            }
            while (rd == 1 || rd == 0 || rd == rs || rd == rt)
            {
                rd = Reg;
            }
            int a = rand() % 3;
            sub(rs, rs, rs,0);
            ori(rs, rs, 2147480000 + I, 0);
            sub(rt, rt, rt,0);
            ori(rt, rt, 2147480000 + I, 0);
            if (a == 0)
            {
                add(rd, rs, rt,0);
            }
            else if (a == 1)
            {
                addi(rs, rd, 2147480000 + I,0);
            }
            else
            {
                sub(rs, rt, rt,0);
                sub(rs, rt, rt,0);
                sub(rs, rt, rt,0);
                sub(rs, rt, rt,0);
                sub(rs, rt, rt,0);
            }
        }
        printf("#ExcEnd:\n");
    }
}
int main() {
	int glo = rand()%2;
    srand(time(NULL));
    freopen("test.asm", "w", stdout);
    printf("beq $0,$0,fk\n");
    printf("nop\n");
    printf("prpr:beq $0,$0,prpr\n");
    printf("sw $25,0x7f00($0)\n");
    printf("fk:\n");
    printf("ori $t1,11\n");
    printf("ori $t2,20\n");
 	printf("ori $t3,0xFC01\n"); 
	printf("mtc0 $t3,$12\n");
	if(glo)
	{
		printf("sw $t1,0x7f00($0)\n");
		printf("sw $t2,0x7f04($0)\n");
	}
	else
	{
		printf("sw $t1,0x7f10($0)\n");
		printf("sw $t2,0x7f14($0)\n");		
	}
	printf("ori $25,10\n"); 
	printf("ori $24,11\n"); 
	printf("\n");
    for (int i = 0;i <= 31;i++)
    {
    	if(i!=24&&i!=25)
        printf("ori $%d, $0, %d\n", i, I);
    }
    int T = 13;
    for (int i = 1; i <= T; i++) {
        printf("\n");
        int select = Normal;
        Choose(Normal, 0, -1, -1, -1, -1, 0,1);
        Choose(Normal, 0, -1, -1, -1, -1, 0,1);
        if (Reg % 4)
        {
            printf("jal Test_jal%d\n", i);
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0,1);
            printf("beq $0,$0,Test_beq%d\n", i);
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0,1);
            printf("Test_jal%d: jr $ra\n", i);
            printf("Test_beq%d:\n", i);
        }
        Choose(Normal, 0, -1, -1, -1, -1, 0,1);
        printf("jal Test%d\n", i);
        Choose(Delayinstr, 0, -1, -1, -1, -1, 0,1);
        if (i < T)
        {
            printf("Back%d:", i);
        }
        else
        {
            printf("jal End\n");
            Choose(Delayinstr, 0, -1, -1, -1, -1, 0,1);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= T; i++)
    {
        printf("Test%d:\n", i);
        int sign = Reg % 4;
        if (sign != 3)
        {
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0,1);
        }
        else
        {
            beq_bne(Reg, 31, i, 1);
        }
        r1 = Div0;
        r2 = Div0;
        r3 = Div0;
        while (r1 == r2 || r2 == r3 || r1 == r3 || r1 == 8 || r1 == 9 || r1 == 10 || r2 == 8 || r2 == 9 || r2 == 10 || r3 == 8 || r3 == 9 || r3 == 10 || r1 == 26 || r1 == 27 || r2 == 26 || r2 == 27 || r3 == 26 || r3 == 27)
        {
            r1 = Div0;
            r2 = Div0;
            r3 = Div0;
        }
        int flag = Reg % 2;//判断跳转的相对位置 0 为向前 1 为向后
        if (flag == 0)
        {
            sub(r1, r1, r1,1);
            sub(r2, r2, r2,1);
            ori(r2, r2, 2, 0);
            sub(r3, r3, r3,1);
            ori(r3, r3, 1, 0);
            printf("SubTest%d:\n", i);
            add(r3, r1, r1,1);
            beq_bne(r1, r2, i, 1);
            Choose(Delayinstr, 0, r1, r2, r3, -1, flag,1);
        }
        int last_k = 0;
        for (int j = 1; j <= 25; j++)
        {
            if (j <= 7)
            {
                if (rand() % 20 == 0)
                {
                    Choose(32, 0, r1, r2, r3, -1, flag,1);
                }
                else
                {
                    int select = Normal;
                    Choose(select, 0, r1, r2, r3, -1, flag,1);
                }
            }
            else
            {
                int select = AbNormal;
                if (select == 23)
                {
                    if (flag == 0)
                    {
                        beq_bne(Reg, Reg, i, 0);
                        if (rand() % 3 == 0)
                        {
                            printf("syscall\n");
                        }
                        else
                        {
                            Choose(Delayinstr, 0, r1, r2, r3, -1, flag,1);
                        }
                    }
                    else
                    {
                        beq_bne(Reg, Reg, i, 1);
                        if (rand() % 3 == 0)
                        {
                            printf("syscall\n");
                        }
                        else
                        {
                            Choose(Delayinstr, 0, r1, r2, r3, -1, flag,1);
                        }
                    }
                }
                else
                {
                    if (rand() % 20 == 0)
                    {
                        Choose(32, 0, r1, r2, r3, -1, flag,1);
                    }
                    else
                    {
                        Choose(select, i, r1, r2, r3, -1, flag,1);
                    }
                }
            }
        }
        printf("EndTest%d:\n", i);
        Choose(31, 0, 0, 1, -1, -1, 0,1);
        int sign1 = Reg % 2;
        if (sign1)
        {
            Choose(Delayinstr, 0, -1, -1, -1, -1, 0,1);
        }
        printf("jr $ra\n");
        int delay = Delayinstr;
        if (delay == 10)
        {
            printf("div $%d,$ra\n", Reg);
        }
        else if (delay == 11)
        {
            printf("divu $%d,$ra\n", Reg);
        }
        else
        {
            Choose(delay, 0, -1, -1, -1, -1, 0,1);
        }
        printf("\n\n");
    }
    printf("End:\n");
    printf("beq $0,$0,End\n");
    if(glo)
    {
    	printf("sw $25,0x7f00($0)\n\n");
	}
    else
    {
    	printf("sw $25,0x7f10($0)\n\n");
	}
    printf(".ktext 0x4180\n");
    if(glo)
    {
    	printf("sw $25,0x7f00($0)\n");
	}
	else
	{
		printf("sw $25,0x7f10($0)\n");
	}
    printf("mfc0,$k1,$13\n");
    printf("andi $k1,$k1,0x7c\n");
    printf("bne $k1,$0,noint\n");
    printf("nop\n");
    printf("ori $1,$0,0xABCD\n");
    printf("beq $0,$0,kend\n");
    printf("nop\n");
    printf("noint:\n");
    printf("mfc0 $k1,$13\n");
    printf("andi $k1,$k1,0x80000000\n");
    printf("beq $k1,$0,nodelay\n");
    printf("nop\n");
    printf("mfc0 $k0, $14\n");
    printf("andi $k0,$k0,0xfffffffc\n");
    printf("addu $k0, $k0, 4\n");
    printf("mtc0 $k0, $14\n");
    printf("nodelay:\n");
    printf("mfc0 $k0, $14\n");
    printf("andi $k0,$k0,0xfffffffc\n");
    printf("addu $k0, $k0, 4\n");
    printf("mtc0 $k0, $14\n");
    printf("subu $k1,$k1,$k1\n");
    printf("ori $k1,$0,0x3008\n");
    printf("subu $8,$8,$8\n");
    printf("ori $8,$0,0x6ffc\n");
    printf("slt $9,$8,$k0\n");
    printf("beq $9,$0,nopc_0\n");
    printf("nop\n");
    printf("mtc0 $k1,$14\n");
    printf("addiu $k0,$k1,0\n");
    printf("nopc_0:\n");
    printf("subu $10,$10,$10\n");
    printf("ori $10,$0,0x3000\n");
    printf("slt $9,$k0,$10\n");
    printf("beq $9,$0,nopc_1\n");
    printf("nop\n");
    printf("mtc0 $k1,$14\n");
    printf("addiu $k0,$k1,0\n");
    printf("nopc_1:\n");
    T = 1;
    for (int i = 1; i <= T; i++) {
        printf("\n");
        for (int kk = 0;kk < 4;kk++)
        {
            int select = Normal;
            while (select == 1)
            {
                select = Normal;
            }
            Choose(select, 0, -1, -1, -1, -1, 0,1);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= T; i++)
    {
        printf("kTest%d:\n", i);
        int sign = Reg % 4;
        if (sign != 3)
        {
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0,1);
        }
        else
        {
            beq_bne_exc(Reg, 31, i, 1);
        }
        r1 = Div0;
        r2 = Div0;
        r3 = Div0;
        while (r1 == r2 || r2 == r3 || r1 == r3)
        {
            r1 = Div0;
            r2 = Div0;
            r3 = Div0;
        }
        int flag = 1;//判断跳转的相对位置 0 为向前 1 为向后
        if (flag == 0)
        {
            sub(r1, r1, r1,1);
            sub(r2, r2, r2,1);
            ori(r2, r2, 10, 0);
            sub(r3, r3, r3,1);
            ori(r3, r3, 1, 0);
            printf("kSubTest%d:\n", i);
            add(r3, r1, r1,1);
            beq_bne_exc(r1, r2, i, 1);
            int delay_1 = Delayinstr;
            while (delay_1 == 1)
            {
                delay_1 = Delayinstr;
            }
            Choose(delay_1, 0, r1, r2, r3, -1, flag,1);
        }
        int last_k = 0;
        for (int j = 1; j <= 25; j++)
        {
            if (j <= 7)
            {
                int select = Normal;
                while (select == 1)
                {
                    select = Normal;
                }
                int random = rand() % 5;
                if (random == 0) printf("mtc0 $k0, $14\n");
                else if (random == 1) mfc0(Reg);
                else Choose(select, 0, r1, r2, r3, -1, flag,1);
            }
            else
            {
                int select = AbNormal;
                while (select == 1)
                {
                    select = AbNormal;
                }
                if (select == 23)
                {
                    if (flag == 0)
                    {
                        beq_bne_exc(Reg, Reg, i, 0);
                        int random = rand() % 5;
                        if (random == 0) printf("mtc0 $k0, $14\n");
                        else if (random == 1) mfc0(Reg);
                        else
                        {
                            int delay_1 = Delayinstr;
                            while (delay_1 == 1)
                            {
                                delay_1 = Delayinstr;
                            }
                            Choose(delay_1, 0, r1, r2, r3, -1, flag,1);
                        }
                    }
                    else
                    {
                        beq_bne_exc(Reg, Reg, i, 1);
                        int random = rand() % 5;
                        if (random == 0) printf("mtc0 $k0, $14\n");
                        else if (random == 1) mfc0(Reg);
                        else
                        {
                            int delay_1 = Delayinstr;
                            while (delay_1 == 1)
                            {
                                delay_1 = Delayinstr;
                            }
                            Choose(delay_1, 0, r1, r2, r3, -1, flag,1);
                        }
                    }
                }
                else
                {
                    int random = rand() % 5;
                    if (random == 0) printf("mtc0 $k0, $14\n");
                    else if (random == 1) mfc0(Reg);
                    else Choose(select, i, r1, r2, r3, -1, flag,1);
                }
            }
        }
        printf("kEndTest%d:\n", i);
        Choose(31, 0, 0, 1, -1, -1, 0,1);
        int sign1 = Reg % 2;
        if (sign1)
        {
            int random = rand() % 3;
            if (random == 0) printf("mtc0 $k0, $14\n");
            else if (random == 1) mfc0(Reg);
            else
            {
                int delay_1 = Delayinstr;
                while (delay_1 == 1)
                {
                    delay_1 = Delayinstr;
                }
                Choose(delay_1, 0, -1, -1, -1, -1, 0,1);
            }
        }
        int delay = Delayinstr;
        while (delay == 1)
        {
            delay = Delayinstr;
        }
        if (delay == 10)
        {
            printf("div $%d,$ra\n", Reg);
        }
        else if (delay == 11)
        {
            printf("divu $%d,$ra\n", Reg);
        }
        else
        {
            int random = rand() % 3;
            if (random == 0) printf("mtc0 $k0, $14\n");
            else if (random == 1) mfc0(Reg);
            else Choose(delay, 0, -1, -1, -1, -1, 0,1);
        }
        printf("kend:\n");
        if(glo)
        {
        	printf("sw $24,0x7f00($0)\n");
		}
        else
        {
        	printf("sw $24,0x7f10($0)\n");
		}
        printf("eret\n\n");
        printf("addi $1,$1,1\n");
    }
    return 0;
}


