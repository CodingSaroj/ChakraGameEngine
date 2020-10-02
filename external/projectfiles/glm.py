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

    command = f"{COPY} -r {formatPath('../src/glm/glm')} {formatPath('../include/glm')};\n"

    os.system(command)

if __name__ == "__main__":
    init()
    build()
