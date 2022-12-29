import difflib
import os
import re
import sys
import filestools
from filediff.diff import file_diff_compare
# 0.自动化生成数据
print("生成指令中"+'\n')
command = "C语言.exe"
os.system(command)

# 1.先运行Mars生成机器码
print("生成机器码中"+'\n')
os.system("java -jar Mars4_5.jar test.asm nc mc CompactTextAtZero a dump .text HexText command.txt")

# 2.运行写好的circ文件将里面的ROM值更改为上述输出的机器码
print("添加指令至单周期cpu中"+'\n')
content = open("command.txt").read()
mymem = open("单周期cpu.circ", encoding="utf-8").read()
mymem = re.sub(r'addr/data: 10 32([\s\S]*?)</a>', "addr/data: 10 32\n" + content + "</a>", mymem)
with open("单周期cpu镜像.circ", "w", encoding="utf-8") as file:
    file.write(mymem)
print("添加指令至另一个单周期cpu中"+'\n')
myfriendmem = open("另一个单周期cpu.circ", encoding="utf-8").read()
myfriendmem = re.sub(r'addr/data: 10 32([\s\S]*?)</a>', "addr/data: 10 32\n" + content + "</a>", myfriendmem)
with open("另一个单周期cpu镜像.circ", "w", encoding="utf-8") as file:
    file.write(myfriendmem)

# 3.运行logisim输出结果
print("运行单周期cpu中"+'\n')
command = "java -jar logisim-generic-2.7.1.jar 单周期cpu镜像.circ -tty table > 单周期cpu结果.txt"
os.system(command)
print("运行另一个单周期cpu中"+'\n')
command = "java -jar logisim-generic-2.7.1.jar 另一个单周期cpu镜像.circ -tty table > 另一个单周期cpu结果.txt"
os.system(command)


# 4.找人对拍
print("正在比较结果，时间可能较长，请耐心等待"+'\n')
def read_file(filename):
    try:
        with open(filename, 'r') as f:
            return f.readlines()
    except IOError:
        print("ERROR: 没有找到文件:%s或读取文件失败！" % filename)
        sys.exit(1)


def compare_file(file1, file2, out_file):
    file1_content = read_file(file1)
    file2_content = read_file(file2)
    d = difflib.HtmlDiff()
    result = d.make_file(file1_content, file2_content)
    with open(out_file, 'w') as f:
        f.writelines(result)


compare_file(r'单周期cpu结果.txt', r'另一个单周期cpu结果.txt', r'result.html')
file_diff_compare("单周期cpu结果.txt","另一个单周期cpu结果.txt")
print("比较结束，测试完毕，请查看结果"+'\n')
#5.到文件中查看结果