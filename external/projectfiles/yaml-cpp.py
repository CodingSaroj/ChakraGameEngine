import os
import platform

CD = ""
MKDIR = ""
COPY = ""

def init():
    global CD
    global MKDIR
    global COPY

    if os.name == "nt":
        CD = "cd"
        MKDIR = "mkdir"
        COPY = "copy"
    elif os.name == "posix":
        CD = "cd"
        MKDIR = "mkdir"
        COPY = "cp"

def formatPath(path: str):
    if os.name == "nt":
        return path.replace("/", "\\")
    elif os.name == "posix":
        return path

def build():
    global CD
    global MKDIR
    global COPY

    command = f"{CD} {formatPath('../src/yaml-cpp')};\n"
    command += f"{MKDIR} build; {CD} build;\n"
    command += "cmake .. -G \"Unix Makefiles\" -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DYAML_BUILD_SHARED_LIBS=OFF;\n"
    command += "make yaml-cpp;\n"
    command += f"{COPY} -r {formatPath('../include/yaml-cpp')} {formatPath('../../../include/yaml-cpp')};\n"
    command += f"{COPY} {formatPath('./*.a')} {formatPath('../../../lib/')};\n"
    command += f"{COPY} {formatPath('./*.lib')} {formatPath('../../../lib/')};\n"

    os.system(command)

if __name__ == "__main__":
    init()
    build()
