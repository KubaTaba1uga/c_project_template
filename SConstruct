# SCons configuration file

# *******************************************************************************
# *    IMPORTS
# ******************************************************************************
import os
import re
import subprocess
from glob import glob

# *******************************************************************************
# *    ENVIROMENT VARIABLES
# ******************************************************************************
SRC_DIR = os.environ.get("SRC_DIR", "./src")
BUILD_DIR = os.environ.get("BUILD_DIR", "./build")
TEST_DIR = os.environ.get("TEST_DIR", "./test")
PRODUCTION_BUILD_DIR = os.environ.get(
    "TEST_BUILD_DIR", os.path.join(BUILD_DIR, "./production")
)
PRODUCTION_OBJ_DIR = os.path.join(PRODUCTION_BUILD_DIR, "obj")
TEST_BUILD_DIR = os.environ.get("TEST_BUILD_DIR", os.path.join(BUILD_DIR, "test"))
TEST_OBJ_DIR = os.path.join(TEST_BUILD_DIR, "obj")
TEST_RUNNERS_DIR = os.path.join(TEST_BUILD_DIR, "runners")
TEST_MOCKS_DIR = os.path.join(TEST_BUILD_DIR, "mocks")

CMOCK_DIR = os.environ.get("CMOCK_DIR", "./cmock")
CMOCK_SRC = os.path.join(CMOCK_DIR, "src")
UNITY_DIR = os.environ.get("UNITY_DIR", "./cmock/vendor/unity")
UNITY_SRC = os.path.join(UNITY_DIR, "src")

SCRIPTS_DIR = "./scripts"


# *******************************************************************************
# *    FUNCTIONS
# ******************************************************************************
def download_cmock():
    installation_script = os.path.join(SCRIPTS_DIR, "install_cmock.sh")

    exit_code = subprocess.run([installation_script]).returncode

    if exit_code != 0:
        print(
            f"Cmock installation has failed. Try running {installation_script} manually."
        )
        exit(exit_code)


def create_build_dir():
    os.makedirs(BUILD_DIR, exist_ok=True)


def create_production_build_dir():
    os.makedirs(PRODUCTION_BUILD_DIR, exist_ok=True)


def create_test_build_dir():
    os.makedirs(PRODUCTION_BUILD_DIR, exist_ok=True)


def find_includes(source_file):
    includes = set()
    with open(source_file, "r") as fp:
        source_content = fp.read()

    for include in re.findall(r"#include (\S+)", source_content):
        sanitized_include = include.replace("<", "").replace(">", "").replace('"', "")
        includes.add(sanitized_include)

    return includes


# *******************************************************************************
# *    SETUP
# ******************************************************************************
# create_build_dir()
# create_production_build_dir()
# create_test_build_dir()

# *******************************************************************************
# *    CONFIGURE PRODUCTION BUILD
# ******************************************************************************
include_dirs = []

production = Environment(CPPPATH=include_dirs)
production_conf = Configure(production)

production.VariantDir(PRODUCTION_OBJ_DIR, SRC_DIR, duplicate=0)
production_paths = Glob(f"{PRODUCTION_OBJ_DIR}/*.c")
production_paths.extend(Glob(f"{PRODUCTION_OBJ_DIR}/**/*.c"))

production.Program(f"{PRODUCTION_BUILD_DIR}/main", production_paths)

production = production_conf.Finish()

# *******************************************************************************
# *    CONFIGURE TEST BUILD
# ******************************************************************************
test = Environment(CPPPATH=include_dirs)
test_conf = Configure(test)
test.VariantDir(TEST_OBJ_DIR, SRC_DIR, duplicate=0)
test["UNITY_DIR"] = UNITY_DIR
test["CMOCK_DIR"] = CMOCK_DIR
test["CCFLAGS"] += " -DTEST "
if not os.path.exists(CMOCK_DIR):
    download_cmock()

all_objs = []
# Build Unity
all_objs.append(
    unity := test.Object(
        os.path.join(TEST_OBJ_DIR, "unity.o"),
        os.path.join(UNITY_SRC, "unity.c"),
        CPPPATH=[UNITY_SRC],
        CCFLAGS="",
    )
)

# Build CMock
all_objs.append(
    cmock := test.Object(
        os.path.join(TEST_OBJ_DIR, "cmock.o"),
        os.path.join(CMOCK_SRC, "cmock.c"),
        CPPPATH=[UNITY_SRC, CMOCK_SRC],
        CCFLAGS="",
    )
)

# Prepare to build test
all_headers_to_mock, all_src_headers = set(), set()

test_sources = [
    filename for filename in glob(f"{TEST_DIR}/**/test_*.c", recursive=True)
]

for test_source in test_sources:
    module_name, _ = os.path.splitext(os.path.basename(test_source))
    test_obj = os.path.join(TEST_OBJ_DIR, f"test_{module_name}.o")
    runner_source = os.path.join(TEST_RUNNERS_DIR, f"runner_{module_name}.c")
    runner_obj = os.path.join(TEST_OBJ_DIR, f"runner_{module_name}.o")

    test_includes = find_includes(test_source)

    all_headers_to_mock.update(
        mocked_includes := [
            include for include in test_includes if include.startswith("mock_")
        ]
    )

    all_src_headers.update(
        src_includes := [
            include
            for include in test_includes
            if os.path.exists(os.path.join(SRC_DIR, include))
        ]
    )

    # Create runners
    all_objs.append(
        runner_command := test.Command(
            runner_source,
            test_source,
            [
                "UNITY_DIR=${UNITY_DIR} ruby ${CMOCK_DIR}/scripts/create_runner.rb"
                + f" {test_source} {runner_source}",
            ],
        )
    )

    # Build runners
    all_objs.append(
        runner_obj := test.Object(
            runner_obj,
            runner_source,
            CPPPATH=[UNITY_SRC, CMOCK_SRC, TEST_MOCKS_DIR],
        )
    )

    # Build test suite
    mock_objs = [os.path.join(TEST_MOCKS_DIR, include) for include in mocked_includes]
    # all_objs.append(
    #     test_suite_obj := test.Object(
    #         test_obj,
    #         [test_source, ]
    #     )
    # )

    from pprint import pprint

    print()
    pprint(mocked_includes)
    pprint(src_includes)
    print()

# Generate and build mocks
for mock_header in all_headers_to_mock:
    mock_src = os.path.join(TEST_MOCKS_DIR, mock_header.replace(".h", ".c"))
    mock_obj = os.path.join(TEST_OBJ_DIR, mock_header.replace(".h", ".o"))
# production.VariantDir(TEST_OBJ_DIR, SRC_DIR, duplicate=0)

test_conf.Finish()
# print(env.Dump())
# print(all_paths)
