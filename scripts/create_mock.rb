require "#{ENV['CMOCK_DIR']}/lib/cmock"


raise 'Header file to mock must be specified!' unless ARGV.length >= 1

cmock_config = ENV.fetch('CMOCK_CONFIG', './config.yaml')

cmock = CMock.new(cmock_config)
cmock.setup_mocks(ARGV[0])
