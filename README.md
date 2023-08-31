# ncnn_face_rec

## 功能

本系统完成了通过ncnn实现了人脸检测及人脸识别，并实现将人脸编码结果通过POST请求发送到服务器。

## 编译及运行环境

| 软件     | 描述  |
| -------- | ----- |
| 系统     | MacOS |
| IDE      | Clion |
| GUI      | QT5   |
| 构建工具 | cmake |

## 如何编译

1. 拉取第三方子仓库

```bash
git submodue update --init
```

2. 执行编译脚本

```bash
bash ./build.sh
```

## 如何运行

```bash
./build/bin/edge-face-recognize
```

