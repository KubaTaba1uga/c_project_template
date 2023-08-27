# SCons configuration file

# *******************************************************************************
# *    IMPORTS
# ******************************************************************************
import os
import subprocess

# *******************************************************************************
# *    ENVIROMENT VARIABLES
# ******************************************************************************
SRC_DIR = os.environ.get("SRC_DIR", "./src")
BUILD_DIR = os.environ.get("BUILD_DIR", "./build")
PRODUCTION_BUILD_DIR = os.environ.get(
    "TEST_BUILD_DIR", os.path.join(BUILD_DIR, "./production")
)
TEST_BUILD_DIR = os.environ.get("TEST_BUILD_DIR", os.path.join(BUILD_DIR, "./test"))
CMOCK_DIR = os.environ.get("CMOCK_DIR", "./cmock")
CMOCK_SRC = os.path.join(CMOCK_DIR, "src")
UNITY_DIR = os.environ.get("UNITY_DIR", "./cmock/vendor/unity")
UNITY_SRC = os.path.join(UNITY_DIR, "src")

SCRIPTS_DIR = "./scripts"


# *******************************************************************************
# *    TEST SETUP FUNCTIONS
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


# *******************************************************************************
# *    SETUP
# ******************************************************************************
create_build_dir()
create_production_build_dir()
create_test_build_dir()

# *******************************************************************************
# *    CONFIGURE PRODUCTION BUILD
# ******************************************************************************
include_dirs = []

production = Environment(CPPPATH=include_dirs)
production_conf = Configure(production)

production.VariantDir(PRODUCTION_BUILD_DIR, SRC_DIR, duplicate=0)
production_paths = Glob(f"{PRODUCTION_BUILD_DIR}/*.c")
production_paths.extend(Glob(f"{PRODUCTION_BUILD_DIR}/**/*.c"))

production.Program(f"{PRODUCTION_BUILD_DIR}/main", production_paths)

production = production_conf.Finish()

# *******************************************************************************
# *    CONFIGURE TEST BUILD
# ******************************************************************************
test = Environment(CPPPATH=include_dirs)
test_conf = Configure(test)
production.VariantDir(TEST_BUILD_DIR, SRC_DIR, duplicate=0)

if not os.path.exists(CMOCK_DIR):
    download_cmock()

# Build Unity
unity = Object(
    os.path.join(TEST_BUILD_DIR, "unity.o"),
    os.path.join(UNITY_SRC, "unity.c"),
    CPPPATH=[UNITY_SRC],
)

# Build CMock
cmock = Object(
    os.path.join(TEST_BUILD_DIR, "cmock.o"),
    os.path.join(CMOCK_SRC, "cmock.c"),
    CPPPATH=[UNITY_SRC, CMOCK_SRC],
)

# production.VariantDir(TEST_BUILD_DIR, SRC_DIR, duplicate=0)

# print(env.Dump())
# print(all_paths)
