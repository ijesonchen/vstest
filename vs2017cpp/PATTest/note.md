# Advanced

## 已处理列表

A1001-A1031

A1043

A1131-A1139

## 未处理列表

```
T1001
A1121
```



## 未排查列表

```
A1014: func1未通过，使用timeout标记。
A1016: A1016PrintCharge未通过。分段计算费用相加
A1018：题解使用BFS+DFS处理，逻辑？
A1030：diskstra rebuild shortest path， pt1 WA
A1131: 太慢
A1123: 尝试nsA1123A能否修正。尝试完全树的两次循环判定算法。
```

## 题解分析

已经参考题解方法。查看代码中的总结部分。

```
A1131 A1133 A1135 A1139 
```

## 日志

```
A1008：20min
A1009：40min
	**2018.01.11
A1010: 24/25
	**2018.01.15
A1010-A1012
	**2018.01.16
A1013: 3/25
	**2018.01.17
A1013: pass
A1014: 19/30
A1015: PASS
	**01.18
A1014: PASS
	**01.19
A1016: 100min 15/25 题解,pass
	**01.28
A1017: 23/25
	**01.29
A1017: 2h, 23/25, pass
	1. 严格按照题目说明，不要随意扩展(sln2)
	2. 按照题目直接编码处理
	**2018.01.29
A1018: 90min，20/30
A1019: 20min, pass
A1020: 80min, pass
	**02.01
A1021: 40min, pass 
	**02.02
A1022: 40MIN, PASS
A1023: 20MIN, PASS
A1024: 20MIN, 18/25，溢出。20min pass。
A1025: 40MIN, pass
	**02.05
A1018: 40MIN 25/30. 题解 20min 25/30
	**02.06
A1018: 4.5h 题解 pass 
	**02.07
A1018: 40min 方法2 pass
	**02.12
A1026: 5d6h 题解 pass **复杂流程的模拟
A1027: 15min pass
A1028: 10min 21/25 pt6 TLE. 题解，pass **排序比较优先考虑整形而非字串
	**02.13
A1029：15min pass 数组长度为偶数时，0基中间位置为(n-1)/2
A1030：2h pass **Dijkstra rebuild算法存在问题。DFS不需要循环。
	**02.23
A1139：2h pass
	**02.24
A1134: 25min pass. 注意输出结果中的大小写。
A1135: 2H PASS. google（二叉搜索树的性质：左小右大）. 
		红黑树叶子节点定义为NULL节点。需要据此判断路径黑节点数。
		1）递归计算每一个节点的路径黑节点，只要有子节点为NULL，即比较黑节点数量
		2）直接递归，当该节点为NULL时，根据父节点黑节点数判断（递归需传递父黑节点数）
	**02.25
A1131: 2H PASS
	**02.26
A1131: ref 1H PASS
A1132: REWRITE 15min pass
A1133: rewrite 30min pass ref 20min pass
A1032: 15MIN pass
	**02.27
A1035: rewrite 70min
A1043: 70min pass. 注意输出格式和大小写！！！
	rewrite: preOrder to postOrder not finished!!!
	**02.28
A1043: rewrite
	**03.01
A1020: 10MIN PASS
A1021: 15MIN 23/25, PT1 段错误 15MIN 23/25
A1022: 20MIN PASS
A1023: 2H 22/30 PT2,3 WA
	模拟测试：见A1023总结。
    **03.02
A1023: ref 80min pass. 
	1. AVL的旋转递归实现
	2. 注意区分满二叉树和完全二叉树。参见代码总结
A1008: 20MIN 18/20 15min 15/20
A1009: 40MIN PASS
A1010: 40MIN 24/25
A1011: 50MIN 27/30 10MIN 27/30 20MIN 18/30
	模拟测试1 2H30MIN：18 25 24 27 = 94
    一定要注意时间。有剩余时间要仔细选择
    **0304
A1108: REF 1H nsA1108A pass，nsA1108B 异常
    **0305
A1108: nsA1108B pass nsA1108RefRewrite pass
A1110: 10MIN PASS
T1004: 1H FAILED
T1005: 30MIN 28/35 TLE
T1006: 1H FAILED 1H 22/35 pt2,3,4,5WA
	模拟测试2：3H 0+28+0=28
	1. 只想到暴力解法
	2. 常规问题不会处理（递归全排列）
	3. 速度太慢（T1006想到方法但是太慢）
	**0306
T1004: Permutation with Recurrence, passed
A1104: 20MIN PASS
A1105: 50MIN PASS
A1106: 30MIN 17/25 wa mle, 5min 丢弃中间结果 17/25 WA，5min float-> double pass 
A1107: 30min 20/30 wa, 30min 检查数据 20/30，10min 定位到问题，20min pass
	模拟测试3：3H 20+25+25+20=90
	1. 最后一题一直怀疑是否是未注意题目细节（30min），最后10min才怀疑是不是算法有问题，生成问题数据后已经没时间测试。
	**03.07
T1004: 1H 29/35 TLE
A1039: 20MIN 23/25 TLE，30min pass
	scanf, map[string]->map[int], set->sort(vector)
	**03.08
A1033: 1H20MIN 未完成 1H 未完成
A1034: 1H05MIN 28/30 段错误 10min PASS

```

## 解题报告

```
Sigmainfy blog
https://www.sigmainfy.com/blog/pat-1026-table-tennis.html
柳婼 の blog
https://www.liuchuo.net/archives/2955
```

