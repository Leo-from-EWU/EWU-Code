# Solution for Question 1
students = {}

while True:
    print("\n--- Menu ---")
    print("A. Add a student")
    print("B. Update marks")
    print("C. Search for a student")
    print("D. Display all students")
    print("Q. Quit")

    k = input("Enter A, B, C, D or Q to quit: ").upper()

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
            if not students: # Quick check if dictionary is empty
                print("No students added yet!")
            else:
                for name, marks in students.items():
                    print("Name:", name, "| Marks:", marks)
        
        case "Q":
            print("Goodbye!")
            break  # This breaks us out of the while loop to stop the program

        case _:
            print("Invalid option. Try again.")
