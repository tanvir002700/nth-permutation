#include<ruby.h>

VALUE test()
{
    return rb_str_new2("test method");
}

void Init_nth_permutation()
{
    VALUE mNthPermutation = rb_define_module("NthPermutation");
    rb_define_singleton_method(mNthPermutation, "test", test, 0);
}
