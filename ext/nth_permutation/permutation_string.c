#include<ruby.h>
#include<string.h>

const int CHACARTERS = 257;
const int LIMIT = 21;

struct Str
{
    long long int * factorial;
    long long int possible_permutation;
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
    str->possible_permutation = 0;
    return obj;
}

int * factorial()
{
    long long int * fact = (long long int *) calloc(LIMIT, sizeof(long long int));

    fact[0] = 1;
    for(int i=1; i<LIMIT; i++) fact[i] = fact[i-1] * i;

    return fact;
}

int * frequency(char * str)
{
    int * freq = (int *) calloc(CHACARTERS, sizeof(int));
    for(int i=0; str[i]; i++) freq[str[i]]++;
    return freq;
}

long long int number_of_permutation(const long long int * factorial, const int * freq, int len)
{
    long long int fact = factorial[len];
    for(int i=0; i<CHACARTERS; i++) fact /= factorial[freq[i]];
    return fact;
}

static VALUE permutation(VALUE self, VALUE rb_nth)
{
    struct Str * str;
    Data_Get_Struct(self, struct Str, str);

    Check_Type(rb_nth, T_FIXNUM);
    int nth = FIX2INT(rb_nth);
    if(nth > str->possible_permutation) rb_raise(rb_eRangeError, "there's no such nth permutation.");

    int * freq = (int *) calloc(CHACARTERS, sizeof(int));
    memcpy(freq, str->frequency, CHACARTERS*sizeof(int));

    int len = strlen(str->ptr);

    char * nth_permutation = (char *) calloc(len + 1, sizeof(char));
    int indx = 0;

    while(len)
    {
        long long upto = 0;
        for(int i='a'; i<'z'; i++)
        {
            if(!freq[i])continue;
            freq[i] -= 1;

            long long int now_permutation = number_of_permutation(str->factorial, freq, len-1);
            if(upto + now_permutation >= nth)
            {
                nth -= upto;
                nth_permutation[indx++] = (char) i;
                len--;
                break;
            }
            else
            {
                upto += now_permutation;
                freq[i] += 1;
            }
        }
    }
    nth_permutation[str->len] = NULL;

    free(freq);

    return rb_str_new2(nth_permutation);
}

static VALUE initialize(VALUE self, VALUE rb_string)
{
    struct Str * str;

    Check_Type(rb_string, T_STRING);
    if(RSTRING_LEN(rb_string) >= LIMIT) rb_raise(rb_eRangeError, "can't handle more than 20 character length string");
    Data_Get_Struct(self, struct Str, str);

    str->ptr = calloc(RSTRING_LEN(rb_string) + 1 , sizeof(char));
    memcpy(str->ptr, StringValuePtr(rb_string), RSTRING_LEN(rb_string));

    str->len = strlen(str->ptr);
    str->factorial = factorial();
    str->frequency = frequency(str->ptr);
    str->possible_permutation = number_of_permutation(str->factorial, str->frequency, str->len);

    rb_iv_set(self, "@str", rb_string);
    rb_iv_set(self, "@length", INT2NUM(RSTRING_LEN(rb_string)));
    rb_iv_set(self, "@possible_permutation", INT2NUM(str->possible_permutation));

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
    rb_define_attr(cPermutationString, "possible_permutation", 1, 0);
}

