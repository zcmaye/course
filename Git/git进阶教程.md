# Git进阶教程

## 分支管理

分支就是科幻电影里面的平行宇宙，当你正在电脑前努力学习Git的时候，另一个你正在另一个平行宇宙里努力学习SVN。

如果两个平行宇宙互不干扰，那对现在的你也没啥影响。不过，在某个时间点，两个平行宇宙合并了，结果，你既学会了Git又学会了SVN！

![learn-branches](./assets/branch.png)

分支在实际中有什么用呢？假设你准备开发一个新功能，但是需要两周才能完成，第一周你写了50%的代码，如果立刻提交，由于代码还没写完，不完整的代码库会导致别人不能干活了。如果等代码全部写完再一次提交，又存在丢失每天进度的巨大风险。

现在有了分支，就不用怕了。你创建了一个属于你自己的分支，别人看不到，还继续在原来的分支上正常工作，而你在自己的分支上干活，想提交就提交，直到开发完毕后，再一次性合并到原来的分支上，这样，既安全，又不影响别人工作。

其他版本控制系统如SVN等都有分支管理，但是用过之后你会发现，这些版本控制系统创建和切换分支比蜗牛还慢，简直让人无法忍受，结果分支功能成了摆设，大家都不去用。

但Git的分支是与众不同的，无论创建、切换和删除分支，Git在1秒钟之内就能完成！无论你的版本库是1个文件还是1万个文件。



在版本回退]里，你已经知道，每次提交，Git都把它们串成一条时间线，这条时间线就是一个分支。截止到目前，只有一条时间线，在Git里，这个分支叫主分支，即`master`分支。`HEAD`严格来说不是指向提交，而是指向`master`，`master`才是指向提交的，所以，`HEAD`指向的就是当前分支。

一开始的时候，`master`分支是一条线，Git用`master`指向最新的提交，再用`HEAD`指向`master`，就能确定当前分支，以及当前分支的提交点：

```
                  HEAD
                    │
                    ▼
                 master
                    │
                    ▼
┌───┐    ┌───┐     ┌───┐
│   │───▶│   │───▶│   │
└───┘    └───┘     └───┘
```

每次提交，`master`分支都会向前移动一步，这样，随着你不断提交，`master`分支的线也越来越长。

当我们创建新的分支，例如`dev`时，Git新建了一个指针叫`dev`，指向`master`相同的提交，再把`HEAD`指向`dev`，就表示当前分支在`dev`上：

```
                 master
                    │
                    ▼
┌───┐     ┌───┐    ┌───┐
│   │───▶│   │───▶│   │
└───┘     └───┘    └───┘
                    ▲
                    │
                   dev
                    ▲
                    │
                  HEAD
```

你看，Git创建一个分支很快，因为除了增加一个`dev`指针，改改`HEAD`的指向，工作区的文件都没有任何变化！

不过，从现在开始，对工作区的修改和提交就是针对`dev`分支了，比如新提交一次后，`dev`指针往前移动一步，而`master`指针不变：

```
                 master
                    │
                    ▼
┌───┐    ┌───┐     ┌───┐    ┌───┐
│   │───▶│   │───▶│   │───▶│   │
└───┘    └───┘     └───┘    └───┘
                             ▲
                             │
                            dev
                             ▲
                             │
                           HEAD
```

假如我们在`dev`上的工作完成了，就可以把`dev`合并到`master`上。Git怎么合并呢？最简单的方法，就是直接把`master`指向`dev`的当前提交，就完成了合并：

```
                           HEAD
                             │
                             ▼
                          master
                             │
                             ▼
┌───┐    ┌───┐     ┌───┐    ┌───┐
│   │───▶│   │───▶│   │───▶│   │
└───┘    └───┘     └───┘    └───┘
                             ▲
                             │
                            dev
```

所以Git合并分支也很快！就改改指针，工作区内容也不变！

合并完分支后，甚至可以删除`dev`分支。删除`dev`分支就是把`dev`指针给删掉，删掉后，我们就剩下了一条`master`分支：

```
                           HEAD
                             │
                             ▼
                          master
                             │
                             ▼
┌───┐    ┌───┐     ┌───┐    ┌───┐
│   │───▶│   │───▶│   │───▶│   │
└───┘    └───┘     └───┘    └───┘
```

真是太神奇了，你看得出来有些提交是通过分支完成的吗？

### 创建与合并分支

下面开始实战。

首先，我们创建`dev`分支，然后切换到`dev`分支：

