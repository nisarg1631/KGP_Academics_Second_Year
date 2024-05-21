from tkinter import *
from tkinter.ttk import Combobox
from tkinter import filedialog as fd
import matplotlib.pyplot as plt

root = Tk()

leftframe = Frame(root,bg='green',padx=10,pady=10)
leftframe.grid(row=0,column=0,sticky=S+N+E+W)

b1=Button(leftframe,text='left button',padx=10,pady=10)
b1.grid(row=0,column=0,sticky=S+N+E+W)

rightframe = Frame(root,bg='red',padx=10,pady=10)
rightframe.grid(row=0,column=1,sticky=S+N+E+W)

b2=Button(rightframe,text='right button',padx=10,pady=10)
b2.grid(row=0,column=0)

root.grid_columnconfigure(0,weight=1)

root.mainloop()