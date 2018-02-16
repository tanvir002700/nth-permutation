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

int * frequency(char * str)
{
    int * freq = (int *) calloc(257, sizeof(int));
    for(int i=0; str[i]; i++)
    {
        freq[str[i]]++;
    }
    return freq;
}

int number_of_permutation(long long int * factorial, int * freq, int len)
{
    long long int fact = factorial[len];
    fprintf(stderr, "total permutation %d\n", fact);
    for(int i='a'; i<'c'; i++)
    {
        fprintf(stderr, "frequency %d\n", freq[i]);
        fact /= factorial[freq[i]];
    }
    return fact;
}

static VALUE permutation(VALUE self, VALUE nth)
{
    struct Str * str;
    Data_Get_Struct(self, struct Str, str);

    int * freq = (int *) calloc(257, sizeof(int));
    memcpy(freq, str->frequency, 257*sizeof(int));

    fprintf(stderr, "before sending function %d\n", str->frequency['a']);
    fprintf(stderr, "before sending function %d\n", freq['a']);

    int p = number_of_permutation(str->factorial, freq, strlen(str->ptr));
    fprintf(stderr, "possible permutation %d\n", p);


    return Qtrue;
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
    str->frequency = frequency(str->ptr);

    for(int i='a'; i<'z'; i++)fprintf(stderr, "%d\n", str->frequency[i]);

    rb_iv_set(self, "@str", rb_string);
    rb_iv_set(self, "@length", INT2NUM(RSTRING_LEN(rb_string)));

    return self;
}

void Init_permutation_string(VALUE mNthPermutation)
{
    VALUE cPermutationString = rb_define_class_under(mNthPermutation, "String", rb_cObject);

    rb_define_alloc_func(cPermutationString, allocate);
    rb_define_method(cPermutationString, "initialize", initialize, 1);
    rb_define_method(cPermutationString, "permutation", permutation, 1);
    rb_define_attr(cPermutationString, "str", 1, 0);
    rb_define_attr(cPermutationString, "length", 1, 0);
}