```bash
$ git switch -c dev
Switched to a new branch 'dev'
```

`git switch`命令加上`-c`参数表示创建并切换，相当于以下两条命令：

```bash
$ git branch dev
fatal: a branch named 'dev' already exists

$ git switch dev
Already on 'dev'
```

因为前面已经创建并切换到了`dev`分支，所以再次创建就会报错。

可以先使用`git branch -d <name>`命令删除分支，然后再创建~。

```bash
git branch -d dev
```

如果不小心写错了分支名，可以直接修改分支名：

```bash
$ git branch -m dev_ok			#修改当前分支，将当前dev分支名修改为dev_ok
$ git branch -m dev_ok dev		#修改指定的分支,将dev_ok分支名修改为dev
```

然后，用`git branch`命令查看当前分支：

```bash
$ git branch
* dev
  master
```

`git branch`命令会列出所有分支，当前分支前面会标一个`*`号。

然后，我们就可以在`dev`分支上正常提交，比如对`readme.txt`做个修改，加上一行：

```css
Creating a new branch is quick.
```

然后提交：

```bash
$ git add readme.txt

$ git commit -m "branch test"
[dev 6f4f0f0] branch test
 1 file changed, 1 insertion(+)
```

现在，`dev`分支的工作完成，我们就可以切换回`master`分支：

```bash
$ git switch master
Switched to branch 'master'
Your branch is up to date with 'origin/master'.
```

切换回`master`分支后，再查看一个`readme.txt`文件，刚才添加的内容不见了！因为那个提交是在`dev`分支上，而`master`分支此刻的提交点并没有变：

```
                  HEAD
                    │
                    ▼
                 master
                    │
                    ▼
┌───┐    ┌───┐     ┌───┐    ┌───┐
│   │───▶│   │───▶│   │───▶│   │
└───┘    └───┘     └───┘    └───┘
                             ▲
                             │
                            dev
```

现在，我们把`dev`分支的工作成果合并到`master`分支上：

```bash
$ git merge dev
Updating e24dc84..6f4f0f0
Fast-forward
 readme.txt | 1 +
 1 file changed, 1 insertion(+)
```

`git merge`命令用于合并指定分支到当前分支。合并后，再查看`readme.txt`的内容，就可以看到，和`dev`分支的最新提交是完全一样的。

注意到上面的`Fast-forward`信息，Git告诉我们，这次合并是“快进模式”，也就是直接把`master`指向`dev`的当前提交，所以合并速度非常快。

当然，也不是每次合并都能`Fast-forward`，我们后面会讲其他方式的合并。

合并完成后，就可以放心地删除`dev`分支了：

```bash
$ git branch -d dev
Deleted branch dev (was 6f4f0f0).
```

删除后，查看`branch`，就只剩下`master`分支了：

```bash
$ git branch
* master
```

因为创建、合并和删除分支非常快，所以Git鼓励你使用分支完成某个任务，合并后再删掉分支，这和直接在`master`分支上工作效果是一样的，但过程更安全。

> 我们注意到切换分支使用`git switch <branch>`，其实还有一个`git checkout`命令也能切换分支，但是他与前面讲过的撤销修改则是`git checkout -- <file>`(我们用的是`git restore <file>`)，同一个命令，有两种作用，确实有点令人迷惑。
>
> 实际上，切换分支这个动作，用`switch`更科学。因此，最新版本的Git提供了新的`git switch`命令来切换分支。
>
> 实际上，撤销修改`git restore`也是用来替代`git checkout --`命令的。

### 解决冲突

人生不如意之事十之八九，合并分支往往也不是一帆风顺的。

准备新的`feature1`分支，继续我们的新分支开发：

```bash
$ git switch -c feature1
Switched to a new branch 'feature1'
```

修改`readme.txt`最后一行，改为：

```css
Creating a new branch is quick AND simple.
```

在`feature1`分支上提交：

```bash
$ git add readme.txt

$ git commit -m "AND simple"
[feature1 b7eca00] AND simple
 1 file changed, 1 insertion(+), 1 deletion(-)
```

切换到`master`分支：

```bash
$ git switch master
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 1 commit.
  (use "git push" to publish your local commits)
```

Git还会自动提示我们当前`master`分支比远程的`master`分支要超前1个提交，因为我们在前面已经把这个仓库推送到了远程仓库，而在刚才合并时，我们在本地又有了一个新的提交，所以才提示本地分支比远程分支提前一个提交(就是多了一个提交)。

在`master`分支上把`readme.txt`文件的最后一行改为：

