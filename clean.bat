@echo Cleaning solution...
:: solution
del /s /q *.sdf > NUL
rd /s /q scripts\vs2010\ipch > NUL
:: scripts
del /s /q *.user > NUL
del /s /q *.log > NUL
:: cglib
del cglib\bin\Debug\cglib.lib
del cglib\bin\Release\cglib.lib
:: obj
del /s /q *.obj > NUL
del /s /q *.tlog > NUL
del /s /q *.lastbuildstate > NUL
del /s /q *.idb > NUL
del /s /q *.pdb > NUL
del /s /q *.manifest > NUL
del /s /q *.res > NUL
del /s /q *.rc > NUL
:: projects
del /s /q *.exe
del /s /q *.ilk
del /s /q *.unsuccessfulbuild
@echo Done.
pause