#include <thread>
#include <stdexcept>
#include <vector>

//清单2.6 scoped_thread的用法
class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :
		t(std::move(t_))
	{
		if (!t.joinable())
			throw std::logic_error("No thread");
	}

	~scoped_thread()
	{
		t.join();
	}

	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator = (scoped_thread const&) = delete;
};

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

void f_2_3_0()
{
	int some_local_state;
	scoped_thread t(std::thread(func(some_local_state)));
	//do_something_in_current_thread();
}

#include <iostream>
//清单2.7量产线程，等待它们结束
void do_work(unsigned id) {
	while (id < 200) {
		id++;
		std::cout << "id=" << id;
	}
}

#include <algorithm>    // std::for_each
#include <functional>
void f_2_3()
{
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; i++)
	{
		threads.push_back(std::thread(do_work, i));//产生线程
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));//对每个线程调用join()

}

int main() {
	f_2_3();

	return 0;
}

