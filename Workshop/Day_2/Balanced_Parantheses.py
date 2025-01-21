def check(a):
    open = ["{", "[", "("]
    close = ["}", "]", ")"]

    stack = []
    c = 0
    for i in a:
        if c==0 and i in close: 
            c=1
            return "Unbalanced"
        
        if i in open: stack.append(i)
        elif i in close:
            pos = close.index(i)
            if ((len(stack) > 0) and (open[pos] == stack[len(stack)-1])): stack.pop()
            else: return "Unbalanced"
        if len(stack) == 0: return "Balanced"
        else: return "Unbalanced"

a = str(input())
print(check(a))