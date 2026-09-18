class EWU:
    Uni= "East West University"

    def __init__(self,name,id,marks):
        self.name=name
        self.id=id
        self.marks=marks
    def welcome(self):
        print("Welcome to EWU students to get cooked....")



print("Hey bockchod enter")
name=input()
id=int(input())
marks=80
s1=EWU(name,id,marks)

print(s1.name,s1.marks,s1.id)
s1.welcome()

