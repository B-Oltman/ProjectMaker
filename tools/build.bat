@echo off

set CommonCompilerFlags=-MTd -nologo -Gm- -GR- -EHa- -Od -WX -W4 -wd4201 -wd4100 -wd4189 -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref 

IF NOT EXIST .\build mkdir .\build
pushd .\build

cl %CommonCompilerFlags% ..\code\main.cpp /link  %CommonLinkerFlags%

popd
