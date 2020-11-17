#include <thread>
#include <stdexcept>
#include <vector>

//�嵥2.6 scoped_thread���÷�
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
			//do_something(i);           // 1. Ǳ�ڷ�����������������
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
//�嵥2.7�����̣߳��ȴ����ǽ���
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
		threads.push_back(std::thread(do_work, i));//�����߳�
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));//��ÿ���̵߳���join()

}

int main() {
	f_2_3();

	return 0;
}

