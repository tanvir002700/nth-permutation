#include<ruby.h>
#include<permutation_string.h>

VALUE test()
{
    return rb_str_new2("test method");
}

void Init_nth_permutation()
{
    VALUE mNthPermutation = rb_define_module("NthPermutation");
    rb_define_singleton_method(mNthPermutation, "test", test, 0);
    Init_permutation_string(mNthPermutation);
}
