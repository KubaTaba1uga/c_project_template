# Template for new C projects
# ******************************************************************************
# *    App
# ******************************************************************************
project('c_project_template', 'c',
         version: '0.0.1',
	 meson_version: '>=1.0.1',
	 default_options: [
            'werror=true',
            'c_std=c11'
         ]
)



subdir('src')


# ******************************************************************************
# *    Logging
# ******************************************************************************
cmake = import('cmake')

logging_proj = cmake.subproject('stumpless')
logging_dep = logging_proj.dependency('stumpless')


main = executable('main', sources, dependencies: [logging_dep])

# ******************************************************************************
# *    Tests
# ******************************************************************************
subdir('test')
