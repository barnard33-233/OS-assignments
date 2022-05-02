import sys

def write_to_log():
    fp = open("./log", "w")
    for line in tmp:
        fp.write(line)


def got(x, y):
    try:
        assert(fork[y] == -1)
        fork[y] = x
    except:
        print("{}, {}, {}, {}".format(x, y, fork[y], line_num))
        write_to_log()
        sys.exit(-1)

def release(x, y):
    try:
        assert(fork[y] == x)
        fork[y] = -1
    except:
        print("{}, {}, ,{}, {}".format(x, y, fork[y], line_num))
        write_to_log()
        sys.exit(-1)


firstline = sys.stdin.readline()
cnt = int(firstline)
fork = []
for i in range(cnt):
    fork.append(-1)

line_num = 0
group_cnt = 10000000
tmp = []
while True:
    for i in range(group_cnt):
        line = sys.stdin.readline()
        tmp.append(line)
        line_num += 1
        exec(line)
    print(f"{group_cnt} lines right")
