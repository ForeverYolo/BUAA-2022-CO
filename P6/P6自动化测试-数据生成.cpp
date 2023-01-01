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
#define Normal rand()%21
#define AbNormal rand()%22
#define Delayinstr rand()%19
#define Div0 rand()%26+5
#define Stall_Jal rand()%13+23
void Choose(int i, int casenum, int no1, int no2, int no3, int no4, int flag);

void add(int rs, int rt, int rd)
{
    printf("addu $%d,$%d,$%d\n", rd, rt, rs);
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
void sub(int rs, int rt, int rd)
{
    printf("subu $%d,$%d,$%d\n", rd, rt, rs);
}
void addi(int rs, int rt, int imm)
{
    printf("addiu $%d,$%d,%d\n", rt, rs, imm);
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
    printf("mult $%d,$%d\n",rt, rs);
}
void multu(int rs, int rt)
{
    printf("multu $%d,$%d\n", rt, rs);
}
void Div(int rs, int rt)
{
    int rss= rs;
    int rtt = rt;
    while(rtt==0)
    {
    	rtt = Reg;
	}
	while(rss==0)
	{
		rss = Reg;
	}
	ori(rtt,rss,I+4,0);
	ori(rtt,rss,I+4,0);
	int delay = Delayinstr;
	while(delay == 8||delay == 9)
	{
		delay = Delayinstr;
	}
	Choose(delay, 0, rss, rtt, rs, rt, 0);
	Choose(delay, 0, rss, rtt, rs, rt, 0);
    printf("div $%d,$%d\n", rtt, rss);
}
void Divu(int rs, int rt)
{
    int rss= rs;
    int rtt = rt;
    while(rtt==0)
    {
    	rtt = Reg;
	}
	while(rss==0)
	{
		rss = Reg;
	}
	ori(rtt,rss,I+4,0);
	ori(rtt,rss,I+4,0);
	int delay = Delayinstr;
	while(delay == 8||delay == 9)
	{
		delay = Delayinstr;
	}
	Choose(delay, 0, rss, rtt, rs, rt, 0);
	delay = Delayinstr;
	while(delay == 8||delay == 9)
	{
		delay = Delayinstr;
	}
	Choose(delay, 0, rss, rtt, rs, rt, 0);
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
        sub(rs, rs, rs);
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
        sub(rs, rs, rs);
        ori(rs, rs, imm1, 0);
        int imm3 = 0 - imm2;
        if ((Reg % 3) == 0)
        {
            printf("lw $%d,%d($%d)\n", rt, imm3, rs);
        }
        else if ((Reg % 3) == 1)
        {
            printf("lb $%d,%d($%d)\n", rt, imm3+1, rs);
        }
        else
        {
            printf("lh $%d,%d($%d)\n", rt, imm3+2, rs);
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
        if(Reg%2) 
        {
        	sub(Reg, Reg, rss);
        	lui(rss, rtt, imm, 0);
        	int imm_1 = 0 - (imm << 16);
        	if (!Reg)
        	{
            	Choose(Delayinstr, 0, r1, r2, r3, rss, 0);
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
			ori(Reg,rss,Ib,0);
			lui(rss,rtt,0,0);
			if (!Reg)
        	{
        	    Choose(Delayinstr, 0, r1, r2, r3, rss, 0);
       		}
       		if((Reg % 3) == 0) printf("lw $%d,%d($%d)\n", rtt, I, rss);
       		else if((Reg % 3) == 1) printf("lh $%d,%d($%d)\n", rtt, I, rss);
       		else printf("lb $%d,%d($%d)\n", rtt, I, rss);
		}
    }
    else if (flag == 3)
    {
    	printf("sw $0,0($0)\n");
        int imm = Ib;
        sub(rt, rt, rt);
        ori(rt, rt, 12, 0);
        int random = rand() % 3; 
		if(random == 0)
		{
        	printf("sw $%d,0($0)\n", rt);
		} 
        else if(random == 1)
        {
            printf("sh $%d,0($0)\n", rt);
		}
        else if(random == 2)
        {
            printf("sb $%d,0($0)\n", rt);
		}
        random = rand() % 3;
		if(random == 0)
		{
			printf("lw $%d,0($0)\n", rs);
		} 
        else if(random == 1)
        {
            printf("lh $%d,0($0)\n", rs);
		}
        else if(random == 2)
        {
            printf("lb $%d,0($0)\n", rs);
		}
		random = rand() % 3;
		if(random == 0)
		{
			printf("lw $%d,%d($%d)\n", rt, imm, rs);
		} 
        else if(random == 1)
        {
            printf("lh $%d,%d($%d)\n", rt, imm, rs);
		}
        else if(random == 2)
        {
        	printf("lb $%d,%d($%d)\n", rt, imm, rs);
		}
		random = rand() % 3;
		if(random == 0)
		{
			printf("sw $%d,%d($0)\n", rt, Ib);
		} 
        else if(random == 1)
        {
            printf("sh $%d,%d($0)\n", rt, Ib);
		}
        else if(random == 2)
        {
        	printf("sb $%d,%d($0)\n", rt, Ib);
		} 
    }
    else if(flag == 4) 
    {
    	printf("sw $0,0($0)\n");
        int imm = Ib;
        sub(rt, rt, rt);
        ori(rt, rt, Ib, 0);
        int random = rand()%3;
        if(random == 0) printf("sw $%d,0($0)\n", rt);
        else if(random == 1) printf("sh $%d,0($0)\n", rt);
        else printf("sb $%d,0($0)\n", rt);
        ori(rt, rt, Ib, 0);
        random = rand()%3;
        if(random == 0) printf("lw $%d,0($0)\n", rs);
        else if(random == 1) printf("lh $%d,0($0)\n", rs);
        else printf("lb $%d,0($0)\n", rs);
        random = rand()%3;
        if(random == 0) printf("sw $%d,%d($%d)\n", rt, Ib, rs);
        else if(random == 1) printf("sh $%d,%d($%d)\n", rt, Ib, rs);
        else printf("sb $%d,%d($%d)\n", rt, Ib, rs);
    }
    else //解决 "load <~~ mv_fr"
    {
    	int base = Reg;
    	int rtt = rt;
		int rss = rs;
		while(rtt==0||rtt==base)
		{
			rtt = Reg;	
		} 
		while(rss==0||rss==rtt||rss==base)
		{
			rss = Reg;
		}
    	sub(rtt, rtt, rtt);
    	sub(rss,rss,rss);
    	int num_1 = rand()%10;
    	while(num_1<=4)
    	{
    		num_1 = rand()%10;
		}
    	int num = (((rand()%10)+1)*4)*num_1+4;
    	ori(0,rtt,num_1,0);
    	ori(0,rss,num,0);
    	printf("divu $%d,$%d\n", rss, rtt);
    	if(Reg % 2 == 1)
    	{
    		printf("mfhi $%d\n",base);
		}
		else
		{
			printf("mflo $%d\n",base);
		}
		if(Reg % 3)
		{
			int rad= Delayinstr;
			while(rad == 8 || rad == 9)
			{
				rad = Delayinstr;	
			} 
			Choose(rad, 0, rss, rtt, base, 0, 0);
		}
		int random = Reg;
		if((random % 3) == 0)
		{
			printf("lw $%d,0($%d)\n", rss,base);
		}
		else if((random % 3) == 1)
		{
			printf("lh $%d,0($%d)\n", rss,base);
		}
		else
		{
			printf("lb $%d,0($%d)\n", rss,base); 
		}
	}
}
void sw_sh_sb(int rs, int rt)
{
    int flag = Reg % 2;
    if (flag == 0)
    {
        int imm = Ib;
        sub(rs, rs, rs);
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
        sub(rs, rs, rs);
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
    if((Reg % 3) ==0) printf("sw $%d,%d($%d)\n", rt, imm, base);
    else if((Reg % 3) ==1) printf("sh $%d,%d($%d)\n", rt, imm, base);
    else printf("sb $%d,%d($%d)\n", rt, imm, base);
}
void lw_lh_lb_diy(int base, int rt, int imm)
{
    if ((Reg % 3) == 0) printf("lw $%d,%d($%d)\n", rt, imm, base);
    else if ((Reg % 3)== 1) printf("lh $%d,%d($%d)\n", rt, imm, base);
    else printf("lb $%d,%d($%d)\n", rt, imm, base);
}
void beq_bne(int rs, int rt, int casenum, int flag)
{
    if (flag == 1)
    {
        if((Reg % 2)==0) printf("beq $%d,$%d,EndTest%d\n", rs, rt, casenum);
        else  printf("bne $%d,$%d,EndTest%d\n", rs, rt, casenum);
    }
    else
    {
        if((Reg % 2)==0) printf("beq $%d,$%d,SubTest%d\n", rs, rt, casenum);
        else printf("bne $%d,$%d,SubTest%d\n", rs, rt, casenum);
    }
}
void Choose(int i, int casenum, int no1, int no2, int no3, int no4, int flag)//"add","sub","ori","sw","lw","lui","nop","beq","jal","jr"
{
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
        And(rs, rt, rd);
        break;
    case 1:
        Or(rs, rt, rd);
        break;
    case 2:
        slt(rs, rt, rd);
        break;
    case 3:
        sltu(rs, rt, rd);
        break;
    case 4:
    	if(rand()%2)
    	{
    		add(rs, rt, rd);
		}
		else
		{
			addi(rs, rt, I);
		}   
        break;
    case 5:
        andi(rs, rt, I);
        break;
    case 6:
        mult(rs, rt);
        break;
    case 7:
        multu(rs, rt);
        break;
    case 8:
        Div(rs, rt);
        break;
    case 9:
        Divu(rs, rt);
        break;
    case 10:
        mfhi(rs);
        break;
    case 11:
        mflo(rs);
        break;
    case 12:
        mthi(rs);
        break;
    case 13:
        mtlo(rs);
        break;
    case 14:
        sub(rs, rt, rd);
        break;
    case 15:
        ori(rs, rt, I, 0);
        break;
    case 16:
        lui(rs, rt, I, 0);
        break;
    case 17:
        sw_sh_sb_z(rs, rt);
        break;
    case 18:
        lw_lh_lb_z(rs, rt);
        break;
    case 19:
        sw_sh_sb(rs, rt);
        break;
    case 20:
        lw_lh_lb(rs, rt);
        break;
    case 21:
        beq_bne(rs, rt, casenum, flag);
        break;
    case 22:
        printf("nop\n");
        break;
        //暂停特加：
	case 23:
		slt(31,rt,rd);
		break;
	case 24:
		sltu(31,rs,rd);
		break;
	case 25:
		And(31,rt,rd);
		break;
	case 26:
		Or(31,rt,rd);
		break;
	case 27:
		sub(31,rt,rd);
		break; 
	case 28:
		andi(31,rt,I);
		break;
	case 29:
		addi(31,rt,I);
		break;
    case 30:
        ori(31, rt, I, 0);
        break;
    case 31:
        add(rs, 31, rd);
        break;
    case 32:
        lw_lh_lb_jal(31, rt);
        break;
    case 33:
        sw_sh_sb_jal(31, rt);
        break;
    case 34:
    	if(Reg%2) printf("mthi $31\n");
    	else printf("mtlo $31\n");
    	break;
    case 35:
    	if(Reg%3==0) printf("mult $31,$%d\n",Reg);
    	else if(Reg%3==1) printf("multu $31,$%d\n",Reg);
    	else if(Reg%3==2) printf("divu $%d,$31\n",Reg);
    	else printf("div $%d,$31\n",Reg);
    	break;
    case 36:
        int g = Reg % 5;
        if (g == 0)
        {
            sub(rs, rs, rs);
            add(rs, 31, rd);
            sub(31, 31, 31); // rd $31 rs=0  
            add(rd, 0, 31);
        }
        else if (g == 1)
        {
            sub(rs, rs, rs);
            add(rs, 31, rd);
            sub(31, 31, 31); // rd $31 rs=0  $31=0
            ori(rd, 31, 0, 0);
        }
        else if (g == 2)
        {
            int immi = I;
            sub(rt, rt, rt);
            printf("sw $%d,%d($%d)\n", 31, immi, rt);
            sub(31, 31, 31);
            printf("lw $%d,%d($%d)\n", 31, immi, rt);
        }
        else if(g == 3)
        {
            sub(rs, rs, rs);
            add(rs, 31, rd);
            add(31, 31, 31);
            sub(rd, 31, 31); // rd $31 rs=0  
        }
        else if(g==4)
        {
        	mtlo(31);
        	mthi(31);
        	sub(31, 31, 31);
        	if(Reg%2) mflo(31);
        	else mfhi(31);      	
		}
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
    int T = 13;
    for (int i = 1; i <= T; i++) {
        printf("\n");
        int select = Normal;
        Choose(Normal, 0, -1, -1, -1, -1, 0);
        Choose(Normal, 0, -1, -1, -1, -1, 0);
        if (Reg % 4)
        {
            printf("jal Test_jal%d\n", i);
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0);
            printf("beq $0,$0,Test_beq%d\n", i);
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0);
            printf("Test_jal%d: jr $ra\n", i);
            printf("Test_beq%d:\n", i);
        }
        Choose(Normal, 0, -1, -1, -1, -1, 0);
        printf("jal Test%d\n", i);
        Choose(Delayinstr, 0, -1, -1, -1, -1, 0);
        if (i < T)
        {
            printf("Back%d:", i);
        }
        else
        {
            printf("jal End\n");
            Choose(Delayinstr, 0, -1, -1, -1, -1, 0);
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
            Choose(Stall_Jal, 0, -1, -1, -1, -1, 0);
        }
        else
        {
            beq_bne(Reg, 31, i, 1);
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
        int flag = Reg % 2;//判断跳转的相对位置 0 为向前 1 为向后
        if (flag == 0)
        {
            sub(r1, r1, r1);
            sub(r2, r2, r2);
            ori(r2, r2, 10, 0);
            sub(r3, r3, r3);
            ori(r3, r3, 1, 0);
            printf("SubTest%d:\n", i);
            add(r3, r1, r1);
            beq_bne(r1, r2, i, 1);
            Choose(Delayinstr, 0, r1, r2, r3, -1, flag);
        }
        int last_k = 0;
        for (int j = 1; j <= 25; j++)
        {
            if (j <= 7)
            {
                int select = Normal;
                Choose(select, 0, r1, r2, r3, -1, flag);
            }
            else
            {
                int select = AbNormal;
                if (select == 21)
                {
                    if (flag == 0)
                    {
                        beq_bne(Reg, Reg, i, 0);
                        Choose(Delayinstr, 0, r1, r2, r3, -1, flag);
                    }
                    else
                    {
                        beq_bne(Reg, Reg, i, 1);
                        Choose(Delayinstr, 0, r1, r2, r3, -1, flag);
                    }
                }
                else
                {
                    Choose(select, i, r1, r2, r3, -1, flag);
                }
            }
        }
        printf("EndTest%d:\n", i);
        Choose(36, 0, 0, 1, -1, -1, 0);
        int sign1 = Reg % 2;
        if (sign1)
        {
            Choose(Delayinstr, 0, -1, -1, -1, -1, 0);
        }
        printf("jr $ra\n");
        int delay =  Delayinstr;
        if(delay == 8)
        {
        	printf("div $%d,$ra\n", Reg);
		}
		else if(delay == 9)
		{
			printf("divu $%d,$ra\n", Reg);
		}
		else
		{
			Choose(delay, 0, -1, -1, -1, -1, 0);
		}   
        printf("\n\n");
    }
    printf("End:\n");
//    printf("nop\n");
//    printf("nop\n");
//    printf("nop\n");
//    printf("nop\n");
//    printf("nop\n");
//    printf("tag:beq $0,$0,tag\n");
//    printf("nop\n");
    return 0;
}


