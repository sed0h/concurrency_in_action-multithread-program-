#include <thread>

class background_task {
public:
	void operator()()const 
	{
		/*do_something();
		do_something_else();*/
	}
};

//�嵥2.1
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

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	//my_thread.detach();			// 2. ���ȴ��߳̽���
									// 3. ���߳̿��ܻ�������

	if (my_thread.joinable()) {
		my_thread.join();
	}
}