```css
Creating a new branch is quick && simple.
```

提交：

```bash
$ git add readme.txt

$ git commit -m "&& simple"
[master df2ac48] && simple
 1 file changed, 1 insertion(+), 1 deletion(-)
```

现在，`master`分支和`feature1`分支各自都分别有新的提交，变成了这样：

```
                            HEAD
                              │
                              ▼
                           master
                              │
                              ▼
                             ┌───┐
                          ┌─▶│   │
┌───┐    ┌───┐     ┌───┐  │  └───┘
│   │───▶│   │───▶│   │──┤
└───┘    └───┘     └───┘  │  ┌───┐
                          └─▶│   │
                             └───┘
                              ▲
                              │
                          feature1
```

这种情况下，Git无法执行“快速合并”，只能试图把各自的修改合并起来，但这种合并就可能会有冲突，我们试试看：

```bash
$ git merge feature1
Auto-merging readme.txt
CONFLICT (content): Merge conflict in readme.txt
Automatic merge failed; fix conflicts and then commit the result.
```

果然冲突了！Git告诉我们，`readme.txt`文件存在冲突，必须手动解决冲突后再提交。`git status`也可以告诉我们冲突的文件：

```bash
$ git status
On branch master
Your branch is ahead of 'origin/master' by 2 commits.
  (use "git push" to publish your local commits)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   readme.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

我们再查看一下readme.txt的内容：

```bash
$ cat readme.txt
Git is a distributed version control system.
Git is free software distribute under the GPL.
Git has a mutable index called stage.
<<<<<<< HEAD		#当前分支内容
Creating a new branch is quick && simple.
=======				#合并分支的内容
Creating a new branch is quick AND simple.
>>>>>>> feature1	#差异结束
```

Git用`<<<<<<<`，`=======`，`>>>>>>>`标记出不同分支的内容，我们修改如下后保存：

```css
Git is a distributed version control system.
Git is free software distribute under the GPL.
Git has a mutable index called stage.
Creating a new branch is quick and simple.
```

再提交：

```bash
$ git add readme.txt
$ git commit -m "conflict fixed"
[master ae55cf0] conflict fixed
```

现在，`master`分支和`feature1`分支变成了下图所示：

```
                                      HEAD
                                        │
                                        ▼
                                     master
                                        │
                                        ▼
                             ┌───┐     ┌───┐
                          ┌─▶│   │───▶│   │
┌───┐    ┌───┐     ┌───┐  │  └───┘     └───┘
│   │───▶│   │───▶│   │──┤             ▲
└───┘    └───┘     └───┘  │  ┌───┐      │
                          └─▶│   │──────┘
                             └───┘
                               ▲
                               │
                           feature1
```

用带参数的`git log`也可以看到分支的合并情况：

```bash
$ git log --graph --pretty=oneline --abbrev-commit
*   ae55cf0 (HEAD -> master) conflict fixed
|\
| * b7eca00 (feature1) AND simple
* | df2ac48 && simple
|/
* 6f4f0f0 branch test
* e24dc84 (origin/master) remove test.txt
* 76dd540 add test.txt
* 40521de understand how stage works
* 7dd3634 append GPL
* a6fb976 add distributed
* 014a891 wrote a readme file
```

最后，删除`feature1`分支：

```bash
$ git branch -d feature1
Deleted branch feature1 (was b7eca00).
```

工作完成，下班！

**小结**

当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。

解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。

用`git log --graph`命令可以看到分支合并图。

如果你突然反悔，不想合并了可以使用`git merge --abort`命令，撤销合并。

```bash
git merge --abort
```

### 分支管理策略

通常，合并分支时，如果可能，Git会用`Fast forward`模式，但这种模式下，删除分支后，会丢掉分支信息。

如果要强制禁用`Fast forward`模式，Git就会在merge时生成一个新的commit，这样，从分支历史上就可以看出分支信息。

下面我们实战一下`--no-ff`方式的`git merge`：

首先，仍然创建并切换`dev`分支：

```bash
$ git switch -c dev
Switched to a new branch 'dev'
```

修改readme.txt文件，并提交一个新的commit：

```bash
$ git add readme.txt

$ git commit -m "add merge"
[dev af99b85] add merge
 1 file changed, 1 insertion(+), 1 deletion(-)
```

现在，我们切换回`master`：

```bash
$ git switch master
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 4 commits.
  (use "git push" to publish your local commits)
