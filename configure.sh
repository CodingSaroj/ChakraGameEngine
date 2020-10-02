#!/bin/bash
cd external/projectfiles

python3 glm.py
python3 yaml-cpp.py
python3 SPIRV-Cross.py

cd ../../

premake5 gmake2
