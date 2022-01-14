@echo off
@copy /Y "%~dp0\EterPackConsole.exe" "c:\windows\system32\"
@regedit.exe /S "%~dp0\EterPack_Pack.add.reg"
@regedit.exe /S "%~dp0\EterPack_Unpack.add.reg"
@echo EterPack installed
@pause
