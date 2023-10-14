### What is j2?
**j2**是一个UE中可以通过Console快速定位到ContentBrower中目录或资源的工具，无需逐级手动点选目录，通过命令直接跳转。

![](https://img.imzlp.com/imgs/zlp/picgo/2023/202310141101261.gif)

### Usage

插件提供了一个名为`j2`(jump to)的命令，利用Console唤起（\`键）：

参数可以传递目录：

```bash
j2 /Game/StarterContent/Maps
```

![](https://img.imzlp.com/imgs/zlp/picgo/2023/202310141046188.png)

或者资源路径：

```basg
j2 /Game/StarterContent/Textures/T_Concrete_Panels_N
```
并且能够支持ContentBrowser中对资源进行Copy Reference的路径：

```bash
j2 /Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Concrete_Panels_N.T_Concrete_Panels_N'
```

当检测到传递的参数是资源路径，就会跳转到它所在目录下，并选中该资源。

![](https://img.imzlp.com/imgs/zlp/picgo/2023/202310141047884.png)

### History
由于是基于Console实现的，所以它天然能够保存执行的历史，实现在历史记录中快速切换：

![](https://img.imzlp.com/imgs/zlp/picgo/2023/202310141053939.png)

注：Console的执行历史记录在`[PROJECT_DIR]/Saved/Config/ConsoleHistory.ini`中。

```ini
[ConsoleHistory]
History=j2 /Game/StarterContent/Maps
History=j2 /Game/StarterContent/Textures/T_Concrete_Panels_N
History=j2 /Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Concrete_Panels_N.T_Concrete_Panels_N'
History=j2 /Game
```
