class Node:
    def __init__(self, d):
        self.data = d
        self.next = None

head = None

def RemoveLoop(head):
    slow = head
    fast = head

    #Floyd's Detection Algorithm
    while (slow != None and fast != None and fast.next != None):
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            print("Loop detected")
            slow.next = None
            return 1

    return 0

head = Node(10)
head.next = Node(20)
head.next.next = Node(30)
head.next.next.next = Node(40)
head.next.next.next.next = Node(50)


temp = head
while (temp.next != None):
    temp = temp.next

temp.next = head.next.next # Loop starts at node 30

# Detect and remove loop
if (RemoveLoop(head)):
    print("Loop exists and has been removed")
else:
    print("No loop found in the Linked List")
