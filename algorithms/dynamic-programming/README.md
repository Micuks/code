# 算法设计与分析 归并排序和快速排序实验

## {程序执行环境}
在以下环境下进行过测试.

- [操作系统] macOS 13.1 22C5044e arm64;
- [编译器] clang-1400.0.29.102;
- [构建和测试工具] GNU Make 3.81;
- [文档编译工具] XeTeX 3.141592653-2.6-0.999994 (TeX Live 2022)
- [文本编辑器] nvim v0.8.0

## {程序运行方式}
### {排序程序的编译, 运行和测试方法}
一般方法和应用跳跃点优化的动态规划解0-1背包问题都采用
make进行统一构建和测试, 并使用diff命令将结果进行比较,
以确保排序结果正确.\par

程序(及文档)均使用make进行构建, 对于排序程序的构建, 在shell中执行以下命令:
```bash
make
```
二进制文件 BackPack01, JumpPointBackPack 将被编译在build/目录下,
如果要运行默认测试, 可以在shell中执行这条命令:
```bash
make test
```
默认情况下会使用数据生成器data\_gen生成范围在0到100000范围内的500个数字进行测试.
因为当数据太多的时候, 使用跳跃点方法进行计算的时候会发生溢出.\par

其中, data\_gen生成的输入存储在samples/yet\_another\_sample.in中,
程序的输出存储在samples/bag.out和samples/jump\_bag.out中. \par

如果要使用数据生成器data\_gen生成指定范围内的均匀分布的随机数进行测试, 可以用
这条命令:
```bash
make test [from=<range start>] [to=<range end>] [amount=<number of random numbers>]
# e.g. 
# make test from=0 to=12345 amount=50
```

如果要使用自定义文件进行测试, 可以用这条命令:
```bash
# 一般的0-1背包动态规划解法
build/BackPack01 ${infilename} [${outfilename}]
# 跳跃点优化的0-1背包动态规划解法
build/JumpPointBackPack ${infilename} [${outfilename}]
```

其中, \$\{infilename\}是按第一章中的\textbf{输入格式}\ref{sec:iosample}组织的输入数据.
默认情况下将同时输出到标准输出和samples/mergesort.out, 可选自定义输出到
\$\{outfilename\}路径下. 输出格式为第一章中的\textbf{输出格式}\ref{sec:iosample}.

