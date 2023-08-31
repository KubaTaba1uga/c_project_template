cmock_subproject = subproject('cmock')

unity_dependency = cmock_subproject.get_variable('unity_dep')
cmock_dependency = cmock_subproject.get_variable('cmock_dep')

mock_script = find_program('../scripts/create_mock.rb')

cmock_gen_runner = generator(
  find_program('../scripts/create_runner.rb'),
  output: '@BASENAME@_Runner.c',
  arguments: ['@INPUT@', '@OUTPUT@'],
)

cmock_gen_mock = generator(
   find_program('../scripts/create_mock.rb'),
   output: ['mock_@BASENAME@.c', 'mock_@BASENAME@.h', '@PLAINNAME@'],
   arguments: ['@INPUT@', '@BUILD_DIR@'],
)

root = join_paths('..', root)

subdir('test_gardener.d')
subdir('test_cmock.d')
subdir('test_main.d')

#gen_mock = generator(
#  find_program('../subprojects/cmock/scripts/create_mock.rb'),
#  output: '@BASENAME@_mock.c',
#  arguments: ['@INPUT@', '@OUTPUT@'],
#)
 

#test_gardener = executable('test_gardener')
