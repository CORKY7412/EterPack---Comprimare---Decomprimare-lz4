@echo off
@regedit.exe /S "%~dp0\EterPack_Pack.del.reg"
@regedit.exe /S "%~dp0\EterPack_Unpack.del.reg"
@echo EterPack uninstalled
@pause
