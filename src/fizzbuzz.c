#include <fizzbuzz.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct thunk {
  void *data;
  char const *(*func)();
};

struct fizzbuzz_data {
  int n;
};

struct test_func_data {
  struct thunk next_to_call;
  char const *s;
};

static char *
concat(char const *s1, char const *s2) {
  unsigned size = 1;
  char *ret, *out;
  char const *in;

  size += (unsigned)strlen(s1);
  size += (unsigned)strlen(s2);
  out = ret = malloc(size);

  for (in = s1; *in; ++in, ++out) {
    *out = *in;
  }
  for (in = s2; *in; ++in, ++out) {
    *out = *in;
  }
  *out = 0;

  return ret;
}

static char const *
test_func(void *data, char const *_s) {
  struct test_func_data *tfdata;
  struct thunk *call;
  char const *ret_of_call;

  (void)_s;

  tfdata = data;
  call = &tfdata->next_to_call;
  ret_of_call = call->func(call->data, "");
  return concat(tfdata->s, ret_of_call);
}

static struct thunk
test(void *data, int d, char const *s, struct thunk f) {
  struct fizzbuzz_data *fzdata;
  struct thunk ret;

  fzdata = data;
  if (fzdata->n % d == 0)
    {
      struct test_func_data *tfdata;

      tfdata = malloc(sizeof *tfdata);
      tfdata->next_to_call = f;
      tfdata->s = s;

      ret.data = tfdata;
      ret.func = test_func;
    }
  else
    ret = f;

  return ret;
}

static char const *const fizz_str = "Fizz";
static char const *const buzz_str = "Buzz";

static struct thunk
fizz(void *data, struct thunk f) {
  return test(data, 3, fizz_str, f);
}

static struct thunk
buzz(void *data, struct thunk f) {
  return test(data, 5, buzz_str, f);
}

static char const *
identity_func(void *data, char const *x) {
  (void)data;
  return x;
}

static struct thunk const identity = {NULL, identity_func};

static char *
string_of_int(int n) {
  char *ret;

  ret = malloc(30); /* more than large enough for 32-bits */
  sprintf(ret, "%d", n);
  return ret;
}

FZ_EXPORT
char const *
fizzbuzz(int n) {
  struct fizzbuzz_data fzdata;
  struct thunk tmp;

  fzdata.n = n;
  tmp = buzz(&fzdata, identity);
  tmp = fizz(&fzdata, tmp);
  return tmp.func(tmp.data, string_of_int(n));
}
