# 算法设计与分析 归并排序和快速排序实验

## {程序执行环境}

在以下环境下进行过测试.

- [操作系统] Ubuntu 20.04.5 LTS on Windows 10 x86_64, \\
  macOS 12.6 21G115 arm64;
- [编译器] clang-1400.0.29.102;
- [构建和测试工具] GNU Make 3.81;
- [文档编译工具] XeTeX 3.141592653-2.6-0.999994 (TeX Live 2022)

## {程序运行方式}

### {排序程序的编译, 运行和测试方法}

mergesort, 尾递归调用优化的 quicksort 和应用线性选择优化的 quicksort 都采用
make 进行统一构建和测试, 并使用 diff 命令和 C++的 STL 库 sort 结果进行比较,
以确保排序结果正确.

程序(及文档)均使用 make 进行构建, 对于排序程序的构建, 在 shell 中执行以下命令:

```bash
make
```

二进制文件 mergesort, quicksort 和 quicksort_kthSmallest 将被编译在 build/目录下,

如果要运行默认测试, 可以在 shell 中执行这条命令:

```bash
make test
```

如果要使用数据生成器 data_gen 生成指定范围内的均匀分布的随机数进行测试, 可以用
这条命令:

```bash
make testg
```

生成的输入存储在 samples/yet_another_sample.in 中, 程序的输出存储在 samples/
${filename} 中, ${filename}为 mergesort, quicksort 和 QuickSort_kthSmallest.

如果要使用数据生成器 data_gen 生成指定范围内的均匀分布的随机数进行测试, 可以用
这条命令:

```bash
make testg [from=<range start>] [to=<range end>] [amount=<number of random numbers>]

# e.g.

# make testg from=-12345 to=12345 amount=50

```

这种参数对下面介绍的生成递增随机数和递减随机数\textbf{同样适用}.

如果要使用数据生成器 date_gen 生成指定范围内的均匀分布的递增排列的随机数进行测试,
可以用这条命令:

```bash
make testg_ascend
```

生成的输入和程序的输出的存储路径和上述相同.

如果要使用数据生成器 date_gen 生成指定范围内的均匀分布的递增排列的随机数进行测试,
可以用这条命令:

```bash
make testg_descend
```

生成的输入和程序的输出的存储路径和上述相同.

如果要使用自定义文件进行测试, 可以用这条命令:

```bash
build/mergesort ${infilename} [${outfilename}]
build/quicksort ${infilename} [${outfilename}]
build/quicksort_kthSmallest ${infilename} [${outfilename}]
```

其中, \$\{infilename\}是按第一章中的\textbf{输入格式}组织的输入数据.
默认情况下将同时输出到标准输出和 samples/mergesort.out, 可选自定义输出到
\$\{outfilename\}路径下. 输出格式为第一章中的\textbf{输出格式}.

\subsubsection{文档编译}
除排序程序使用 make 管理之外, 本实验的课程报告使用 latex 进行编写, 因此同样可以
使用 make 进行管理. 如果要编译文档, 运行这条命令:

```bash
make docs
```

make 将调用 xelatex 进行编译; 为了确保 cross-referencing 的正确工作, make 将执行两遍
xelatex 编译.
编译生成的中间文件及文档都保存在 docs/build 下, docs/report.pdf 和 docs/build/
report.pdf 均是生成的实验报告.
