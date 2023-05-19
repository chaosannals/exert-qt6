# 第三方库

## botan Windows 下编译个 Qt

botan 现在已经出 3.x 版， qssh 使用了 2.x 版本。

```bash
# 执行配置生成 Qt mingw64 可用的 makefile
python configure.py --cpu=x86_64 --cc-bin=x86_64-w64-mingw32-g++ --ar-command=x86_64-w64-mingw32-ar
```

注：生成的 makefile 有问题。
./botan.dll 任务发被识别 要改成 .\botan.dll 再执行make。
windows 下需要配置 Qt 的编译环境，使用 mingw32-make 代替 make 命令，示例入下：

```bat
@echo off

set QT_BIN_DIR=D:\Qt\6.2.1\mingw81_64\bin
set QT_MINGW64_DIR=D:\Qt\Tools\mingw810_64\bin
set PATH=%QT_MINGW64_DIR%;%QT_BIN_DIR%;%PATH%

@echo on
mingw32-make
```