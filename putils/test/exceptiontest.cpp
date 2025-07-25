#include "RuntimeLog.h"

using namespace std;

int add(int a, int b) {
    throw PUTILS_GENERAL_EXCEPTION("Hello world!", "no exception");
    return a + b;
}

void fun1() {
    try {
        add(1, 2);
    } PUTILS_CATCH_THROW_GENERAL
    return;
}

void fun2(const string& str) {
    try {
        fun1();
    } PUTILS_CATCH_THROW_GENERAL
}

int main() {
    try {
        fun2("Call first time.");
    } PUTILS_CATCH_LOG_GENERAL_ERROR

    fun2("Call second time.");
    return 0;
}
