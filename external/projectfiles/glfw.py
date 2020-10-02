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

    command = f"{CD} {formatPath('../src/glfw')};\n"
    command += f"{MKDIR} build;\n"
    command += f"{CD} build;\n"
    command += "cmake .. -G \"Unix Makefiles\" -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF;\n"
    command += "make all;\n"
    command += f"{COPY} -r {formatPath('../include/GLFW')} {formatPath('../../../include/GLFW')};\n"
    command += f"{COPY} {formatPath('./src/*.a')} {formatPath('../../../lib/')};\n"
    command += f"{COPY} {formatPath('./src/*.lib')} {formatPath('../../../lib/')};\n"

    os.system(command)

if __name__ == "__main__":
    init()
    build()
