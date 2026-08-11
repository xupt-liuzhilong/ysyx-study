# 版本控制(Git)-学习总结

## 一、Git基础

Git是分布式版本控制系统，用于记录代码变化和管理项目版本。

核心区域：

-   工作区：实际编辑文件的位置
-   暂存区：准备提交的文件
-   本地仓库：保存提交历史
-   远程仓库：服务器上的代码仓库

## 二、基本操作

初始化：

``` bash
git init
```

查看状态：

``` bash
git status
```

添加：

``` bash
git add .
```

提交：

``` bash
git commit -m "message"
```

## 三、分支管理

创建分支：

``` bash
git branch dev
```

切换分支：

``` bash
git switch dev
```

合并：

``` bash
git switch master
git merge dev
```

## 四、冲突解决

当不同分支修改同一文件同一位置时会产生冲突。

解决流程：

1.  修改冲突文件
2.  git add 文件
3.  git commit

## 五、reset与revert

### git reset

用于回退版本。

soft：

``` bash
git reset --soft commit
```

保留修改并放入暂存区。

mixed：

``` bash
git reset commit
```

保留文件修改，取消暂存。

hard：

``` bash
git reset --hard commit
```

代码和提交一起回退。

### git revert

``` bash
git revert commit_id
```

通过创建新的反向提交撤销修改。

区别：

  命令     特点
  -------- ------------------------
  reset    修改历史，适合本地
  revert   保留历史，适合远程协作

## 六、远程仓库

查看：

``` bash
git remote -v
```

添加：

``` bash
git remote add origin URL
```

推送：

``` bash
git push
```

拉取：

``` bash
git pull
```

## 七、SSH连接GitHub

测试：

``` bash
ssh -T git@github.com
```

使用SSH地址：

``` bash
git@github.com:user/repo.git
```

## 八、今日实践

完成：

-   分支创建与切换
-   merge合并
-   冲突制造与解决
-   reset实验
-   revert实验
-   本地远程仓库测试
-   GitHub SSH连接确认

## 总结

掌握Git基本开发流程：

-   使用提交保存版本
-   使用分支进行开发
-   使用merge合并代码
-   使用reset和revert处理错误修改
-   使用remote同步远程仓库

Git部分已满足后续一生一芯开发需求。
