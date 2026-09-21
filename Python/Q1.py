

# # Create a dictionary where:Q5
# • Keys = student names
# • Values = marks (integer)
# Write a menu-based program where user presses a key (ʼAʼ, ‘Bʼ, ‘Cʼ, ‘Dʼ)
# depending on the operation they want to perform on the dictionary:
# 1. - Add a studentA
# 2. - Update marksB
# 3. - Search for a studentC
# 4. - Display all students and marks

# ========================= ANS=========================
students = {}
print("A. Add a student")
print("B. Update marks")
print("C. Search for a student")
print("D. Display all students")

k = input("Enter A, B, C or D: ").upper()

match k:
    case "A":
        name = input("Enter student name: ")
        marks = int(input("Enter marks: "))

        students[name] = marks

        print("Student added successfully!")

    case "B":
        name = input("Enter student name: ")

        if name in students:
            marks = int(input("Enter new marks: "))
            students[name] = marks
            print("Marks updated successfully!")
        else:
            print("Student not found.")

    case "C":
        name = input("Enter student name: ")

        if name in students:
            print("Marks:", students[name])
        else:
            print("Student not found.")

    case "D":
        print("\nStudent Information:")

        for name, marks in students.items():
            print("Name:", name, "| Marks:", marks)

    case _:
        print("Invalid option.")