#include "SoLE.h"
enum Ch {EXIT, RESIZE, SOLVE, RANDOM, CHECK };
using namespace std;

int main() {
	Ch ch = RESIZE;
	int rank;
	bool doGeneration = true;
	bool doCheckCorrect = true;
	
	try {
		std::cout << "Set a size : \n"; std::cin >> rank;
		while (ch != EXIT)
		{
			if (rank < 1) throw std::exception("size shoud be greater than zero");
			system("cls");
			std::cout << "Select an option:\n";
			std::cout << "1.Resize the system of linear equasion.\n";
			std::cout << "2.Solve the system by Gause method.\n";
			std::cout << "3.Get a random matrix: "; doGeneration ? std::cout << "TRUE" : std::cout << "FALSE";
			std::cout << "\n4.Get a validation : "; doCheckCorrect ? std::cout << "TRUE" : std::cout << "FALSE";
			std::cout <<"\n0.Exit" << endl;
			scanf_s("%i", &ch);
			switch (ch)
			{
			case EXIT:
				break;
			case RESIZE:
			{
				std::cout << "Set a new size";
				std::cin >> rank;
				break;
			}
			case SOLVE:
			{
				SoLE a(rank, doGeneration);
				a.Gause(doCheckCorrect);
				break;
			}
			case RANDOM:
			{
				doGeneration = !doGeneration;
				break;
			}
			case CHECK:
			{
				doCheckCorrect = !doCheckCorrect;
				break;
			}
			default:
			{
				std::cout << "incorrect imput. Try again" << endl;
				break;
			}

			}
		}
	}
	catch (const std::exception& e)
	{
		cout << "Something go wrong :(\n" << e.what() << endl;
	}
}