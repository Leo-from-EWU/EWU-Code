# Short Note: Passing Objects

If we pass Object A into Class B, Class B can access Object A's functions.

**Example:**
- **Object A:** `chatroom` (has a function `add_user()`)
- **Class B:** `User`

When we pass Object A (`chatroom`) into Class B (`User`), Class B can call Object A's function like this:
`chatroom.add_user(self)`

---

# Short Note: Creating Objects Inside Classes (Composition)

A Class can create and store objects of another Class. This is called a **"Has-A"** relationship (Composition).

**Example:**
- **Class A:** `ChatRoom`
- **Class B:** `Message`

Because `Message` is globally available in the file, `ChatRoom` can create a brand new `Message` object directly inside its own function like this:
`message = Message(sender, content)`

`ChatRoom` then stores this new object in its own list: `self.messages.append(message)`. A ChatRoom *is not* a message, but it *has* messages.

---

# OOP Concepts Checklist (Based on Mini Chatroom)

If you are struggling to understand OOP, this code is the perfect practice! Here are the 5 core concepts it uses. Focus on mastering these:

### 1. Classes vs. Objects (The Blueprint vs. The House)
- **Concept:** A `Class` is just a set of instructions. An `Object` is the actual thing built from those instructions.
- **In the code:** `class User:` is the blueprint. `u1 = User("Alice")` is the actual living, breathing object built from that blueprint.

### 2. Instance Variables (`self`) (Personal Belongings)
- **Concept:** Variables attached to `self` belong *only* to that specific object.
- **In the code:** `self.username`. Alice has her own username, Bob has his own. They don't share. `self` means "My own personal..."

### 3. Class Variables (Shared Community Property)
- **Concept:** Variables attached directly to the Class, shared by *everyone*. 
- **In the code:** `Message.message_counter = 1` (Line 5). There is only one counter. Every time a new message is made, they all look at the exact same shared counter to figure out what ID is next.

### 4. Object Interaction (Passing the Baton)
- **Concept:** Objects shouldn't forcibly change each other's data; they should ask nicely by calling each other's functions.
- **In the code:** The User doesn't hack into the ChatRoom's list. Instead, the User passes itself to the ChatRoom: `room_to_join.add_user(self)`. The ChatRoom does the work.

### 5. Composition (The "Has-A" Relationship)
- **Concept:** Objects can act like containers that hold other objects. 
- **In the code:** The `ChatRoom` object literally contains a list of `User` objects (`self.users = []`) and a list of `Message` objects (`self.messages = []`). 
