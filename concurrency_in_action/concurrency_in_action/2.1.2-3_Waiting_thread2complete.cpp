#include <thread>
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

void f_2_1_0() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		//do_something_in_current_thread();
	}
	catch (const std::exception&)
	{
		t.join();
		throw;
	}
	t.join();
}

/*2.1.3*/
//RAII, Resource Acquisition Is Initialization
//清单 2.3 使用RAII等待线程完成
class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :t(t_) {};
	~thread_guard() {
		if (t.joinable()) 
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;

private:

};

void f_2_1() 
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	//do_something_in_current_thread();
	int index = 0;
	for (; index < 10000; index++) {
		index++;
	}
}

//int main() {
//
//	//f_2_1_0();
//	f_2_1();
//	return 0;
//}