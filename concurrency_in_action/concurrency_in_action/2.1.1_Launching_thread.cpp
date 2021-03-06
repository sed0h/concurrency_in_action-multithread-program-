#include <thread>

class background_task {
public:
	void operator()()const 
	{
		/*do_something();
		do_something_else();*/
	}
};

//清单2.1
struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator() ()
	{
		for (unsigned j = 0; j < 1000000; ++j)
		{
			//do_something(i);           // 1. 潜在访问隐患：悬空引用
			i++;
		}
	}
};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	//my_thread.detach();			// 2. 不等待线程结束
									// 3. 新线程可能还在运行

	if (my_thread.joinable()) {
		my_thread.join();
	}
}