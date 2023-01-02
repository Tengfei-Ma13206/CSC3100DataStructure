class Node:
    def __init__(self, v):
        self.leftSum = v
        self.val = v
        self.left = None
        self.right = None
        self.pos = 1
root = None
def findNode(root, p):
    if root == None:
        return Node(0)
    else:
        if p < root.pos:
            return findNode(root.left, p)
        elif p == root.pos:
            return root
        else:
            return findNode(root.right, p-root.pos)

def insert(root, p, v):
    if root == None:
        return Node(v)
    else:
        if p < root.pos:
            root.pos += 1
            root.leftSum += v
            root.left = insert(root.left, p, v)
        else:
            root.right = insert(root.right, p - root.pos, v)
    return root

def remove(root, p):
    if root == None:
        return None
    else:
        v = findNode(root, p).val
        if p < root.pos:
            root.pos -= 1
            root.leftSum -= v
            root.left = remove(root.left, p)
        elif p > root.pos:
            root.right = remove(root.right, p -root.pos)
        else:
            if root.left != None and root.right != None:
                tmp = root.left
                root.pos -= 1
                root.leftSum -= v
                while tmp.right != None:
                    tmp = tmp.right
                root.val = tmp.val
                root.left = remove(root.left, p-1)
            elif (root.left == None and root.right == None):
                root = None
            else:
                if root.left != None:
                    root = root.left
                else:
                    root = root.right
    return root

def suml(root, l):
    if root.pos == l:
        return root.leftSum
    elif root.pos < l:
        return root.leftSum+suml(root.right, l-root.pos)
    else:
        return suml(root.left, l)
operationNum = int(input())
for i in range(operationNum):
    op = input().split()
    if int(op[0]) == 1:
        root = insert(root, int(op[1]), int(op[2]))
    elif int(op[0]) == 2:
        root = remove(root, int(op[1]))
    else:
        nodel = findNode(root, int(op[1]))
        print(suml(root, int(op[2])) - suml(root,int(op[1])) + nodel.val)





