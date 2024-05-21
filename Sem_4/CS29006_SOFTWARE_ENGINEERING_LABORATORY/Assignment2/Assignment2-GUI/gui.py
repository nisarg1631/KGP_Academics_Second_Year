from tkinter import *
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)

root = Tk()

mylabel_equation = Label(root, text="Enter equation in x")
mylabel_equation.pack()
equation = Entry(root, borderwidth=10)
equation.pack()

mylabel_start = Label(root, text="Enter start of the range for x")
mylabel_start.pack()
start = Entry(root, borderwidth=10)
start.pack()

mylabel_end = Label(root, text="Enter end of the range for x")
mylabel_end.pack()
end = Entry(root, borderwidth=10)
end.pack()


def get_values():
    eq = equation.get()
    eq = eq.replace('^', '**')
    eq = eq.replace('x', '(x)')
    st = eval(start.get())
    en = eval(end.get())
    vals = []

    for i in range(int(st), int(en) + 1, 1):
        new_eq = eq.replace('x', str(i))
        vals.append(eval(new_eq))

    plt.plot(range(int(st), int(en) + 1, 1), vals)
    plt.show()
    # label = Label(root, text = vals[0])
    # label.grid(row = 7, column = 0)


button = Button(root, text="CALCULATE", padx=30, pady=7, command=get_values)
button.pack()
root.mainloop()
