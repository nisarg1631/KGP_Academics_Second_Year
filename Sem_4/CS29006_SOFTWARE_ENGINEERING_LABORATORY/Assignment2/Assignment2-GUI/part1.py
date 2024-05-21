import os
from tkinter import *
from ast import literal_eval
from numpy import *
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg, NavigationToolbar2Tk)
from tkinter.font import Font


class LeftFrame(Frame):
    def __init__(self, master=None, rframe=None):
        Frame.__init__(self, master, background="#424242")
        self.master = master
        self.rframe = rframe
        self.grid(row=0, column=0)

        label1_x = 10
        label1_y = 1
        self.lab1 = Label(self, text="Function (variable x):", bd=2)
        self.lab1.grid(row=label1_x, column=label1_y, padx=10, pady=10)
        self.exprtext = Text(self, width=20, height=5,font=Font(
            family="Times New Roman", size=15))
        self.exprtext.grid(row=label1_x, column=label1_y+10, padx=10, pady=10)
        self.lab2 = Label(self, text="Variable Range (a,b): ", bd=2)
        self.lab2.grid(row=label1_x+8, column=label1_y, padx=10, pady=10)
        self.variablevalue = Text(self, width=20, height=5,font=Font(
            family="Times New Roman", size=15))
        self.variablevalue.grid(
            row=label1_x+8, column=label1_y+10, padx=10, pady=10)
        self.evaluatebutton = Button(
            self, text="Evaluate !", command=self.evaluate)
        self.evaluatebutton.grid(row=100, column=label1_y)
        self.exitbutton = Button(
            self, text="Exit", command=exit)
        self.exitbutton.grid(row=100, column=label1_y+10, padx=10)

    def evaluate(self):
        expr = self.exprtext.get(1.0, END)
        print(expr)
        varval = self.variablevalue.get(1.0, END)
        print(varval)
        a = eval(varval)
        print(a)
        x = arange(a[0], a[1], 0.01)
        expr = expr.strip('\n')
        y = eval(expr)
        self.rframe.frame_plot(x, y)


class RightFrame(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master, bg="#848484")
        self.master = master
        self.grid(row=0, column=1, sticky=S+N+E+W)
        master.grid_columnconfigure(1, weight=1)
        master.grid_rowconfigure(0, weight=1)

    def frame_plot(self, x, y):
        # print(y)
        fig = Figure(figsize=(5, 5.5), dpi=100)
        fig.add_subplot(111).plot(x, y)
        try:
            self.canvas.get_tk_widget().pack_forget()
            self.toolbar.pack_forget()
        except AttributeError:
            pass
        self.canvas = FigureCanvasTkAgg(fig, master=self)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack()
        self.toolbar = NavigationToolbar2Tk(self.canvas, self)
        self.toolbar.update()
        self.canvas.get_tk_widget().pack()


class Window(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master, background="#424242")
        self.master = master
        master.geometry("1000x600")
        self.rightframe = RightFrame(master)
        self.leftframe = LeftFrame(master, self.rightframe)
        master.wm_title("Function Grapher")
        self.grid(row=0, column=0, sticky="nsew")


if os.environ.get('DISPLAY', '') == '':
    print('no display found. Using :0.0')
    os.environ.__setitem__('DISPLAY', ':0.0')


root = Tk()
app = Window(root)
root.resizable(False, False)

root.mainloop()
