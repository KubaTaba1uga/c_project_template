root = join_paths('..', root)
src = join_paths(root, 'src')

test_gardener_name = 'test_gardener.c'

test_gardener_src = files([src / 'gardener.h', src / 'gardener.c',  test_gardener_name])

test_gardener_exe = executable('test_gardener',
  sources: [
   test_gardener_src,
   cmock_gen_runner.process(test_gardener_name),
   cmock_gen_mock.process(src / 'utils' / 'std_lib_utils.h')        
  ],
  include_directories: [src, src / 'utils'],
  dependencies: [ unity_dependency, cmock_dependency ],
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ]
)

test('test gardener.c', test_gardener_exe)
