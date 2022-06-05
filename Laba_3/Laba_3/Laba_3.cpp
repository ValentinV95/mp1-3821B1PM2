#include <iostream>
#include <windows.h>
#include "classes.h"
#include "menu.h"

void menu_init() {
	int choice_vec, choice_matrix;
	size_t size;
	std::cout << "Enter matrix size: ";
	std::cin >> size;
	matrix<double> sqr_matrix(size);
	vector<double> vec_right(size);

	std::cout << "Enter the vector:\n1) Random\n2) Manual" << std::endl;
	std::cout << "Choice - ";
tryagain_vec:
	std::cin >> choice_vec;
	std::cout << std::endl;
	switch (choice_vec) {
	case 1:
		vec_right.set_random();
		std::cout << "\t" << vec_right;
		break;
	case 2:
		vec_right.set_manual();
		std::cout << "\t" << vec_right;
		break;
	default:
		std::cout << "Enter again 1 or 2" << std::endl;
		goto tryagain_vec;
	}
	std::cout << std::endl;
	std::cout << "Enter matrix:\n1) Random\n2) Manual" << std::endl;
	std::cout << "Choice - ";
tryagain_matrix:
	std::cin >> choice_matrix;
	std::cout << std::endl;
	switch (choice_matrix) {
	case 1:
		sqr_matrix.set_random_matrix();
		std::cout << sqr_matrix;
		break;
	case 2:
		sqr_matrix.set_manual_matrix();
		std::cout << sqr_matrix;
		break;
	default:
		std::cout << "Enter again 1 or 2" << std::endl;
		goto tryagain_matrix;
	}

	int flag_show;
	std::cout << "Show system?\n1)yes\n2)no" << std::endl;
	std::cout << "Choice - ";
tryagain_flag:
	std::cin >> flag_show;
	std::cout << std::endl;
	switch (flag_show) {
	case 1:
		sqr_matrix.show_system(vec_right);
		break;
	case 2:
		std::cout << std::endl;
		break;
	default:
		std::cout << "Enter again 1 or 2" << std::endl;
		goto tryagain_flag;
	}
	sqr_matrix.triangle_lower(sqr_matrix, size, vec_right);
}