```

准备合并`dev`分支，请注意`--no-ff`参数，表示禁用`Fast forward`：

```bash
$ git merge --no-ff -m "merge with no-ff" dev
Merge made by the 'ort' strategy.
 readme.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

因为本次合并要创建一个新的commit，所以加上`-m`参数，把commit描述写进去。

合并后，我们用`git log`看看分支历史：

```bash
$ git log --graph --pretty=oneline --abbrev-commit
*   884e78a (HEAD -> master) merge with no-ff
|\
| * af99b85 (dev) add merge
|/
*   ae55cf0 conflict fixed
...
```

可以看到，不使用`Fast forward`模式，merge后就像这样：

```
                                  HEAD
                                   │
                                   ▼
                                 master
                                   │
                                   ▼
                                  ┌───┐
                           ┌─────▶│   │
┌───┐     ┌───┐     ┌───┐  │      └───┘
│   │───▶ │   │───▶│   │──┤        ▲
└───┘     └───┘     └───┘  │  ┌───┐ │
                           └─▶│   │─┘
                              └───┘
                               ▲
                               │
                              dev
```

#### 分支策略

在实际开发中，我们应该按照几个基本原则进行分支管理：

首先，`master`分支应该是非常稳定的，也就是仅用来发布新版本，平时不能在上面干活；

那在哪干活呢？干活都在`dev`分支上，也就是说，`dev`分支是不稳定的，到某个时候，比如1.0版本发布时，再把`dev`分支合并到`master`上，在`master`分支发布1.0版本；

你和你的小伙伴们每个人都在`dev`分支上干活，每个人都有自己的分支，时不时地往`dev`分支上合并就可以了。

所以，团队合作的分支看起来就像这样：

![git-br-policy](./assets/branches.png)

#### 小结

Git分支十分强大，在团队开发中应该充分应用。

合并分支时，加上`--no-ff`参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而`fast forward`合并就看不出来曾经做过合并。

### Bug分支

软件开发中，bug就像家常便饭一样。有了bug就需要修复，在Git中，由于分支是如此的强大，所以，每个bug都可以通过一个新的临时分支来修复，修复后，合并分支，然后将临时分支删除。

当你接到一个修复一个代号101的bug的任务时，很自然地，你想创建一个分支`issue-101`来修复它，但是，等等，当前正在`dev`上进行的工作还没有提交：

```bash
$ git status
On branch dev
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   hello.c
```

并不是你不想提交，而是工作只进行到一半，还没法提交，预计完成还需1天时间。但是，必须在两个小时内修复该bug，怎么办？

#### 修复Bug

幸好，Git还提供了一个`stash`功能，可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作：

```bash
$ git stash
Saved working directory and index state WIP on dev: af99b85 add merge
```

现在，用`git status`查看工作区，就是干净的（除非有没有被Git管理的文件），因此可以放心地创建分支来修复bug。

首先确定要在哪个分支上修复bug，假定需要在`master`分支上修复，就从`master`创建临时分支：

```bash
$ git switch master
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 6 commits.
  (use "git push" to publish your local commits)

$ git switch -c issue-101
Switched to a new branch 'issue-101'
```

现在修复bug，需要把“Git is free software ...”改为“Git is a free software ...”，然后提交：

```bash
$ git add readme.txt

$ git commit -m "fix bug 101"
[issue-101 b808302] fix bug 101
 1 file changed, 1 insertion(+), 1 deletion(-)
```

修复完成后，切换到`master`分支，并完成合并，最后删除`issue-101`分支：

```bash
$ git switch master
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 6 commits.
  (use "git push" to publish your local commits)

$ git merge --no-ff -m "merged bug fix 101" issue-101
Merge made by the 'ort' strategy.
 readme.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

注意：删除分支时候可能会报错：

```bash
$ git branch -d issue-101
error: the branch 'issue-101' is not fully merged
hint: If you are sure you want to delete it, run 'git branch -D issue-101'
hint: Disable this message with "git config set advice.forceDeleteBranch false"
```

> 大概意思是，如果本地分支没有合并到其他分支，或者没有对应的远程分支，删除时则会提示这个错误。使用`-D`选项强制删除即可！

太棒了，原计划两个小时的bug修复只花了5分钟！现在，是时候接着回到`dev`分支干活了！

```bash
$ git switch dev
Switched to branch 'dev'

