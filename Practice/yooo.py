x=int (input("Enter the input\n"))
y=int(input("Enter the input\n"))
print("Enter your operation: \n")
s=input()


match s:
    case '+':
        s=x+y
        print("Your number:",s)
    case '*':
        s=x*y
        print("Your number:",s)




