@echo off

cl /LD src\TcpBridge.cpp /Fe:TcpBridge.dll ws2_32.lib

del + TcpBridge.lib
del + TcpBridge.exp
del + TcpBridge.obj
