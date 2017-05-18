#include <ctest.h>
#include <output.c>

CTEST(output_string, message_1)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"/rus house\"}";
    char expected[] = "здание";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_2)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"/eng курица\"}";
    char expected[] = "hen";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_3)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"/start_eng\"}";
    char expected[] = "Игра(в стадии разработки)";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_4)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"Hello\"}";
    char expected[] = "Hello";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_5)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"Привет\"}";
    char expected[] = "Привет";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_6)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"Что происходит?\"}";
    char expected[] = "Что происходит?";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_7)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"What you doing?\"}";
    char expected[] = "What you doing?";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_8)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"/start\"}";
    char expected[] = "Привет, меня зовут Арнольд и меня не отпускают из квартиры, они дали мне телефон, кормят меня чёрной икрой и заставляют отвечать каждому на сообщения.\n Они разрешили мне выполнять только эти команды:\n\n1. /start\n2. /rus <english word>\n3. /eng <русское слово>\n4. /start_eng\n Я конечно не против этой работы, а сказал это просто так, чтобы ты знал.\n";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}