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

src='../src'
include = [src]
test_cmock_name = 'test_cmock.c'
test_gardener_name = 'test_gardener.c'

cmock_test_src = files([
  test_cmock_name
])

test_cmock_exe = executable('test_cmock',
  sources: [
   cmock_test_src,
   cmock_gen_runner.process(test_cmock_name)                   
  ],
  dependencies: [ unity_dependency ],
)



test_gardener_src = files(['../src/gardener.h','../src/gardener.c',    test_gardener_name])

test_gardener_exe = executable('test_gardener',
  sources: [
   test_gardener_src,
   cmock_gen_runner.process(test_gardener_name),
   cmock_gen_mock.process('../src/utils/std_lib_utils.h')        
  ],
  include_directories: [src, src/'utils'],
  dependencies: [ unity_dependency, cmock_dependency ],
)



#gen_mock = generator(
#  find_program('../subprojects/cmock/scripts/create_mock.rb'),
#  output: '@BASENAME@_mock.c',
#  arguments: ['@INPUT@', '@OUTPUT@'],
#)
 

#test_gardener = executable('test_gardener')
