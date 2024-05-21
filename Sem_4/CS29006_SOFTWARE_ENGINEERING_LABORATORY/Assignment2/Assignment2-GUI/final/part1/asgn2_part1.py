from tkinter import *
from tkinter.font import Font
from tkinter import messagebox
from numpy import *
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure


class PrimaryDisplay:
    def __init__(self, heading):
        self.root = Toplevel(root)
        self.root.title("PLOTTER")
        self.root.geometry("710x1000")
        self.root.resizable(0,0)
        
        self.titleframe = Frame(self.root, bg='gray30')
        self.heading = Label(self.titleframe, text=heading, justify=CENTER, bg='gray60',
                             font=Font(family="Comic Sans MS", size=15, weight='bold'))

        self.font_csms = Font(family="Comic Sans MS", size=10, weight='bold')
        self.font_tnr = Font(family="Times New Roman", size=15)

        self.topframe = Frame(self.root)
        self.label1 = Label(self.topframe, text='f(x) = ', font=self.font_csms)
        self.input_func = Entry(self.topframe, font=self.font_tnr)
        self.input_func.config(width=60)
        self.input_func.insert(0,"x")
        
        self.bottomframe = Frame(self.root)
        self.label2 = Label(self.bottomframe, text='Evaluate from x =', font=self.font_csms)
        self.input_from = Entry(self.bottomframe, font=self.font_tnr, validate='key')
        self.input_from.config(width=10, validatecommand=(self.input_from.register(self.validateInputFloat), '%P'))
        self.input_from.insert(0, "1.0")
        self.label3 = Label(self.bottomframe, text='to x =', font=self.font_csms)
        self.input_to = Entry(self.bottomframe, font=self.font_tnr, validate='key')
        self.input_to.config(width=10, validatecommand=(self.input_to.register(self.validateInputFloat), '%P'))
        self.input_to.insert(0, "10.0")
        self.label4 = Label(self.bottomframe, text='Number of samples =', font=self.font_csms)
        self.input_steps = Entry(self.bottomframe, font=self.font_tnr, validate='key')
        self.input_steps.config(width=10, validatecommand=(self.input_steps.register(self.validateInputInt), '%P'))
        self.input_steps.insert(0, "10")

        self.button_eval = Button(self.root, text='EVALUATE', bg='gray60', command=self.evaluate, width=15, height=2)

        self.resultframe = Frame(self.root)
        self.content = Text(self.resultframe, font=Font(family="Times New Roman", size=15), state=DISABLED, wrap=WORD)
        self.content_scrollbar = Scrollbar(self.resultframe)
        self.content.config(yscrollcommand=self.content_scrollbar.set, height=10)
        self.content_scrollbar.config(command=self.content.yview)

        self.plotframe = Frame(self.root)
        self.plotcanvas = FigureCanvasTkAgg(Figure())
        self.toolbar = NavigationToolbar2Tk(self.plotcanvas, self.plotframe)
        self.plotcanvas.get_tk_widget().pack_forget()
        self.toolbar.pack_forget()

        self.button_quit = Button(self.root, text='QUIT APPLICATION', bg='gray60', command=self.QuitApp, width=15, height=2)
        self.pack()

    def pack(self):
        self.heading.pack(fill=X)
        
        self.label1.grid(row=0, column=0)
        self.input_func.grid(row=0, column=1)

        self.label2.grid(row=0, column=0, padx=5)
        self.input_from.grid(row=0, column=1)
        self.label3.grid(row=0, column=2, padx=5)
        self.input_to.grid(row=0, column=3)
        self.label4.grid(row=0, column=4, padx=5)
        self.input_steps.grid(row=0, column=5)

        self.content_scrollbar.pack(side=RIGHT, fill=Y)
        self.content.pack(fill=BOTH)
        
        self.titleframe.pack(padx=10, pady=10, fill=X)
        self.topframe.pack(padx=10, pady=5)
        self.bottomframe.pack(padx=10, pady=5)
        self.button_eval.pack(pady=10)
        self.resultframe.pack(padx=10, pady=5)
        self.plotframe.pack(padx=10, pady=5)
        self.button_quit.pack(pady=10)
    
    def validateInputFloat(self, inp):
        if not inp or inp=='-':
            return True
        try:
            float(inp)
            return True
        except:
            return False
    
    def validateInputInt(self, inp):
        if not inp or inp.isdigit():
            return True
        else:
            return False

    def evaluate(self):
        self.content.config(state=NORMAL)
        self.content.delete(1.0, END)
        self.content.config(state=DISABLED)
        self.plotcanvas.get_tk_widget().pack_forget()
        self.toolbar.pack_forget()
        try:
            fx = self.input_func.get().rstrip().replace('^','**')
            start = float(self.input_from.get().rstrip())
            end = float(self.input_to.get().rstrip())
            step = int(self.input_steps.get().rstrip())
            vals = linspace(start, end, step)
            answer = [eval(fx) for x in vals]
            if (NAN in answer) or (PINF in answer) or (NINF in answer):
                raise Exception("Division by zero/Domain error")
            self.content.config(state=NORMAL)
            self.content.delete(1.0, END)
            for (val, ans) in zip(vals, answer):
                self.content.insert(END, f'f({val:.4f}) = {ans:.4f}\n')
            self.content.config(state=DISABLED)
            self.plotgraph(vals, answer)
        except Exception as e:
            messagebox.showerror(title="Cannot evaluate. Check input.", message=e)
    
    def plotgraph(self, xdata, ydata):
        graph = Figure(figsize=(4.5,4.5), dpi=100)
        graph.add_subplot(111).plot(xdata, ydata)
    
        self.plotcanvas = FigureCanvasTkAgg(graph, self.plotframe)
        self.plotcanvas.draw()
        self.plotcanvas.get_tk_widget().pack()
        self.toolbar = NavigationToolbar2Tk(self.plotcanvas, self.plotframe)
        self.toolbar.update()
        self.plotcanvas.get_tk_widget().pack()

    def QuitApp(self):
        root.quit()


if __name__ == '__main__':
    # auxiliary window to  quit the application successfully
    root = Tk()
    root.withdraw()

    # application windows
    disp1 = PrimaryDisplay("FUNCTION PLOTTER")
    root.mainloop()
