# -*- coding: utf-8 -*-

from Tkinter import *
import datetime
import time
from tkMessageBox import *

rightnum = 0

user_answer = [" "]*1000

i = 1


class history_window():

    def __init__(self):
        self.root = Tk()
        self.root.geometry("500x500+450+100")
        self.root.title("see your history record.")

        scroll = Scrollbar(self.root)
        scroll.pack(side=RIGHT, fill=Y)

        with open('history.txt', 'r') as f3:
            his = f3.readlines()

            his_len = len(his)/4

        list = Listbox(self.root,height=100, width=200, yscrollcommand=scroll.set)
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

    def quit_window(self):
        self.root.destroy()


class result_window():

    def __init__(self):
        self.root = Tk()
        self.root.geometry("500x500+450+100")
        self.root.title("welcome to test your math ability.")
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

        file = r'history.txt'
        with open(file, 'a+') as f4:
            global nowTime
            f4.write(nowTime + '\n')
            f4.write(str_num + '道' + '\n')
            f4.write(str_rightnum + '道' + '\n')
            f4.write(str_acc + '%' + '\n')

        show_history_button = Button(self.root, text="show history", height=1, width=10, font=("Arial", 16), command=self.show_history)
        show_history_button.place(x=90, y=320, anchor='nw')

        close_button = Button(self.root, text="close", height=1, width=15, fg="red", bg="black", font=("Arial", 16), command=self.quit_window)
        close_button.place(x=260, y=320, anchor='nw')

    def show_history(self):
        self.root.destroy()
        hwin = history_window()

    def quit_window(self):
        self.root.destroy()


class MyWindow:

    def __init__(self):
        self.root = Tk()
        self.root.geometry("500x500+450+100")
        self.root.title("welcome to test your math ability.")

        global i
        question = Label(self.root, text="第" + str(i) + "题" + " :  " + q[i - 1], height=2, width=28, bg="Green", font=("微软雅黑", 20))
        question.place(x=25, y=0, anchor='nw')

        answer_title = Label(self.root, text="answer: ", height=2, width=10, font=("Arial", 24))
        answer_title.place(x=0, y=100, anchor='nw')

        answerbox = Entry(self.root, width=10)
        answerbox.place(x=160, y=134, anchor='nw')
        user_answer[i-1] = answerbox.get()

        if user_answer[i-1] == right_answer[i-1]:
            global rightnum
            rightnum += 1

        nextq = Button(self.root, text="next question", height=1, width=15, fg="red", bg="black", font=("Arial", 16), command=self.OnNext)
        nextq.place(x=260, y=320, anchor='nw')

        self.count = 0
        self.total_time = 10
        while self.count <= self.total_time:
            remain_time = self.total_time - self.count
            time_label = Label(self.root, text=str(remain_time) + "s", height=2, width=7, bg="SkyBlue",
                               font=("微软雅黑", 24))
            time_label.place(x=35, y=300, anchor='nw')
            self.root.update()
            time.sleep(1)  # sleep 1 second
            self.count += 1
        if self.total_time != -1:
            showinfo('notify', 'time\'s up!')
            self.OnNext()

    def OnNext(self):
        global i
        i = i+1

        self.total_time = -1
        self.root.destroy()

        if i != num+1:
            win = MyWindow()
        else:
            win = result_window()


nowTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')  #record time

with open('question.txt', 'r') as f1:
    q = f1.readlines()

num = len(q)

with open('answer.txt', 'r') as f2:
    right_answer = f2.readlines()

win = MyWindow()

win.root.mainloop()