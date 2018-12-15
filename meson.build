project(
  'fizzbuzz',
  'c',
  version: '0.1.0',
  license: 'Apache-2.0',
  default_options: [
    'werror=true',
    'warning_level=3',
    'c_std=c89',
    'default_library=static'])

if get_option('default_library') == 'shared'
  defines = ['-DFZ_SHARED=1']
else
  defines = []
endif

fizzbuzz_defines = defines + ['-DFZ_IMPLEMENTATION=1']
fizzbuzz_includes = include_directories('include')

fizzbuzz = declare_dependency(
  link_with: library(
    'fizzbuzz',
    'src/fizzbuzz.c',
    include_directories: fizzbuzz_includes,
    c_args: fizzbuzz_defines),
  include_directories: fizzbuzz_includes)

fizzbuzz_exe = executable(
  'fizzbuzz',
  'src/main.c',
  dependencies: fizzbuzz,
  c_args: defines)