$ git status
On branch dev
nothing to commit, working tree clean
```

工作区是干净的，刚才的工作现场存到哪去了？用`git stash list`命令看看：

```bash
$ git stash list
stash@{0}: WIP on dev: af99b85 add merge
```

工作现场还在，Git把`stash`内容存在某个地方了，但是需要恢复一下，有两个办法：

一是用`git stash apply`恢复，但是恢复后，`stash`内容并不删除，你需要用`git stash drop`来删除；

另一种方式是用`git stash pop`，恢复的同时把`stash`内容也删了：

```bash
$ git stash pop
On branch dev
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   hello.c

Dropped refs/stash@{0} (d6e32bfa7cf506ba076452f892362d4c890231ac)
```

再用`git stash list`查看，就看不到任何`stash`内容了：

```bash
$ git stash list
```

你可以多次`stash`，恢复的时候，先用`git stash list`查看，然后恢复指定的`stash`，用命令：

```bash
$ git stash apply stash@{0}
```

#### 同步Bug修改

在`master`分支上修复了bug后，我们要想一想，`dev`分支是早期从`master`分支分出来的，所以，这个bug其实在当前`dev`分支上也存在。

那怎么在`dev`分支上修复同样的bug？重复操作一次，提交不就行了？

有木有更简单的方法？

有！

同样的bug，要在`dev`上修复，我们只需要把`b808302 fix bug 101`这个提交所做的修改“复制”到`dev`分支。注意：我们只想复制`b808302 fix bug 101`这个提交所做的修改，并不是把整个`master`分支merge过来。

为了方便操作，Git专门提供了一个`cherry-pick`命令，让我们能复制一个特定的提交到当前分支：

```bash
$ git cherry-pick b808302
error: your local changes would be overwritten by cherry-pick.
hint: commit your changes or stash them to proceed.
fatal: cherry-pick failed
```

报错了，告诉我们需要先将本地更改提交或者隐藏后，再操作！

```bash
$ git stash
Saved working directory and index state WIP on dev: af99b85 add merge

$ git cherry-pick b808302
[dev 6ecb685] fix bug 101
 Date: Tue Nov 25 15:09:48 2025 +0800
 1 file changed, 1 insertion(+), 1 deletion(-)
 
 $ git stash pop
On branch dev
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   hello.c

Dropped refs/stash@{0} (b4884cfb89f1976c8a03181026a6d63cda7c3b4d)

$ git log --pretty=oneline --graph --abbrev-commit
* 6ecb685 (HEAD -> dev) fix bug 101			#自动提交的
* af99b85 add merge
*   ae55cf0 conflict fixed
```

Git自动给`dev`分支做了一次提交，注意这次提交的commit是`6ecb685`，它并不同于`master`的`b808302`，因为这两个commit只是改动相同，但确实是两个不同的commit。用`git cherry-pick`，我们就不需要在`dev`分支上手动再把修bug的过程重复一遍。

有些聪明的童鞋会想了，既然可以在`master`分支上修复bug后，在`dev`分支上可以“重放”这个修复过程，那么直接在`dev`分支上修复bug，然后在`master`分支上“重放”行不行？当然可以，不过你仍然需要`git stash`命令保存现场，才能从`dev`分支切换到`master`分支。

#### 小结

修复bug时，我们会通过创建新的bug分支进行修复，然后合并，最后删除；

当手头工作没有完成时，先把工作现场`git stash`一下，然后去修复bug，修复后，再`git stash pop`，回到工作现场；

在`master`分支上修复的bug，想要合并到当前`dev`分支，可以用`git cherry-pick <commit>`命令，把bug提交的修改“复制”到当前分支，避免重复劳动。

### 多人协作

当你从远程仓库克隆时，实际上Git自动把本地的`master`分支和远程的`master`分支对应起来了，并且，远程仓库的默认名称是`origin`。

要查看远程库的信息，用`git remote`：

```bash
$ git remote
origin
```

或者，用`git remote -v`显示更详细的信息：

```bash
$ git remote -v
origin  https://gitee.com/zcmaye/learngit.git (fetch)
origin  https://gitee.com/zcmaye/learngit.git (push)
```

上面显示了可以抓取和推送的`origin`的地址。如果没有推送权限，就看不到push的地址。

#### 推送分支

推送分支，就是把该分支上的所有本地提交推送到远程库。推送时，要指定本地分支，这样，Git就会把该分支推送到远程库对应的远程分支上：

```bash
$ git push origin master
```

如果要推送其他分支，比如`dev`，就改成：

```bash
$ git push origin dev
```

但是，并不是一定要把本地分支往远程推送，那么，哪些分支需要推送，哪些不需要呢？

- `master`分支是主分支，因此要时刻与远程同步；
- `dev`分支是开发分支，团队所有成员都需要在上面工作，所以也需要与远程同步；
- bug分支只用于在本地修复bug，就没必要推到远程了，除非老板要看看你每周到底修复了几个bug；
- feature分支是否推到远程，取决于你是否和你的小伙伴合作在上面开发。

总之，就是在Git中，分支完全可以在本地自己藏着玩，是否推送，视你的心情而定！

#### 拉取分支

多人协作时，大家都会往`master`和`dev`分支上推送各自的修改。

现在，模拟一个你的小伙伴，可以在另一台电脑（注意要把SSH Key添加到GitHub）或者同一台电脑的另一个目录下克隆：

```bash
$ git clone https://gitee.com/zcmaye/learngit.git
Cloning into 'learngit'...
remote: Enumerating objects: 37, done.
remote: Counting objects: 100% (37/37), done.
remote: Compressing objects: 100% (26/26), done.
remote: Total 37 (delta 12), reused 0 (delta 0), pack-reused 0 (from 0)
Receiving objects: 100% (37/37), done.
Resolving deltas: 100% (12/12), done.
```

当你的小伙伴从远程库clone时，默认情况下，你的小伙伴只能看到本地的`master`分支。不信可以用`git branch`命令看看：

```bash
$ git branch
* master
```

现在，你的小伙伴要在`dev`分支上开发，就必须创建远程`origin`的`dev`分支到本地，于是他用这个命令创建本地`dev`分支：

```bash
$ git switch -c dev origin/dev
branch 'dev' set up to track 'origin/dev'.
Switched to a new branch 'dev'
```

现在，他就可以在`dev`上继续修改，然后，时不时地把`dev`分支`push`到远程：

```bash
$ vim env.txt

