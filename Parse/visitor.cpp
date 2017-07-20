#include "visitor.h"
std::function<int(int, int)> CalVisitor::getFunc(bin_op op) {
	std::function<int(int, int)> func;
	switch (op)
	{
	case bin_op::Plus:
		func = [](int a, int b) {return a + b; };
		break;
	case bin_op::Minus:
		func = [](int a, int b) {return a - b; };
		break;
	case bin_op::Multiplication:
		func = [](int a, int b) {return a * b; };
		break;
	case bin_op::Division:
		func = [](int a, int b) {return a / b; };
		break;
	}
	return func;
}