# Unix shell and history feature

## 设计实现

1. 解释并执行命令
   
2. 命令：
   + 已经实现的命令(创建进程去执行)
   + 内建命令（单独实现）
   + 历史（见书上的说明）

3. 历史记录

## 编译

编译命令： `make`

其他命令详见Makefile

## 具体实现

这里的版本仅仅实现了书上要求的基本功能，因为最后时间来不及了，所以pipe和重定向等没有做

1. Analyzer：实现了读取和分析命令的部分
   
   `GetCmd`: 从stdin读取一行命令

   `AnalyzeCmd`: 解析命令(这里包含了对`!!`和`![number]`命令的扩展)

   `FormStdCmd`: 从argv重组成一个完整的命令，防止调用历史命令时需要对叹号进行递归的扩展

2. Executer：
   
   `Command`: 实现对内建命令和本地的命令的运行

3. History：
   
   `SaveHistory`: 存储一条命令

   `GetHistory`: 根据输入的数字获取一条历史命令

4. Builtins：cd, dirs, history, exit

5. shell: shell主体的实现和命令提示符号的打印

## 泄漏

结果见文件leak-check.txt，使用valgrind作为检测工具