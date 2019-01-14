# -*- coding: utf-8 -*-

from Tkinter import *
import datetime
import time
from tkMessageBox import *

q = ["1*2+(3-4)*23/123", "1+233333333333333", "2*21"]  # question
num = 3    # question num
rightnum = 1
afz = [1, 2, 3]  # answer fz
afm = [2, 3, 9]   # answer fm
i = 1


def show_history(event):
    a = 0    #


def quit_window(event):
    quit()


def time_change_window():
    global i
    i = i+1
    if i == num+1:
        show_result()
    else:
        show_window(i)

    return


def show_result():
    str_num = str(num)
    str_rightnum = str(rightnum)
    acc = round(float(rightnum)/num, 3)*100
    str_acc = str(acc)
    line1 = Label(window, text="total question number: "+str_num, height=2, width=25, font=("Arial", 24))
    line1.place(x=0, y=0, anchor='nw')
    line2 = Label(window, text="your right answer number: "+str_rightnum, height=2, width=25, font=("Arial", 24))
    line2.place(x=0, y=80, anchor='nw')
    line3 = Label(window, text="your accuracy is: " + str_acc + "%", height=2, width=25, font=("Arial", 24))
    line3.place(x=0, y=160, anchor='nw')

    show_history_button = Button(window, text="show history", height=1, width=10, font=("Arial", 16))
    show_history_button.place(x=90, y=320, anchor='nw')
    show_history_button.bind("<Button-1>", show_history)

    close_button = Button(window, text="close", height=1, width=15, fg="red", bg="black", font=("Arial", 16))
    close_button.place(x=260, y=320, anchor='nw')
    close_button.bind("<Button-1>", quit_window)

    return


def change_window(event):
    if time_label.destroy() == 1:
        print(1111)
    global i
    i = i+1
    if i == num+1:
        show_result()
    else:
        show_window(i)

    return


def show_window(ind):
    question = Label(window, text="第"+str(ind) + "题"+" :  " + q[ind - 1], height=2, width=28, bg="Green", font=("微软雅黑", 20))
    question.place(x=25, y=0, anchor='nw')

    answer_title = Label(window, text="answer: ", height=2, width=10, font=("Arial", 24))
    answer_title.place(x=0, y=100, anchor='nw')

    answerbox = Entry(window, width=10)
    answerbox.place(x=160, y=134, anchor='nw')
    answer = answerbox.get()

    nextq = Button(window, text="next question", height=1, width=15, fg="red", bg="black", font=("Arial", 16))
    nextq.place(x=260, y=320, anchor='nw')
    nextq.bind("<Button-1>", change_window)

    count = 0
    total_time = 3
    while count <= total_time:
        remain_time = total_time - count
        global time_label
        time_label = Label(window, text=str(remain_time) + "s", height=2, width=7, bg="SkyBlue", font=("微软雅黑", 24))
        time_label.place(x=35, y=300, anchor='nw')
        window.update()
        time.sleep(1)  # sleep 1 second
        count += 1
    showinfo('notify', 'time\'s up!')
    if time_label.destroy() == 1:
        print(1111)
    time_change_window()

    return


nowTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')  #record time

window = Tk()
window.geometry("500x500+450+100")
window.title("welcome to test your math ability.")

show_window(1)
window.mainloop()
