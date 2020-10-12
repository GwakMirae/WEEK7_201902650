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
/*(실습 1-1) 분석결과 : 
* main()에서 funcA()를 호출하면 funcA()함수가 실행된다.
* 'A'라는 id_를 가지는 Test 객체가 생성되고 funcB()가 호출되어 funcB()함수가 실행된다.
* funcB()함수에서는 'B'라는 id_를 가지는 Test객체가 생성되고 주석처리 되어있기 때문에 error가 발생하지 않는다.
* 따라서 "Executed in B"가 출력되고 함수가 끝났기 때문에 'B'에 대한 destructor가 호출된다.
* "Destructor execution: B"가 출력되며 funcB를 호출했던 funcA로 돌아가게 된다.
* funcA의 funcB호출이후 코드가 실행되고 "Executed in A"가 출력되며 함수가 끝난다.
* 역시 함수가 끝났으므로 함수내에서 만들었던 객체 'A'에 대해 destructor가 호출되어 "Destructor execution: A"가 출력된다.
* 이후 main()함수로 복귀하게 되고 프로그램이 종료된다.
*/

/*(실습 1-2) 분석결과 : 
* main()에서 funcA()를 호출하면 funcA()함수가 실행된다.
* 'A'라는 id_를 가지는 Test 객체가 생성되고 funcB()가 호출되어 funcB()함수가 실행된다.
* funcB()함수에서는 'B'라는 id_를 가지는 Test객체가 생성되고 runtime_error라는 오류 객체가 생성되고 throw된다.
* funcA()함수는 main()에서 try문안에 쓰여있고 현재 funcB에서 오류가 발생했기 때문에 
* exception타입을 받는 catch문에 의해서 catch되고 매개변수 e로 받아들여져 해당 Exception이 출력된다.
* stack unwinding에 의해 예외가 발생하면 예외가 발생하지 않을 때처럼 정상적인 흐름으로 차례대로 return 되지 않고
* stack에서 해당 exception handler가 있는 곳으로 바로 복귀하게 된다. 
* 하지만 funcA와 funcB함수 모두 함수가 종료되었으므로 destructor는 실행된다.
*/