#include <fizzbuzz.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_map {
  void *data;
  char const *(*func)(void *, char const *);
};

struct test_func_data {
  struct string_map next_to_call;
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
  struct string_map *call;
  char const *ret_of_call;

  (void)_s;

  tfdata = data;
  call = &tfdata->next_to_call;
  ret_of_call = call->func(call->data, "");
  return concat(tfdata->s, ret_of_call);
}

static struct string_map
test(int n, int d, char const *s, struct string_map f) {
  struct string_map ret;

  if (n % d == 0) {
    struct test_func_data *tfdata;

    tfdata = malloc(sizeof *tfdata);
    tfdata->next_to_call = f;
    tfdata->s = s;

    ret.data = tfdata;
    ret.func = test_func;
  } else {
    ret = f;
  }

  return ret;
}

static struct string_map
fizz(int n, struct string_map f) {
  return test(n, 3, "Fizz", f);
}

static struct string_map
buzz(int n, struct string_map f) {
  return test(n, 5, "Buzz", f);
}

static char const *
identity_func(void *data, char const *x) {
  (void)data;
  return x;
}

static struct string_map const identity = {NULL, identity_func};

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
  struct string_map tmp;

  tmp = buzz(n, identity);
  tmp = fizz(n, tmp);
  return tmp.func(tmp.data, string_of_int(n));
}
