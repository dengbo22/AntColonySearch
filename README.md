# AntColonySearch
Ant Colony Research before Master Degree. 2015.7.5

2015.7.5:首次尝试提交，代码运行正常，但是仍有BUG。

2015.7.6:代码修改完成，BUG已经解决，能够在Ubuntu上顺利运行。


2015.7.11:代码大体无BUG，已经可以在随机起点的状态下运行
NewTSP类：
	将起点城市作为参数的函数均修改成不需要参数的函数
Ant类：
	将起点城市作为参数的函数均修改成不需要参数的函数
	重载“=”操作符
	创建SplitPath函数用于对结果进行分割并将结果保存在m_dbSplitLength中

Main文件：
	新建全局变量g_nCenterCity表示中心城市

新建Helper类用于进行一系列操作（暂时只有随机数生成)


2015.7.12:代码整体运行正常，已经经过一次稳定性调校
接下来计划进行信息素调校


