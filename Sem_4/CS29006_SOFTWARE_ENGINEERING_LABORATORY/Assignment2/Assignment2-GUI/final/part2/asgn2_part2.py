from tkinter import *
from tkinter.ttk import Combobox
from tkinter.font import Font
from tkinter import messagebox
from tkinter import filedialog
from PIL import ImageTk
from PIL import Image as Im


class PrimaryDisplay:
    def __init__(self, heading):
        self.root = Toplevel(root)
        self.root.resizable(0, 0)
        self.root.title("THE SOCIAL NETWORK")
        self.titleframe = Frame(self.root, bg='gray30')
        self.topframe = Frame(self.root)
        self.bottomframe = Frame(self.root)
        self.heading = Label(self.titleframe, text=heading, justify=CENTER, bg='gray60',
                             font=Font(family="Comic Sans MS", size=15, weight='bold'))
        self.droplist = Combobox(self.topframe, values=[name for name in users.keys()], state='readonly')
        self.dropbox_label = Label(self.topframe, text='Select user:', justify=LEFT,
                                   font=Font(family="Comic Sans MS", size=10, weight='bold'))

    def pack(self):
        self.heading.pack()
        self.droplist.grid(row=5, column=1)
        self.dropbox_label.grid(row=5, column=0, padx=10)
        self.titleframe.pack(padx=10, pady=10, fill=X)
        self.topframe.pack(padx=10, pady=10)
        self.bottomframe.pack(padx=10, pady=10, fill=BOTH)


class CommunicationModule(PrimaryDisplay):
    def __init__(self):
        super().__init__('SEND MESSAGES')
        self.message_label = Label(self.bottomframe, text='Message Type:', justify=LEFT,
                                   font=Font(family="Comic Sans MS", size=10, weight='bold'))
        self.message_type = IntVar()  # 0 for personal, 1 for group
        self.message_personal = Radiobutton(self.bottomframe, text='PERSONAL', variable=self.message_type, value=0,
                                            command=self.updatelist)
        self.message_group = Radiobutton(self.bottomframe, text='GROUP', variable=self.message_type, value=1,
                                         command=self.updatelist)
        self.sendto_label = Label(self.bottomframe, text='Send to:', justify=CENTER,
                                  font=Font(family="Comic Sans MS", size=10, weight='bold'))
        self.sendto_list = Combobox(self.bottomframe, state='readonly')
        self.inputframe_text = Frame(self.root)
        self.content = Text(self.inputframe_text, font=Font(family="Times New Roman", size=15), wrap=WORD)
        self.content.config(height=15, width=40)
        self.inputframe_image = Frame(self.root)
        self.image_button = Button(self.inputframe_image, text='SELECT\nIMAGE', bg='gray60', command=self.select_image)
        self.remove_image_button = Button(self.inputframe_image, text='REMOVE\nIMAGE', bg='gray60', command=self.remove_image)
        self.image_info = Text(self.root, font=Font(family="Times New Roman", size=15), state=DISABLED)
        self.image_info.config(height=1, width=40)
        self.send_button = Button(self.root, text='SEND', bg='gray60', command=self.send)
        self.pack()

    def pack(self):
        self.droplist.bind("<<ComboboxSelected>>", self.callback)
        self.droplist.current(0)
        self.callback("<<ComboboxSelected>>")
        self.message_label.grid(row=0, column=0, padx=(50,0))
        self.message_personal.grid(row=0, column=1)
        self.message_group.grid(row=0, column=2)
        self.sendto_label.grid(row=10, column=0, padx=(40,0), pady=10)
        self.sendto_list.place(x=150, y=32)
        self.content.pack(fill=X)
        self.image_button.pack(side=LEFT, padx=10)
        self.remove_image_button.pack(side=RIGHT, padx=10)
        self.remove_image()
        super().pack()
        self.inputframe_text.pack(padx=5, pady=10)
        self.inputframe_image.pack(pady=10)
        self.image_info.pack()
        self.send_button.pack(padx=10, pady=10)

    def select_image(self):
        img = filedialog.askopenfilename(filetypes=[("PNG", "*.png"), ("JPEG", "*.jpeg"), ("JPG", "*.jpg")])
        if img:
            self.image_info.config(state=NORMAL)
            self.image_info.delete(1.0, END)
            self.image_info.insert(END, img)
            self.image_info.config(state=DISABLED)

    def remove_image(self):
        self.image_info.config(state=NORMAL)
        self.image_info.delete(1.0, END)
        self.image_info.insert(END, "No image selected")
        self.image_info.config(state=DISABLED)

    def callback(self, event):
        self.message_type.set(0)
        self.updatelist()

    def updatelist(self):
        if not self.message_type.get():
            self.sendto_list.config(values=[contact.userid for contact in users[self.droplist.get()].contacts])
        else:
            self.sendto_list.config(values=[group.groupid for group in users[self.droplist.get()].groups])
        self.sendto_list.current(0)

    def send(self):
        text = self.content.get(1.0, END)
        text = text.rstrip()
        img = self.image_info.get(1.0, END)
        img = img.rstrip()
        if img == "No image selected":
            img = None

        if text or img:
            if not self.message_type.get():
                users[self.droplist.get()].sendMessage(text, img, [users[self.sendto_list.get()]])
            else:
                groups[self.sendto_list.get()].sendMessage(text, img, users[self.droplist.get()])
        else:
            messagebox.showerror(title="EMPTY MESSAGE", message="Please enter some text or select an image to send.")
        self.content.delete(1.0, END)
        self.remove_image()


