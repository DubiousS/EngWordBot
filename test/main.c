#define CTEST_MAIN
#define CTEST_COLOR_OK
#include <ctest.h>
#include <locale.h>

int main(int argc, const char** argv)
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
    return ctest_main(argc, argv);
}