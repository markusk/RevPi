#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
u"""Kleines Fenster mit 2 Buttons.

Ein Button schaltet den Ausgang O_1 beim Klick an und der andere Button beim
Klick wieder aus.

"""
import tkinter
import revpimodio2


class MyApp(tkinter.Frame):

    def __init__(self, master=None):
        super().__init__(master)
        self.pack()
        
        # RevPiModIO verwenden mit autorefresh=True!
        self.rpi = revpimodio2.RevPiModIO(autorefresh=True)

        # Button erstellen und "click_an" als Event binden
        self.btn_an = tkinter.Button(self)
        self.btn_an["text"] = "anschalten"
        self.btn_an["command"] = self.click_an
        self.btn_an.pack()

        # Button erstellen und "click_aus" als Event binden
        self.btn_aus = tkinter.Button(self)
        self.btn_aus["text"] = "ausschalten"
        self.btn_aus["command"] = self.click_aus
        self.btn_aus.pack()

    def click_an(self):
        # Ausgang O_1 auf True setzen
        self.rpi.io.O_1.value = True

    def click_aus(self):
        # Ausgang O_1 auf False setzen
        self.rpi.io.O_1.value = False


if __name__ == "__main__":
    root = tkinter.Tk()
    myapp = MyApp(root)
    root.mainloop()