class UserInfoDisplay(PrimaryDisplay):
    def __init__(self, heading):
        super().__init__(heading)
        self.content = Text(self.bottomframe, font=Font(family="Times New Roman", size=15), state=DISABLED, wrap=WORD)
        self.content_scrollbar = Scrollbar(self.bottomframe)
        self.content.config(yscrollcommand=self.content_scrollbar.set)
        self.content_scrollbar.config(command=self.content.yview)
        self.pack()

    def pack(self):
        self.droplist.bind("<<ComboboxSelected>>", self.callback)
        self.droplist.current(0)
        self.callback("<<ComboboxSelected>>")
        self.content_scrollbar.pack(side=RIGHT, fill=Y)
        self.content.pack(fill=BOTH)
        super().pack()

    def callback(self, event):
        self.content.config(state=NORMAL)
        self.content.delete(1.0, END)


class ContactsDisplay(UserInfoDisplay):
    def __init__(self):
        super().__init__('CONTACTS')
        self.content.config(height=10, width=30)

    def callback(self, event):
        super().callback(event)
        global users
        name = self.droplist.get()
        if not users[name].contacts:
            self.content.insert(END, "User doesn't have any contact")
        else:
            for num, contacts in enumerate(users[name].contacts):
                self.content.insert(END, f'{num + 1}. ' + contacts.userid + '\n')
        self.content.config(state=DISABLED)


class GroupsDisplay(UserInfoDisplay):
    def __init__(self):
        super().__init__('GROUPS')
        self.content.config(height=10, width=30)

    def callback(self, event):
        super().callback(event)
        global users
        name = self.droplist.get()
        if not users[name].groups:
            self.content.insert(END, "User isn't part of any group")
        else:
            for num, group in enumerate(users[name].groups):
                self.content.insert(END, f'{num + 1}. ' + group.groupid + '\n')
        self.content.config(state=DISABLED)


