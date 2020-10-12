#include <iostream>
#include <stdexcept>

class Test
{
public:
	Test(char id) : id_(id) {}
	~Test() {
		std::cout << "Destructor execution: " << id_ << std::endl;
	}

private:
	char id_;
};

int funcB() {
	Test r('B');
	throw std::runtime_error("Exception from funcB!\n");
	std::cout << "Executed in B" << std::endl;
	return 0;
}
int funcA() {
	Test r('A');
	funcB();
	std::cout << "Executed in A" << std::endl;
	return 0;
}
int main() {
	try {
		funcA();
	}
	catch(std::exception& e){
		std::cout << "Exception: " << e.what();
	}
}
/*(�ǽ� 1-1) �м���� : 
* main()���� funcA()�� ȣ���ϸ� funcA()�Լ��� ����ȴ�.
* 'A'��� id_�� ������ Test ��ü�� �����ǰ� funcB()�� ȣ��Ǿ� funcB()�Լ��� ����ȴ�.
* funcB()�Լ������� 'B'��� id_�� ������ Test��ü�� �����ǰ� �ּ�ó�� �Ǿ��ֱ� ������ error�� �߻����� �ʴ´�.
* ���� "Executed in B"�� ��µǰ� �Լ��� ������ ������ 'B'�� ���� destructor�� ȣ��ȴ�.
* "Destructor execution: B"�� ��µǸ� funcB�� ȣ���ߴ� funcA�� ���ư��� �ȴ�.
* funcA�� funcBȣ������ �ڵ尡 ����ǰ� "Executed in A"�� ��µǸ� �Լ��� ������.
* ���� �Լ��� �������Ƿ� �Լ������� ������� ��ü 'A'�� ���� destructor�� ȣ��Ǿ� "Destructor execution: A"�� ��µȴ�.
* ���� main()�Լ��� �����ϰ� �ǰ� ���α׷��� ����ȴ�.
*/

/*(�ǽ� 1-2) �м���� : 
* main()���� funcA()�� ȣ���ϸ� funcA()�Լ��� ����ȴ�.
* 'A'��� id_�� ������ Test ��ü�� �����ǰ� funcB()�� ȣ��Ǿ� funcB()�Լ��� ����ȴ�.
* funcB()�Լ������� 'B'��� id_�� ������ Test��ü�� �����ǰ� runtime_error��� ���� ��ü�� �����ǰ� throw�ȴ�.
* funcA()�Լ��� main()���� try���ȿ� �����ְ� ���� funcB���� ������ �߻��߱� ������ 
* exceptionŸ���� �޴� catch���� ���ؼ� catch�ǰ� �Ű����� e�� �޾Ƶ鿩�� �ش� Exception�� ��µȴ�.
* stack unwinding�� ���� ���ܰ� �߻��ϸ� ���ܰ� �߻����� ���� ��ó�� �������� �帧���� ���ʴ�� return ���� �ʰ�
* stack���� �ش� exception handler�� �ִ� ������ �ٷ� �����ϰ� �ȴ�. 
* ������ funcA�� funcB�Լ� ��� �Լ��� ����Ǿ����Ƿ� destructor�� ����ȴ�.
*/