$ git add env.txt

$ git commit -m "add env"
[dev f708df8] add env
 1 file changed, 1 insertion(+)
 create mode 100644 env.txt

$ git push origin dev
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 265 bytes | 265.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Powered by GITEE.COM [1.1.23]
remote: Set trace flag cf4e6d82
To https://gitee.com/zcmaye/learngit.git
   f4eedb5..f708df8  dev -> dev
```

#### 推送冲突

你的小伙伴已经向`origin/dev`分支推送了他的提交，而碰巧你也对同样的文件作了修改，并试图推送：

```bash
$ git push origin dev
To https://gitee.com/zcmaye/learngit.git
 ! [rejected]        dev -> dev (fetch first)
error: failed to push some refs to 'https://gitee.com/zcmaye/learngit.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

推送失败，因为你的小伙伴的最新提交和你试图推送的提交有冲突，解决办法也很简单，Git已经提示我们，先用`git pull`把最新的提交从`origin/dev`抓下来，然后，在本地合并，解决冲突，再推送：

```bash
$ git pull
remote: Enumerating objects: 4, done.
remote: Counting objects: 100% (4/4), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (3/3), 245 bytes | 49.00 KiB/s, done.
From https://gitee.com/zcmaye/learngit
   f4eedb5..f708df8  dev        -> origin/dev
There is no tracking information for the current branch.
Please specify which branch you want to merge with.
See git-pull(1) for details.

    git pull <remote> <branch>

If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> dev
```

`git pull`也失败了，原因是没有指定本地`dev`分支与远程`origin/dev`分支的链接，根据提示，设置`dev`和`origin/dev`的链接：

```bash
$ git branch --set-upstream-to=origin/dev dev
branch 'dev' set up to track 'origin/dev'.
```

再pull：

```bash
$ git pull
Updating f4eedb5..f708df8
Fast-forward
 env.txt | 1 +
 1 file changed, 1 insertion(+)
 create mode 100644 env.txt
```