class MessagesDisplay(UserInfoDisplay):
    def __init__(self):
        self.image_buffer = []
        super().__init__('INCOMING MESSAGES')
        self.content.config(height=25, width=30)
        self.button = Button(self.topframe, text='REFRESH', bg='gray60', command=self.refresh)
        self.button.grid(row=5, column=2, padx=10)

    def refresh(self):
        self.callback("<<ComboboxSelected>>")

    def callback(self, event):
        super().callback(event)
        self.image_buffer.clear()
        global users
        name = self.droplist.get()
        if not users[name].messages:
            self.content.insert(END, "User doesn't have any messages")
        else:
            for num, message in enumerate(users[name].messages):
                self.content.insert(END, f'{num + 1}. ' + message[0] + '\n')
                if message[1]:
                    image = Im.open(message[1])
                    width, height = image.size
                    image = image.resize((350, int((350.0 * height) / width)), Im.ANTIALIAS)
                    self.image_buffer.append(ImageTk.PhotoImage(image))
                    self.content.image_create(END, image=self.image_buffer[-1])
                    self.content.insert(END, '\n')
                self.content.insert(END, "\n\t****************\n\n")
        self.content.config(state=DISABLED)


class User:
    def __init__(self, userid):
        self.userid = userid
        self.contacts = []
        self.groups = []
        self.messages = []

    def addContact(self, contact):
        self.contacts.append(contact)

    def addGroup(self, group):
        self.groups.append(group)

    def sendMessage(self, text, image, recipients=[]):
        for recipient in recipients:
            recipient.messages.append((text + f" [from {self.userid}]", image))


class Group:
    def __init__(self, groupid):
        self.groupid = groupid
        self.members = []

    def addMember(self, member):
        member.groups.append(self)
        self.members.append(member)

    def sendMessage(self, text, image, user):
        user.sendMessage(text, image, [recipient for recipient in self.members if recipient is not user])


def readFile():
    try:
        file = open("social_network.txt", "r")
        users = {}
        groups = {}
        state = ''

        for line in file.readlines():
            line = line.rstrip()
            if line == '#users':
                state = 'users'
                continue
            if line == '#groups':
                state = 'groups'
                continue
            name, _, links = line.replace('<', '').replace('>', '').partition(': ')
            if state == 'users':
                users[name] = links.split(', ')
            elif state == 'groups':
                groups[name] = links.split(', ')
        file.close()
        return users, groups
    except IOError:
        print("\'social_network.txt\' not found. Please load one before proceeding.\n")
        sys.exit(1)

def readMessages():
    try:
        file = open("messages.txt", "r")
        name = ""
        text = ""
        img = ""
        line = file.readline()
        while line:
            if line[0]=='*':
                name = line.rstrip()[1:]
            else:
                text = line.rstrip()[1:]
                line = file.readline().rstrip()[1:]
                if line == 'None':
                    img = None
                else:
                    img = line
                users[name].messages.append((text, img))
            line = file.readline()
    except IOError:
        pass


def writeMessages():
    file = open("messages.txt", "w")
    for user in users.values():
        file.write(f"*{user.userid}\n")
        for received in user.messages:
            file.write('-'+str(received[0])+'\n')
            file.write('-' + str(received[1]) + '\n')
    file.close()


def QuitApp():
    root.quit()


if __name__ == '__main__':
    userlist, grouplist = readFile()
    users = {user: User(user) for user in userlist.keys()}
    groups = {group: Group(group) for group in grouplist.keys()}

    for userid, user in users.items():
        # sanity check to ensure only contacts present in the user list are added as contacts
        validcontacts = [users[contact] for contact in userlist[userid] if contact in users.keys()]
        for contact in validcontacts:
            user.addContact(contact)
    for groupid, group in groups.items():
        # sanity check to ensure only members present in the user list are added as members
        validmembers = [users[member] for member in grouplist[groupid] if member in users.keys()]
        for member in validmembers:
            group.addMember(member)

    readMessages()

    # auxiliary window to  quit the application successfully
    root = Tk()
    root.title("THE SOCIAL NETWORK")
    root.geometry("300x300")
    root.resizable(0, 0)
    button = Button(root, text='QUIT APPLICATION', bg='gray60', command=QuitApp, width=15, height=3)
    button.pack(pady=10)

    # application windows
    disp1 = ContactsDisplay()
    disp2 = GroupsDisplay()
    disp3 = MessagesDisplay()
    disp4 = CommunicationModule()
    root.mainloop()

    writeMessages()
