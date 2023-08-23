require "#{ENV['CMOCK_DIR']}/lib/cmock"


raise 'Header file to mock must be specified!' unless ARGV.length >= 1

mock_out = ENV.fetch('MOCK_OUT', './build/test/mocks')
mock_prefix = ENV.fetch('MOCK_PREFIX', 'mock_')
cmock_config = ENV.fetch('CMOCK_CONFIG', './config.yaml')

cmock = CMock.new(cmock_config)
#cmock = CMock.new(:plugins => %i[ignore return_thru_ptr], :mock_prefix => mock_prefix, :mock_path => mock_out)
cmock.setup_mocks(ARGV[0])
