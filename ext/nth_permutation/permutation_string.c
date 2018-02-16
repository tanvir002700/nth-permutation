#include<ruby.h>
#include<string.h>

struct Str
{
    long long int * factorial;
    int * frequency;
    char *ptr;
    int len;
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
    str->len = 0;
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

static VALUE permutation(VALUE self, VALUE rb_nth)
{
    struct Str * str;
    Data_Get_Struct(self, struct Str, str);

    int nth = FIX2INT(rb_nth);

    int * freq = (int *) calloc(257, sizeof(int));
    memcpy(freq, str->frequency, 257*sizeof(int));

    int len = strlen(str->ptr);

    while(len)
    {
        long long upto = 0;
        for(int i=0; i<257; i++)
        {
            if(!freq[i])continue;
            freq[i] -= 1;
            long long int now_permutation = number_of_permutation(str->factorial, freq, str->len);
            if(upto + now_permutation >= nth)
            {
                nth -= upto;
                fprintf(stderr, "%c\n", (char)i);
                len--;
                break;
            }
            else
            {
                upto += now_permutation;
                freq[i]+=i;
            }
        }
    }

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
    str->len = strlen(str->ptr);

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

