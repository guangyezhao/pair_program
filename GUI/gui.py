# -*- coding: utf-8 -*-

from tkinter import *
import datetime
import time
import tkinter.messagebox

rightnum = 0  # 正确的题数

user_answer = [" "]*1000  # 记录用户的答案

i = 1


# 历史记录类
class HistoryWindow:

    def __init__(self):
        self.root = Tk()
        self.root.geometry("500x500+450+100")
        self.root.title("see your history record.")

        scroll = Scrollbar(self.root)
        scroll.pack(side=RIGHT, fill=Y)

        with open('history.txt', 'r') as f3:
            his = f3.readlines()              # 读入历史记录

            his_len = len(his)/4

        # 展现历史记录
        list = Listbox(self.root, height=100, width=200, yscrollcommand=scroll.set)
        for j in range(his_len):
            list.insert(END, "time: "+his[4*j])
            list.insert(END, "total number: " + his[4*j+1])
            list.insert(END, "right answer number: " + his[4*j+2])
            list.insert(END, "正确率: " + his[4*j+3])
            list.insert(END, "\n")
        list.pack(side=LEFT)
        scroll.config(command=list.yview)

        close_button = Button(self.root, text="close", height=1, width=6, fg="red", bg="black", font=("Arial", 16), command=self.quit_window)
        close_button.place(x=420, y=460, anchor='nw')

    # 关闭页面
    def quit_window(self):
        self.root.destroy()


# 结果窗口类
class ResultWindow:

    def __init__(self):
        self.root = Tk()
        self.root.geometry("500x500+450+100")
        self.root.title("Your answer result as fellow")

        # 展现本次答题结果
        str_num = str(num)
        str_rightnum = str(rightnum)
        acc = round(float(rightnum) / num, 3) * 100
        str_acc = str(acc)
        line1 = Label(self.root, text="total question number: " + str_num + "道", height=2, width=25, font=("Arial", 24))
        line1.place(x=0, y=0, anchor='nw')
        line2 = Label(self.root, text="your right answer number: " + str_rightnum + "道", height=2, width=25, font=("Arial", 24))
        line2.place(x=0, y=80, anchor='nw')
        line3 = Label(self.root, text="your accuracy is: " + str_acc + "%", height=2, width=25, font=("Arial", 24))
        line3.place(x=0, y=160, anchor='nw')

        # 将答题结果记录到history.txt
        file = r'history.txt'
        with open(file, 'a+') as f4:
            global nowTime
            f4.write(nowTime + '\n')
            f4.write(str_num + '道' + '\n')
            f4.write(str_rightnum + '道' + '\n')
            f4.write(str_acc + '%' + '\n')

        show_history_button = Button(self.root, text="show history", height=1, width=10, bg="Yellow", font=("Arial", 16), command=self.show_history)
        show_history_button.place(x=180, y=320, anchor='nw')

        close_button = Button(self.root, text="close", height=1, width=6, fg="red", bg="black", font=("Arial", 16),
                              command=self.quit_window)
        close_button.place(x=420, y=460, anchor='nw')

    # 展现历史记录页面
    def show_history(self):
        self.root.destroy()
        hwin = HistoryWindow()

    # 关闭窗口
    def quit_window(self):
        self.root.destroy()


# 答题界面窗口类
class QuestionWindow:

    def __init__(self):
        self.root = Tk()
        self.root.geometry("600x600+400+50")
        self.root.title("welcome to test your math ability.")

        global i
        question = Label(self.root, text="第" + str(i) + "题" + " :  " + q[i - 1], height=2, width=35, bg="Green", font=("微软雅黑", 20))
        question.place(x=19, y=30, anchor='nw')

        answer_title = Label(self.root, text="answer: ", height=2, width=10, font=("Arial", 24))
        answer_title.place(x=6, y=200, anchor='nw')

        answerbox = Entry(self.root, width=10)
        answerbox.place(x=160, y=233, anchor='nw')
        user_answer[i-1] = answerbox.get()

        if user_answer[i-1] == right_answer[i-1]:
            global rightnum
            rightnum += 1

        hind = Label(self.root, text="提示: \n如果答案是整数，请直接写；\n如果答案是分数，请写xx/xx的形式。", justify=LEFT, height=5, width=35, font=("微软雅黑", 14))
        hind.place(x=216, y=180, anchor='nw')

        nextq = Button(self.root, text="next question", height=1, width=15, fg="black", bg="Orchid", font=("Arial", 16), command=self.OnNext)
        nextq.place(x=350, y=450, anchor='nw')

        close_button = Button(self.root, text="close", height=1, width=6, fg="red", bg="black", font=("Arial", 16),
                              command=self.close)
        close_button.place(x=518, y=558, anchor='nw')

        # 倒计时模块
        self.count = 0
        self.total_time = 80
        while self.count <= self.total_time:
            remain_time = self.total_time - self.count
            time_label = Label(self.root, text=str(remain_time) + "s", height=2, width=7, bg="SkyBlue",
                               font=("微软雅黑", 36))
            time_label.place(x=80, y=400, anchor='nw')
            self.root.update()
            time.sleep(1)  # sleep 1 second
            self.count += 1
        if self.total_time != -1:
            tkinter.messagebox.askokcancel('notify', 'time\'s up!')
            self.OnNext()

    # 到下一道题，由时间到了或者点击“next question”触发
    def OnNext(self):
        global i
        i = i+1

        self.total_time = -1
        self.root.destroy()   # 为了让本页面的倒计时停止，让total_time为-1，并且摧毁本页面

        if i != num+1:
            win = QuestionWindow()
        else:
            win = ResultWindow()

    # 关闭本页面，退出答题
    def close(self):
        self.total_time = -1
        self.root.destroy()


# 获取当前时间点
nowTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

# 读入所有问题
with open('question.txt', 'r') as f1:
    q = f1.readlines()

# 问题的个数
num = len(q)

# 读入所有问题的答案
with open('answer.txt', 'r') as f2:
    right_answer = f2.readlines()

# 打开一个页面，开始答题
win = QuestionWindow()

win.root.mainloop()