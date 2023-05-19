# [exert-qt6](https://github.com/chaosannals/exert-qt6)

```pro
# QT *.pro 设置兼容 xp 编译。
win32 {
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
    QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01

    DEFINES += _ATL_XP_TARGETING
}
```

[QScintilla](https://riverbankcomputing.com/software/qscintilla/download)


## 打包

```bat
@Rem 需要 Qt 的命令环境，同时需要生成的 exe 文件。
windeployqt your_project.exe
```