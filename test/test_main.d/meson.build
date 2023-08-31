src = join_paths(root, 'src')

test_main_name = 'test_main.c'

test_main_src = files([test_main_name, src/'main.c', src/'gardener.c', src/'utils'/'std_lib_utils.c'])

test_main_exe = executable('test_main',
  sources: [
    test_main_src,
    cmock_gen_runner.process(test_main_name),
  ],
  include_directories: [src, src/'utils'],
  dependencies: [ unity_dependency, cmock_dependency],
  c_args:['-DTEST'],
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ]
)

test('test main.c', test_main_exe)
