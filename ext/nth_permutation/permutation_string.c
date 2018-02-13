#include<ruby.h>
#include<string.h>

struct Str
{
    char *ptr;
};

static void deallocate(struct Str *str)
{
    free(str);
}

static VALUE allocate(VALUE klass)
{
    struct Str * str = (struct Str *)malloc(sizeof(struct Str));

    VALUE obj = Data_Make_Struct(klass, struct Str, NULL, deallocate, str);
    str->ptr = NULL;
    return obj;
}

static VALUE initialize(VALUE self, VALUE rb_string)
{
    struct Str * str;

    Check_Type(rb_string, T_STRING);
    Data_Get_Struct(self, struct Str, str);

    str->ptr = calloc(RSTRING_LEN(rb_string) + 1 , sizeof(char));
    memcpy(str->ptr, StringValuePtr(rb_string), RSTRING_LEN(rb_string));

    rb_iv_set(self, "@str", rb_string);
    rb_iv_set(self, "@length", INT2NUM(RSTRING_LEN(rb_string)));

    return self;
}

void Init_permutation_string(VALUE mNthPermutation)
{
    VALUE cPermutationString = rb_define_class_under(mNthPermutation, "String", rb_cObject);

    rb_define_alloc_func(cPermutationString, allocate);
    rb_define_method(cPermutationString, "initialize", initialize, 1);
    rb_define_attr(cPermutationString, "str", 1, 0);
    rb_define_attr(cPermutationString, "length", 1, 0);
}