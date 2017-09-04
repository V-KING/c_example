## 本功能
1. 读取config文件中的ip的配置，并将配置文件读取到的信息放入一个struct
net_parameter结构体，
2. 配置文件中的配置可以随意调换顺序

对ip地址的配置文件的解析处理

## 万能配置文件读取
到对任何配置文件的处理的方法如下：
1. 在read_config_file.h 中,修改或增加DataTypeEndef的类型
2. 对 struct net_parameter的定义做相应的修改，可能你的配置是不是ip的配置
3. 在matched_cfg_item函数中，返回值 要与 struct
INIFileFmtDef的变量数组(这里你可能自己定义了另一个数组)顺序相对应

## update部分v1.0：
1. 对配置文件config的匹配，之前是config文件的匹配必须严格按照顺序匹配，现在config中的顺序可以随意

