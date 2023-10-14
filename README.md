## What is this?
这是一个UE中可以通过Console快速定位到ContentBrower中目录或资源的工具，无需逐级手动点选目录，直接跳转。

## Usage

插件提供了一个名为`j2`(jump to)的命令，可以传递目录或者资源路径：

```bash
j2 /Game/StarterContent/Maps
j2 /Game/StarterContent/Textures/T_Concrete_Panels_N
```

并且能够支持ContentBrowser中对资源进行Copy Reference的路径：

```bash
j2 /Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Concrete_Panels_N.T_Concrete_Panels_N'
```
就会跳转到该目录下，并选中该资源。
