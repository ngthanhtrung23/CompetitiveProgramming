# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        if root is None:
            return ""
        
        vals = []
        self.dfs1(root, vals)
        return ','.join(vals)
    
    def dfs1(self, root, vals):
        if root == None:
            vals.append('')
            return
        
        vals.append(str(root.val))
        self.dfs1(root.left, vals)
        self.dfs1(root.right, vals)
        

    def deserialize(self, s):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        if s == "":
            return None
        data = s.split(',')
        return self.dfs2(data, 0)[0]
    
    def dfs2(self, data, i):
        if data[i] == '':
            return (None, i+1)
        
        res = TreeNode(int(data[i]))
        res.left, i = self.dfs2(data, i + 1)
        res.right, i = self.dfs2(data, i)
        
        return (res, i)

# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))
