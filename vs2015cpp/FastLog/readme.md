# 程序说明

main.cpp为测试程序

```
1. 初始化预定义日志内容
2. 初始化日志
3. 启动线程LogThread
4. 等待线程结束并打印耗时
```

FastLog为日志实现

```
1. class Logger为日志类。
初始化时，注册信号处理函数，启动后台写入进程。
为了减少多线程同时写入日志时的竞争，初始化时针对每一个线程准备一个SLogHeader对象vector<SLogHeader> vLogContent，同时需要准备多个互斥量vector<mutex> vMtx，用于写日志线程的同步
	struct SLogHeader
	{
		std::string hdr; // 使用该SLogHeader的线程标识符
		std::vector<SLogItem> vLogs; // 线程写入的日志
	｝
	struct SLogItem
	{
		std::int64_t tp; // 日志时间(精确到ns)
		std::string log; // 日志内容
	｝
2. 线程日志写入流程：
	每个线程初始化时，获取到ThreadLogger对象
	class ThreadLogger
	{
		int idxLogCntr; // 对应Logger中的mutex及SLogHeader容器的索引
		Logger* pFastLogger; // Logger指针
		std::string logHdr; // 线程标识符
	｝
	每次写入日志，使用Logger::vMtx[idxLogCntr]锁住Logger::vLogContent[idxLogCntr]，追加日志
3. 日志落地流程：
	vector<SLogHeader> vLogTmp锁住并交换vLogContent中的内容
	每个SLogHeader中的日志是由一个线程顺序写入的，因此，只要对vLogTmp中日志执行归并操作，即可按顺序提取到vLogTmp中的所有日志
	将所有日志按时间序落地
4. crash处理：
	日志一开始注册了SigHandler，当程序crash时：
	停止写入进程并等待结束
	将当前未落地的日志写入文件
```

# 存在的问题及解决方案

由于时间关系，程序有些地方存在一些不合理的地方。
0. windows下测试未达到性能要求

    windows下测试8线程1M次日志调用约耗时600ms。

    可能的优化方案是不实用string而采用定长char[]，或采用内存池方式优化。

1. 规定了最大日志线程

   为了方便，对最大日志线程进行了限制，为每一个线程准备了一个队列

   如果取消这一限制，原来部分逻辑仍然可用，每一条日志都要记录线程标识符即可。

   即合并SLogHeader和SLogItem，展平为 标识符、时间、日志

2. crash处理为了方便，使用了全局Logger指针

   将Logger改为单例模式，在程序启动时（未启动多线程时）初始化，退出时（工作线程已经退出）关闭。

3. linux下性能比windows低很多

   windows server 2008r2: 550ms

   CentOS 7: 1500ms

4. crash后线程写入的日志可能丢失

   策略是尽可能收集日志，所以crash后仍然允许写入日志。

   可以通过增加标志位，crash后调用日志函数直接返回错误，不再接受新的日志。

5. ​

   ​

# Linux日志性能优化

   8线程，1M次每线程，release

1. 线程本地`vector<array<char,256>> v（10000）`，循环使用 50ms
2. 线程本地`vector<array<char,256>> v`，每次追加 250-300ms
3. 线程本地`vector<array<char,256>> v`，每次加锁追加 300-400ms
4. 不加锁追加到日志容器 500-600ms，无写入线程
5. 不加锁追加，提前获取到日志容器引用 250-350ms，无写入线程
6. 提前获取到锁及容器引用，无写入线程，300-500ms
7. 获取锁及引用，写入线程500ms swap，300-550ms
8. 获取锁及引用，写入线程10ms swap，300-700ms
9. 获取锁及引用，实际写入，linux 500-700ms, windows 350-450ms

```

```



