#include <iostream>
#include "time_wheel.h"


// 创建一个定时器
ngl::time_wheel g_wheel(ngl::time_wheel_config
	{
		.m_time_wheel_precision = 10,
		.m_time_wheel_bit = 8,
		.m_time_wheel_count = 4,
	});


int main()
{
	ngl::wheel_parm lparm
	{
		.m_ms = 1000,
		.m_intervalms = [](int64_t) {return 1000; } ,
		.m_count = 0x7fffffff,
		.m_fun = [](ngl::wheel_node* anode)
		{
			time(nullptr);
			std::cout << "[" << time(nullptr) << "]" << std::endl;
		}
	};
	g_wheel.addtimer(lparm);

	while (1)
	{
		ngl::sleep::seconds(1);
	}
	return 0;
}