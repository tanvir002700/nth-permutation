#include<ruby.h>
#include<string.h>

struct Str
{
    long long int * factorial;
    int * frequency;
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
    str->factorial = NULL;
    str->frequency = NULL;

    return obj;
}

int * factorial()
{
    long long int * fact = (long long int *) calloc(21, sizeof(long long int));

    fact[0] = 1;

    for(int i=1; i<21; i++)
    {
        fact[i] = fact[i-1] * i;
    }

    return fact;
}

static VALUE initialize(VALUE self, VALUE rb_string)
{
    struct Str * str;
    long long int * fact;

    Check_Type(rb_string, T_STRING);
    Data_Get_Struct(self, struct Str, str);

    str->ptr = calloc(RSTRING_LEN(rb_string) + 1 , sizeof(char));
    memcpy(str->ptr, StringValuePtr(rb_string), RSTRING_LEN(rb_string));

    str->factorial = factorial();

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
