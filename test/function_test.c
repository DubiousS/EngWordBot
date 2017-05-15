#include <strings.h>
#include <function.h>
#include <ctest.h>

CTEST(arithmetic_suite, income_second_if_data_scmp_1)
{
    const int result = scmp("test", "test");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_scmp_2)
{
    const int result = scmp("tes", "test");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_scmp_3)
{
    const int result = scmp("test", "tes");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_4)
{
    const int result = scmp("1654654654", "9849889445465");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_5)
{
    const int result = scmp("1654654654", "1654654654");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_6)
{
    const int result = scmp("9849889445465", "9849889445465");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_7)
{
    const int result = scmp("asd*/-*/*--/asd", "asd*/-*/*--/asd");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_8)
{
    const int result = scmp("", "");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_9)
{
    const int result = scmp("a\n", "a\n");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_scmp_10)
{
    const int result = scmp("\0", "\0");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}

//slen

CTEST(arithmetic_suite, income_second_if_data_slen_1)
{
    const int result = slen("\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_2)
{
    const int result = slen("1\0");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_3)
{
    const int result = slen("as\0");
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_4)
{
    const int result = slen("789\0");
    const float expected = 3;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_5)
{
    const int result = slen("/*/*\0");
    const float expected = 4;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_6)
{
    const int result = slen("asd\0asd");
    const float expected = 3;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_7)
{
    const int result = slen("asd*\nasd\0");
    const float expected = 8;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_8)
{
    const int result = slen("\n-1\0");
    const float expected = 3;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_9)
{
    const int result = slen("\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_slen_10)
{
    const int result = slen("12345678910asertyuio*/123+-$^\0");
    const float expected = 29;
    ASSERT_EQUAL(expected, result);
}

//sspn ':', '*', '?', '"', '<', '>', '|'

CTEST(arithmetic_suite, income_second_if_data_sspn_1)
{
    const int result = sspn("asdasdasdasdasdasda\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_2)
{
    const int result = sspn(":\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_3)
{
    const int result = sspn("asd*sdasdasdasdasda\0");
    const float expected = 3;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_4)
{
    const int result = sspn("asda?dasdasdasdasda\0");
    const float expected = 4;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_5)
{
    const int result = sspn("asda\"dasdasdasdasda\0");
    const float expected = 4;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_6)
{
    const int result = sspn("asdasda<dasdasdasda\0");
    const float expected = 7;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_7)
{
    const int result = sspn("a>dasdasdasdasdasda\0");
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_8)
{
    const int result = sspn("as|asdasdasdasdasda\0");
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_9)
{
    const int result = sspn("asd:/sdasdasdasdasda\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, income_second_if_data_sspn_10)
{
    const int result = sspn("asda()$!@$&_+='@)dasda\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}


//check
CTEST(arithmetic_suite, income_second_if_data_check_1)
{
    const int result = check("asdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdfasdaasdfdf\0");
    const float expected = -1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_check_2)
{
    const int result = check("asdasda<dasdasdasda\0");
    const float expected = 7;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_check_3)
{
    const int result = check("asdasdadasdasdasda\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_check_4)
{
    const int result = check("asdasda!@#$!@!#1231312312\0");
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_check_5)
{
    const int result = check("asda?dasdasdasdasda\0");
    const float expected = 4;
    ASSERT_EQUAL(expected, result);
}

//process
CTEST(arithmetic_suite, income_second_if_data_process_1)
{
    const int result = process("\0", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_2)
{
    const int result = process("asdasdas\0", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_3)
{
    const int result = process("\\192.168.10.2\\home\\openmpi\\mpicc.exe\0", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_4)
{
    const int result = process("my.ya.ru", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_5)
{
    const int result = process("http://my.ya.ru", NULL, NULL);
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_6)
{
    const int result = process("http://csc.sibsutis.ru", NULL, NULL);
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_7)
{
    const int result = process("http://10.ya.ru", NULL, NULL);
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_8)
{
    const int result = process("http://my.ya.eu", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_9)
{
    const int result = process("http://a.b.c.d.e.ru", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_10)
{
    const int result = process("http://a.b.c.ru/", NULL, NULL);
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_11)
{
    const int result = process("http://a.b.c.ru/asdasdasd/asd*", NULL, NULL);
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_12)
{
    const int result = process("http://.ru/asdasdasd/asd*", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_13)
{
    const int result = process("http://ru/", NULL, NULL);
    const float expected = 0;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_14)
{
    const int result = process("http://10.ya.ru/home/Open-MPI/MPicc-test.exe\0", NULL, NULL);
    const float expected = 1;
    ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic_suite, income_second_if_data_process_15)
{
    const int result = process("http://my.ya.ru/home/Open-MPI/MPicc-test.exe\0", NULL, NULL);
    const float expected = 2;
    ASSERT_EQUAL(expected, result);
}
