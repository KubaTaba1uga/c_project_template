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
CMOCK_CONFIG = os.environ.get("CMOCK_CONFIG", "./cmock_config.yaml")

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


def get_mock_name(source_file):
    return "mock_" + os.path.basename(src_file)


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
all_objs = []
if not os.path.exists(CMOCK_DIR):
    download_cmock()

test_paths = Glob(f"{TEST_OBJ_DIR}/*.c")
test_paths.extend(Glob(f"{TEST_OBJ_DIR}/**/*.c"))


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
test_files = [filename for filename in glob(f"{TEST_DIR}/**/test_*.c", recursive=True)]
src_files = list(glob(f"{SRC_DIR}/**/*.c", recursive=True)) + list(
    glob(f"{SRC_DIR}/**/*.h", recursive=True)
)


files_to_mock = set()
# Find files to mock
for test_file in test_files:
    test_includes = find_includes(test_file)

    # Find corresponding src file
    for src_file in src_files:
        src_file_mock = get_mock_name(src_file)
        if src_file_mock in test_includes:
            files_to_mock.add(src_file)

mocks = {}
# Build mocks
for src_file in files_to_mock:
    mock = get_mock_name(src_file)
    mock_src = os.path.join(TEST_MOCKS_DIR, mock).replace(".h", ".c")
    mock_obj = os.path.join(TEST_OBJ_DIR, mock.replace(".c", ".o").replace(".h", ".o"))

    all_objs.append(
        mock_src_ := test.Command(
            mock_src,
            src_file,
            f"CMOCK_DIR={CMOCK_DIR} CMOCK_CONFIG={CMOCK_CONFIG} ruby "
            + os.path.join(SCRIPTS_DIR, "create_mock.rb")
            + f" {src_file} --silent",
        )
    )
    all_objs.append(
        mock_obj_ := test.Object(
            mock_obj,
            mock_src,
            CPPPATH=[
                TEST_MOCKS_DIR,
                SRC_DIR,
                UNITY_SRC,
                CMOCK_SRC,
            ],
        )
    )


# Build test suits
for test_source in test_files:
    test_module_name, _ = os.path.splitext(os.path.basename(test_source))
    module_name = test_module_name.replace("test_", "")
    test_obj = os.path.join(TEST_OBJ_DIR, f"test_{module_name}.o")
    runner_source = os.path.join(TEST_RUNNERS_DIR, f"runner_{module_name}.c")
    runner_obj = os.path.join(TEST_OBJ_DIR, f"runner_{module_name}.o")
    test_bin = os.path.join(TEST_BUILD_DIR, test_module_name)

    # Create runners
    all_objs.append(
        runner_command := test.Command(
            runner_source,
            test_source,
            [
                "UNITY_DIR=${UNITY_DIR} ruby ${CMOCK_DIR}/scripts/create_runner.rb"
                + f" {test_source} {runner_source} --silent",
            ],
        )
    )

    # Build runners
    all_objs.append(
        runner_obj := test.Object(
            runner_obj,
            runner_source,
            CPPPATH=[SRC_DIR, UNITY_SRC, CMOCK_SRC, TEST_MOCKS_DIR],
        )
    )

    # Build test suite
    all_objs.append(
        test_obj_ := test.Object(
            test_obj,
            test_source,
            CPPPATH=[SRC_DIR, UNITY_SRC, CMOCK_SRC, TEST_MOCKS_DIR],
        )
    )

    test_includes = find_includes(test_source)
    mocked_files = [
        os.path.join(TEST_OBJ_DIR, include.replace(".h", ".o").replace(".c", ".o"))
        for include in test_includes
        if include.startswith("mock_")
    ]

    # Build test executable
    test_objs = [test_obj, runner_obj, unity, cmock]
    if mocked_files:
        test_objs.extend(mocked_files)

    all_objs.append(test.Program(test_bin, test_objs))

    # test_paths.extend(test_objs)
    # headers_to_link = set()

    # for include in test_includes:


test_conf.Finish()
