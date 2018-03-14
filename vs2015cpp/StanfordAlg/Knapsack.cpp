void TestKnapsack(void);


/*
0-1背包 动态规划
问题: n个物品，价值vi,重量wi，背包大小W。
要求：背包中所装物品的总价值V最大
即求子集S，使sigma(wi) <= W 时，sigma(vi)最大

思路：已知S是最优解，考虑最后一个元素n
1）不选n，则s    是前n-1 背包W    价值V    下最优解
2）选取n，则s-{n}是前n-1 背包W-wi 价值V-vi 下最优解

最优子结构
令A[i,x]表示 前i个元素，背包x下的价值
则A[i,x] = max{ A[i-1, x],    // 包含n
		   vi + A[i-1, x-wi]} // 不包含n 
*/
namespace nsKnapsack01 {


	void main(void)
	{

	}
}







void TestKnapsack(void)
{
	nsKnapsack01::main();
}