# Submssion 1 ——ljg

## Code



> sudo apt-get update
>
> sudo apt-get install ibus-gtk ibus-pinyin  # 安装输入法，反正后面还有很多……

-----------



> sudo passwd root	# 关于root
>
> su -
>
> exit

---



> sudo apt-get vim
>
> sudo apt-get update
>
> sudo apt-get upgrade	# 记得之后安装了清华的

---



> sudo apt-get install git
>
> git config --local --list
>
> git config --local --list
> git config --list
> git config --global user.email "870033938@qq.com"
> git config --global user.name "Serendipity"

> git version
> git --version

> ssh-keygen -t rsa -C "skyleaworlder"
>
> ssh -T git@github.com

> git config --global alias.commit cm
> git config --global alias.checkout co
> git config --global alias.status st
> git config --global alias.lg 'log --pretty=oneline --abbrev-commit --graph'
> git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"

> git add firsttxt
> git commit -m "this is my first txt on ubuntu"
>
> git log
>
> git status
> git diff
> git checkout master

> git reset --hard HEAD^
> git reset HEAD^
> git reset HEAD
> git reflog
>
> git diff HEAD -- firsttxt  查看工作区和版本库里面最新版本的区别
>
> git checkout -- firsttxt  清理工作区修改,但是不能撤销已提交到暂存区的修改
>
> git clean -n  查看该有哪些未清理的未跟踪文件
> git clean -i
> git clean -f
> git clean -df
>
> git rm txt
> git reset HEAD txt
> git checkout -- txt
>
> git remote add origin git@github.com:skyleaworlder/Yamedekudasai
> git remote rm origin
>
> git push origin master
> git push -u origin master
>
> git clone git@github.*com*:skyleaworlder/markdown-portfolio # 我今天中午找了1h的错，结果发现我打的是git@github:skyleawordlder，少了个.com，我这1h里面，重置了4次的ssh密钥，翻遍了我觉得可能有解决方案的所有地方，结果md！少了个.com！
>
> git clone git@github.com:ganler/SPTraining-VisionGroup
>

---



> sudo apt-get install build-essential
> sudo apt-get gcc g++

---



> cd ..
>
> touch 1.txt
>
> cat 1.txt
>
> rm 1.txt
>
> mkdir build && cd build
>
> ls -a										
>
> // 其实还有，但是感觉有点忘了

---



命令行以前没有太接触嘛，就是看别人打，但是自己完全不懂。（也不是



## Question

1. 总之装这个ubuntu整个过程我担惊受怕。生怕原来的windows的区域也被波及。
2. 这下有了不看qq的理由了，因为电脑现在没装qq，很好。
3. ubuntu是真滴慢啊，nmd，wsm？
4. 举步维艰，干啥都查一波。
5. vpn有点贵……除了吃饭喝水，还没有很规律地花过钱。有点不适应。所以还没科学上网，要的时候再搞（其实是搞了两个VPN发现都用不了了很气馁就放弃了
6. git明明过了一遍了，但是再看廖雪峰的教程还是觉得第一次看。难不成是他重写了一遍？（不
7. github界面很好看
8. 我英语差，大学一直不变过的自我认知，现在才晓得，原来是**差到不行**了。
9. end.