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

    command = f"{CD} {formatPath('../src/assimp')};\n"
    command += f"{MKDIR} build;\n"
    command += f"{CD} build;\n"
    command += "cmake .. -G \"Unix Makefiles\" -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_SHARED_LIBS=ON -DASSIMP_NO_EXPORT=OFF -DASSIMP_BUILD_TESTS=OFF;\n"
    command += "make all;\n"
    command += f"{COPY} -r {formatPath('../include/assimp')} {formatPath('../../../include/assimp')};\n"
    command += f"{COPY} {formatPath('./include/assimp/config.h')} {formatPath('../../../include/assimp/config.h')}\n"
    command += f"{COPY} {formatPath('./bin/*.so')} {formatPath('../../../lib/')};\n"

    os.system(command)

if __name__ == "__main__":
    init()
    build()
