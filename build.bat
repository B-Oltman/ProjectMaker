@echo off

set CommonCompilerFlags=-MTd -nologo -Gm- -GR- -EHa- -Od -WX -W4 -wd4201 -wd4100 -wd4189 -wd4996 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref 

REM TODO - can we just build both with one exe?

IF NOT EXIST .\build mkdir .\build
pushd .\build

cl %CommonCompilerFlags% ..\code\project_maker.cpp /link  %CommonLinkerFlags%

popd
