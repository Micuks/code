# 算法设计与分析 
分别使用C++与Rust进行编写和实现了四种算法并互为比较.

由于这次文档编写了8小时, 且使用了新的Pseudo-code方式, 
导致latex编译时出现许多错误, 等latex的语法错误改正完毕, 
编译通过后已经超时了, 对于没有按时提交作业感到十分抱歉.

##{程序执行环境}
在以下环境下进行过测试.

	- [操作系统] macOS 13.1 22C5044e arm64;
	- [C++编译器] g++ (Homebrew GCC 12.2.0) 12.2.0;
	- [Rust编译器] rustc 1.65.0 (897e37553 2022-11-02)
	- [构建和测试工具] GNU Make 3.81;
	- [文档编译工具] XeTeX 3.141592653-2.6-0.999994 (TeX Live 2022)
	- [文本编辑器] nvim v0.8.1

## {程序运行方式}

下面是Huffman程序的运行方式, 其余三个运行方式同理. 在latex文档中详细介绍.

\subsection{程序运行方式}
\subsubsection{Huffman编码程序的编译, 运行和测试方法}
C++版本和Rust版本均使用 make进行统一构建和测试, 并使用diff命令将结果进行比较,
以确保排序结果正确.\par

程序(及文档)均使用make进行构建, 对于Huffman编码程序的构建, 在Huffman/文件夹下的shell中执行以下命令:
\begin{lstlisting}[language=bash]
make
\end{lstlisting}
二进制文件 Huffman和HuffmanRS 将被编译在../build/目录下, 其中,
Huffman为C++版的编译输出, 而HuffmanRS为Rust版的编译输出.
如果要运行样例测试, 可以在shell中执行这条命令:
\begin{lstlisting}[language=bash]
make huffman_default_test
\end{lstlisting}
程序输出将存储在data/huffman/huffman[\_rs].out中.\par

如果要自定义生成数据进行测试, 如下
\begin{lstlisting}[language=bash]
make test
\end{lstlisting}
默认情况下会使用数据生成器data\_gen生成范围在0到1000范围内的5000个数字进行测试.\par

程序同样支持\textbf{debug模式}编译. 在debug模式下, 会输出更多的运行信息.
指定DEBUG变量如下:
\begin{lstlisting}[language=bash]
make test DEBUG=1
\end{lstlisting}

其中, huffman\_data\_gen生成的输入存储在data/huffman\_yasample.in中,
程序的输出存储在data/huffman\_yasample.out和data/huffman\_rs\_yasample.out中. \par

如果要使用数据生成器data\_gen生成指定范围内的均匀分布的随机数进行测试, 可以用
这条命令:
\begin{lstlisting}[language=bash]
make test [from=<range start>] [to=<range end>] [amount=<number of random numbers>]
# e.g. 
# make test from=0 to=12345 amount=50
\end{lstlisting}

由于分别使用c++和rust实现了命令行参数处理工具, 因此如果要使用自定义文件进行测试,
可以用这条命令:
\begin{lstlisting}
# c++版
../build/Huffman --in ${infilename} --out [${outfilename}]
# Rust版
../build/HuffmanRS --in ${infilename} --out [${outfilename}]
\end{lstlisting}
其中, \$\{infilename\}是按第一章中的\textbf{输入格式}组织的输入数据.
默认情况下将同时输出到标准输出和data/huffman\_yasample.out, 可选自定义输出到
\$\{outfilename\}路径下. 输出格式为第一章中的\textbf{输出格式}.

\subsubsection{文档编译}
除排序程序使用make管理之外, 本实验的课程报告使用latex进行编写, 因此同样可以
使用make进行管理. 如果要编译文档, 在Greedy/目录下, 运行这条命令:
\begin{lstlisting}[language=bash]
# cwd = Greddy/
make docs
\end{lstlisting}
make将调用xelatex进行编译; 为了确保cross-referencing的正确工作, make将执行两遍
xelatex编译.\par
编译生成的中间文件及文档都保存在docs/build下, docs/report.pdf和docs/build/
report.pdf均是生成的实验报告.

