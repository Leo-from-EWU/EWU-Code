class Book:
    count=0
    l1=[]
    def __init__(self,title,author,rvw):
        self.ttile=title
        self.author=author
        self.rvw=rvw
        
    def addrvw(self):
        Book.l1.append(self.rvw)
        Book.count=Book.count+1
        self.display()
        

    

    def display(self):
            print(f"{self.rvw}.Reviw")

b1=Book("Leon the greater king","leon","This book is goodf")
b2=Book("Hi is the power","Sam","Umm gd")  



b1.addrvw()
b2.display()
