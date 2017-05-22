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
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"Hello\"}";
    char expected[] = "Hello";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_4)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"Привет\"}";
    char expected[] = "Привет";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_5)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"Что происходит?\"}";
    char expected[] = "Что происходит?";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_6)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"What you doing?\"}";
    char expected[] = "What you doing?";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_7)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"/start\"}";
    char expected[] = "Привет, меня зовут Арнольд и меня не отпускают из квартиры, они дали мне телефон, кормят меня чёрной икрой и заставляют отвечать каждому на сообщения.\n Они разрешили мне выполнять только эти команды:\n\n1. /start\n2. /rus <english word>\n3. /eng <русское слово>\n4. /start_eng\n5. /random\n Я конечно не против этой работы, а сказал это просто так, чтобы ты знал.\n";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_8)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"текст маленькими буквами\"}";
    char expected[] = "текст маленькими буквами";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_9)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\"ТЕКСТ БОЛЬШИМИ БУКВАМИ\"}";
    char expected[] = "ТЕКСТ БОЛЬШИМИ БУКВАМИ";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, message_10)
{
    char body[] = "{\"asdasda\":\"asfasfasf\",\"text\":\",./!@#$^&*()-=_+|<>;:{}[]\"}";
    char expected[] = ",./!@#$^&*()-=_+|<>;:{}[]";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_1)
{
    char body[] = "{\"asbgfda\":\"asfmovbjdsf\",\"text\":\"/rus airmail\"}";
    char expected[] = "авиапочта";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_2)
{
    char body[] = "{\"asdmiha\":\"asbkpokpuvf\",\"text\":\"/eng призывать\"}";
    char expected[] = "invoke";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_3)
{
    char body[] = "{\"asbgfda\":\"asfmovbjdsf\",\"text\":\"/rus plum\"}";
    char expected[] = "слива";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_4)
{
    char body[] = "{\"asdmiha\":\"asbkpokpuvf\",\"text\":\"/eng костюм\"}";
    char expected[] = "costume";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_5)
{
    char body[] = "{\"asbgfda\":\"asfmovbjdsf\",\"text\":\"/rus circle\"}";
    char expected[] = "круг, кружок, область, двигаться по кругу";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_6)
{
    char body[] = "{\"asdmiha\":\"asbkpokpuvf\",\"text\":\"/eng кто?\"}";
    char expected[] = "who";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_7)
{
    char body[] = "{\"asbgfda\":\"asfmovbjdsf\",\"text\":\"/rus league\"}";
    char expected[] = "лига";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_8)
{
    char body[] = "{\"asdmiha\":\"asbkpokpuvf\",\"text\":\"/eng манго\"}";
    char expected[] = "mango";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_9)
{
    char body[] = "{\"asbgfda\":\"asfmovbjdsf\",\"text\":\"/rus inspire\"}";
    char expected[] = "внушать";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}

CTEST(output_string, translate_10)
{
    char body[] = "{\"asdmiha\":\"asbkpokpuvf\",\"text\":\"/eng база данных\"}";
    char expected[] = "database";
    char msg[4096];
    output(body, msg);
    ASSERT_STR(expected, msg);
}