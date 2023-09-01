# C Project Template

Template for new c projects. Includes build system, test, mocking, readme, license. 

1. [Getting Started](#Getting-Started)
2. [Prerequisites](#Prerequisites)
3. [Building](#Building)
3. [Tests](#Tests)



## Getting Started

Clone project
```
git clone https://github.com/KubaTaba1uga/c_project_template.git <new project name>
```

Delete template git files
```
rm -rf <new project name>/.git
```

Initiate new git files
```
cd <new project name>
git init
```

Once you have initialized the repository, create a remote repository somewhere like GitHub.com.

Add the remote URL to your local git repository
```
git remote add origin <URL>
```

Commit at least one file

Push changes
```
git push -u origin master
```

I recommend installing perequesitest and confirming that all tests are passing before src/*, test/* are actually deleted.

Project's name or version can be changed in ./meson.build file.

## Prerequisites

Requirements for the software and other tools to build, test and push 
- [Meson](https://mesonbuild.com/)
- [Unity](https://github.com/ThrowTheSwitch/Unity)
- [Cmock](https://github.com/ThrowTheSwitch/CMock)

## Building

Debian 12 is only supported OS in installation scripts, if that's not the one You're using check out Perequesites to install them manually.   

Install perequesites
```
./scripts/install_ruby.sh
./scripts/install_meson.sh
```

Configure build for app and tests
```
meson setup build
```

Compile build config
```
meson compile -C build
```

## Tests

Run all tests
```
meson test -C build
```

### Style test

New tests units should be grouped by directories.
To understand more look on ./test directory.

## Authors

  - **Jakub Buczyński** - *C Project Template* -
    [KubaTaba1uga](https://github.com/KubaTaba1uga)

See also the list of
[contributors](https://github.com/PurpleBooth/a-good-readme-template/contributors)
who participated in this project.

## License

This project is licensed under the [CC0 1.0 Universal](LICENSE.md)
Creative Commons License - see the [LICENSE.md](LICENSE.md) file for
details

## Acknowledgments

  - Hat tip to anyone whose code is used
  - Inspiration
  - etc