但是如果合并有冲突，需要手动解决，解决的方法和分支管理中的[解决冲突](https://liaoxuefeng.com/books/git/branch/merge/index.html)完全一样。解决后，提交，再push：

```bash
$ git commit -m "fix env conflict"
```

因此，多人协作的工作模式通常是这样：

1. 首先，可以尝试用`git push origin <branch-name>`推送自己的修改；
2. 如果推送失败，则因为远程分支比你的本地更新，需要先用`git pull`试图合并；
3. 如果合并有冲突，则解决冲突，并在本地提交；
4. 没有冲突或者解决掉冲突后，再用`git push origin <branch-name>`推送就能成功！

如果`git pull`提示`no tracking information`，则说明本地分支和远程分支的链接关系没有创建，用命令`git branch --set-upstream-to=origin/<branch-name> <branch-name>`。

这就是多人协作的工作模式，一旦熟悉了，就非常简单。

#### 查看分支

前面我们说过可以使用`git branch`命令查看本地分支：

```bash
git branch
```

如果想要查看远程分支可以使用如下三个命令查看：

+ 查看远程跟踪分支（本地存储的远程分支状态）：

  ```bash
  $ git branch -r
    origin/HEAD -> origin/master
    origin/dev
    origin/master
  ```

+ 查看远程仓库上实际的所有分支（需要网络连接，直接查询远程仓库）：

  ```bash
  $ git ls-remote --heads origin
  f708df86a256d1f48c5cd612600dddb85261fdc2        refs/heads/dev
  d39db30d0d0b0e239915c2153a95de1fb23d2558        refs/heads/master
  ```

+ 查看远程仓库的详细信息，包括远程分支列表（需要网络连接）：

  ```bash
  $ git remote show origin
  * remote origin
    Fetch URL: https://gitee.com/zcmaye/learngit.git
    Push  URL: https://gitee.com/zcmaye/learngit.git
    HEAD branch: master
    Remote branches:
      dev    tracked
      master tracked
    Local branches configured for 'git pull':
      dev    merges with remote dev
      master merges with remote master
    Local refs configured for 'git push':
      dev    pushes to dev    (up to date)
      master pushes to master (fast-forwardable)
  ```

根据需求，选择不同的命令。

#### 删除分支

前面我们说过可以使用`git branch -d <name>`命令删除本地分支：

```bash
git branch -d dev
```

如果想要删除远程分支可以使用`git push origin -d <branch>`命令：

```bash
$ git push origin -d dev
remote: Powered by GITEE.COM [1.1.23]
remote: Set trace flag 7d4ab09e
To https://gitee.com/zcmaye/learngit.git
 - [deleted]         dev
```

### 小结

- 查看远程库信息，使用`git remote -v`；
- 本地新建的分支如果不推送到远程，对其他人就是不可见的；
- 从本地推送分支，使用`git push origin branch-name`，如果推送失败，先用`git pull`抓取远程的新提交；
- 在本地创建和远程分支对应的分支，使用`git switch -c branch-name origin/branch-name`，本地和远程分支的名称最好一致；
- 建立本地分支和远程分支的关联，使用`git branch --set-upstream-to=origin/<branch-name> <branch-name>`；
- 从远程抓取分支，使用`git pull`，如果有冲突，要先处理冲突。

## 标签管理

发布一个版本时，我们通常先在版本库中打一个标签（tag），这样，就唯一确定了打标签时刻的版本。将来无论什么时候，取某个标签的版本，就是把那个打标签的时刻的历史版本取出来。所以，标签也是版本库的一个快照。

Git的标签虽然是版本库的快照，但其实它就是指向某个commit的指针（跟分支很像对不对？但是分支可以移动，标签不能移动），所以，创建和删除标签都是瞬间完成的。

Git有commit，为什么还要引入tag？

“请把上周一的那个版本打包发布，commit号是6a5819e...”

“一串乱七八糟的数字不好找！”

如果换一个办法：

“请把上周一的那个版本打包发布，版本号是v1.2”

“好的，按照tag v1.2查找commit就行！”

所以，tag就是一个让人容易记住的有意义的名字，它跟某个commit绑在一起。

### 创建标签

在Git中打标签非常简单，首先，切换到需要打标签的分支上：

```bash
$ git branch
* dev
  master

$ git switch master
Switched to branch 'master'
```

然后，敲命令`git tag <name>`就可以打一个新标签：

```bash
git tag v.10
```

可以用命令`git tag`查看所有标签：

```bash
$ git tag
v1.0
```

默认标签是打在最新提交的commit上的。有时候，如果忘了打标签，比如，现在已经是周五了，但应该在周一打的标签没有打，怎么办？

方法是找到历史提交的commit id，然后打上就可以了：

```bash
$ git log --pretty=oneline --abbrev-commit
c4b5020 (HEAD -> master, tag: v1.0) add hello.c
d39db30 (origin/master, origin/HEAD) merged bug fix 101
89fd12a fix bug 101
3f85beb merge with no-ff
fa7a6ca add merge
4c73256 conflict fixed
3304170 && simple
d11b1b2 AND simple
81d5a77 branch test
dd9a520 remove test.txt
9ec7c5d add test.txt
4819e63 understand how stage works
ea461a2 append GPL
dad6e19 add distributed
e445a05 wrote a readme file
```

比方说要对`add merge`这次提交打标签，它对应的commit id是`fa7a6ca`，敲入命令：

```bash
$ git tag v0.9 fa7a6ca
```

再用命令`git tag`查看标签：

```bash
$ git tag
v0.9
v1.0
```

注意，标签不是按时间顺序列出，而是按字母排序的。可以用`git show <tagname>`查看标签信息：

```bash
$ git show v0.9
commit fa7a6ca97ed6db57056452d5bb4c1bd64b3740f1 (tag: v0.9, tag: show)
Author: maye <zcmaye@gmail.com>
Date:   Tue Nov 25 16:40:58 2025 +0800

    add merge

diff --git a/readme.txt b/readme.txt
index 71a01c4..2a57435 100644
--- a/readme.txt
+++ b/readme.txt
@@ -2,3 +2,4 @@ Git is a distributed version control system.
 Git is free software distributed under the GPL.
 Git has a mutable index called stage.
 Creating a new branch is quick and simple.
+--
```

可以看到，`v0.9`确实打在`add merge`这次提交上。

还可以创建带有说明的标签，用`-a`指定标签名，`-m`指定说明文字：

```bash
$ git tag -a v0.1 -m "version 0.1 released" ea461a2
```

用命令`git show <tagname>`可以看到说明文字：

```bash
$ git show v0.1
tag v0.1
Tagger: maye <zcmaye@gmail.com>
Date:   Wed Nov 26 14:30:28 2025 +0800

version 0.1 released

commit ea461a2d54673fea55bab22cd979028c0fb26b56 (tag: v0.1)
Author: maye <zcmaye@gmail.com>
Date:   Tue Nov 25 16:28:30 2025 +0800

    append GPL

diff --git a/readme.txt b/readme.txt
index 9247db6..8443d23 100644
--- a/readme.txt
+++ b/readme.txt
@@ -1,2 +1,2 @@
 Git is a distributed version control system.
-Git is free software.
+Git is free software distributed under the GPL.
```

>  注意：标签总是和某个commit挂钩。如果这个commit既出现在master分支，又出现在dev分支，那么在这两个分支上都可以看到这个标签

**小结**

- 命令`git tag <tagname>`用于新建一个标签，默认为`HEAD`，也可以指定一个commit id；
- 命令`git tag -a <tagname> -m "blablabla..."`可以指定标签信息；
- 命令`git tag`可以查看所有标签。

### 操作标签

如果标签打错了，也可以删除：

```bash
$ git tag -d v0.1
Deleted tag 'v0.1' (was fa39981)
```

因为创建的标签都只存储在本地，不会自动推送到远程。所以，打错的标签可以在本地安全删除。

如果要推送某个标签到远程，使用命令`git push origin <tagname>`：

```bash
$ git push origin v1.0
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 288 bytes | 288.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Powered by GITEE.COM [1.1.23]
remote: Set trace flag ba4540b6
To https://gitee.com/zcmaye/learngit.git
 * [new tag]         v1.0 -> v1.0
```

或者，一次性推送全部尚未推送到远程的本地标签：

```bash
$ git push origin --tags
Total 0 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Powered by GITEE.COM [1.1.23]
remote: Set trace flag b54dff8e
To https://gitee.com/zcmaye/learngit.git
 * [new tag]         v0.9 -> v0.9
```

如果标签已经推送到远程，要删除远程标签就麻烦一点，先从本地删除：

```bash
$ git tag -d v0.9
Deleted tag 'v0.9' (was fa7a6ca)
```

然后，从远程删除。删除命令也是push，但是格式如下：

```bash
$ git push origin -d tag v0.9
remote: Powered by GITEE.COM [1.1.23]
remote: Set trace flag 1a4cc5a4
To https://gitee.com/zcmaye/learngit.git
 - [deleted]         v0.9
```

要看看是否真的从远程库删除了标签，可以登陆Gitee查看。

还可以使用如下方式删除远程标签：

```bash
$ git push origin --delete tag v0.9	#--delete 是 -d 的完整版本
$ git push origin :refs/tags/v0.9	#使用引用规格（refspec）的语法，引用规格通常用于定义本地分支和远程分支之间的映射。
$ git push origin :v0.9				#上面的简写方式
```

**小结**

- 命令`git push origin <tagname>`可以推送一个本地标签；
- 命令`git push origin --tags`可以推送全部未推送过的本地标签；
- 命令`git tag -d <tagname>`可以删除一个本地标签；
- 命令`git push origin --delete tag <tagname>`可以删除一个远程标签。