def buildTree(tree, arr, start, end, pos):
    if start > end:
        return
    
    if start == end:
        tree[pos] = arr[start]
        return
    
    mid = (start+end)//2
    buildTree(tree, arr, start, mid, 2*pos+1)
    buildTree(tree, arr, mid+1, end, 2*pos+2)
    
    tree[pos] = max(tree[2*pos+1], tree[2*pos+2])
    
def rangeUpdateQueryLazy(tree, lazy, start, end, pos, query_start, query_end, inc):
    
    # if updates are pending
    if lazy[pos] !=0:
        tree[pos] += lazy[pos]
        if query_start != query_end:      # Not a leaf node
            lazy[2*pos+1] += lazy[pos]
            lazy[2*pos+2] += lazy[pos]
        lazy[pos] = 0
    
    # No Overlap
    if start > query_start or end < query_end:
        return
    
    # Complete overlap
    if start <= query_start and end >= query_end:
        tree[pos] += inc
        if (query_start != query_end):
            lazy[2*pos+1] += inc
            lazy[2*pos+2] += inc
        return
    
    # partial overlap
    mid = (query_start + query_end)//2
    rangeUpdateQueryLazy(tree, lazy, start, end, 2*pos+1, query_start , mid, inc)
    rangeUpdateQueryLazy(tree, lazy, start, end, 2*pos+2, mid+1, query_end, inc)
    
    tree[pos] = max(tree[2*pos+1], tree[2*pos+2])


if __name__ == "__main__":
    n, m = list(map(int, input().split()))
    arr = [0]*n
    tree = [0]*(4*n+1)
    
    buildTree(tree, arr, 0, n-1, 0)

    query_start, query_end, inc = list(map(int, input().split()))
    rangeUpdateQueryLazy(tree, lazy, 0, n-1, 0, query_start, query_end, inc)
        
    print("Maximum element is:",tree[0])