@echo off
if '%1'=='' goto ERROR
cd \uc2
copy resource.h %1
copy uc2.aps %1
copy uc2.clw %1
copy uc2.ncb %1
copy uc2.opt %1
copy uc2.plg %1
copy uc2.rc %1
echo Files Copy OK!
goto END
:ERROR
echo Specify the directory to save resource template files
echo ex) %0 l.Eng
:END