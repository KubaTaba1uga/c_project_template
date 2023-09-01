# C Project Template

Template for new c projects. Includes build system, test, mocking, readme, license. 

1. [Getting Started](#Getting-Started)
2. [Prerequisites](#Prerequisites)
3. [Building](#Building)
4. [Tests](#Tests)
5. [Authors](#Authors)
6. [License](#License)



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
- [Meson](https://mesonbuild.com/)
- [Ruby](https://www.ruby-lang.org/en/)

Ruby is used by CMock.

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

Hierarchial build is very favoured by Meson, splitting test unit's into seperate directories allow keeping meson.builds short and simple.

## Authors

  - **Jakub Buczyński** - *C Project Template* -
    [KubaTaba1uga](https://github.com/KubaTaba1uga)

## License

This project is licensed under the [MIT](LICENSE.md)
License - see the [LICENSE.md](LICENSE.md) file for
details
